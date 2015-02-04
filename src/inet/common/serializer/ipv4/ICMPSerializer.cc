//
// Copyright (C) 2005 Christian Dankbar, Irene Ruengeler, Michael Tuexen, Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include <platdep/sockets.h>

#include "inet/common/serializer/ipv4/ICMPSerializer.h"

#include "inet/applications/pingapp/PingPayload_m.h"
#include "inet/common/serializer/headers/bsdint.h"
#include "inet/common/serializer/headers/defs.h"
#include "inet/common/serializer/headers/in.h"
#include "inet/common/serializer/headers/in_systm.h"
#include "inet/common/serializer/ipv4/headers/ip.h"
#include "inet/common/serializer/ipv4/headers/ip_icmp.h"
#include "inet/common/serializer/ipv4/IPv4Serializer.h"
#include "inet/common/serializer/TCPIPchecksum.h"
#include "inet/linklayer/common/Ieee802Ctrl_m.h"
#include "inet/networklayer/common/IPProtocolId_m.h"

#if !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32) && !defined(__CYGWIN__) && !defined(_WIN64)
#include <netinet/in.h>    // htonl, ntohl, ...
#endif // if !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32) && !defined(__CYGWIN__) && !defined(_WIN64)

namespace inet {

namespace serializer {

Register_Serializer(ICMPMessage, IP_PROT, IP_PROT_ICMP, ICMPSerializer);

int ICMPSerializer::serialize(const ICMPMessage *pkt, unsigned char *buf, unsigned int bufsize)
{
    Buffer b(buf, bufsize);
    Context c;
    serialize(pkt, b, c);
    return b.getPos();
}

void ICMPSerializer::serialize(const cPacket *_pkt, Buffer &b, Context& c)
{
    unsigned int startpos = b.getPos();
    const ICMPMessage *pkt = check_and_cast<const ICMPMessage *>(_pkt);

    switch (pkt->getType()) {
        case ICMP_ECHO_REQUEST: {
            PingPayload *pp = check_and_cast<PingPayload *>(pkt->getEncapsulatedPacket());
            b.writeByte(ICMP_ECHO);
            b.writeByte(pkt->getCode());
            b.writeUint16(0);   // crc
            b.writeUint16(pp->getOriginatorId());
            b.writeUint16(pp->getSeqNo());
            unsigned int datalen = (pp->getByteLength() - 4);
            for (unsigned int i = 0; i < datalen; i++)
                if (i < pp->getDataArraySize()) {
                    b.writeByte(pp->getData(i));
                }
                else {
                    b.writeByte('a');
                }
            break;
        }

        case ICMP_ECHO_REPLY: {
            PingPayload *pp = check_and_cast<PingPayload *>(pkt->getEncapsulatedPacket());
            b.writeByte(ICMP_ECHOREPLY);
            b.writeByte(pkt->getCode());
            b.writeUint16(0);   // crc
            b.writeUint16(pp->getOriginatorId());
            b.writeUint16(pp->getSeqNo());
            unsigned int datalen = pp->getDataArraySize();
            for (unsigned int i = 0; i < datalen; i++)
                b.writeByte(pp->getData(i));
            break;
        }

        case ICMP_DESTINATION_UNREACHABLE: {
            b.writeByte(ICMP_UNREACH);
            b.writeByte(pkt->getCode());
            b.writeUint16(0);   // crc
            b.writeUint16(0);   // unused
            b.writeUint16(0);   // next hop MTU
            SerializerBase::serialize(pkt->getEncapsulatedPacket(), b, c, ETHERTYPE, ETHERTYPE_IPv4, 0);
            break;
        }

        case ICMP_TIME_EXCEEDED: {
            b.writeByte(ICMP_TIMXCEED);
            b.writeByte(ICMP_TIMXCEED_INTRANS);
            b.writeUint16(0);   // crc
            b.writeUint32(0);   // unused
            SerializerBase::serialize(pkt->getEncapsulatedPacket(), b, c, ETHERTYPE, ETHERTYPE_IPv4, 0);
            break;
        }

        default: {
            throw cRuntimeError("Can not serialize ICMP packet: type %d  not supported.", pkt->getType());
        }
    }
    b.writeUint16To(startpos + 2, TCPIPchecksum::checksum(b._getBuf() + startpos, b.getPos() - startpos));
}

cPacket *ICMPSerializer::parse(const unsigned char *buf, unsigned int bufsize)
{
    Buffer b(const_cast<unsigned char *>(buf), bufsize);
    Context c;
    cPacket *pkt = parse(b, c);
    return pkt;
}

cPacket *ICMPSerializer::parse(Buffer &b, Context& context)
{
    ASSERT(b.getPos() == 0);

    ICMPMessage *pkt = new ICMPMessage("parsed-icmp");
    uint8_t type = b.readByte();     // type
    uint8_t subcode = b.readByte();  // subcode
    b.readUint16();   // crc

    switch (type) {
        case ICMP_ECHO: {
            PingPayload *pp = new PingPayload();
            pkt->setType(ICMP_ECHO_REQUEST);
            pkt->setCode(subcode);
            pkt->setByteLength(4);
            pp->setOriginatorId(b.readUint16());
            uint16_t seqno = b.readUint16();
            pp->setSeqNo(seqno);

            char name[32];
            sprintf(name, "parsed-ping%d", seqno);
            pp->setName(name);

            pp->setByteLength(4 + b.getRemainder());
            pp->setDataArraySize(b.getRemainder());
            for (unsigned int i = 0; b.getRemainder() > 0; i++)
                pp->setData(i, b.readByte());
            pkt->encapsulate(pp);
            pkt->setName(pp->getName());
            break;
        }

        case ICMP_ECHOREPLY: {
            PingPayload *pp = new PingPayload();

            b.readByte();     // subcode
            b.readUint16();   // crc
            pkt->setType(ICMP_ECHO_REPLY);
            pkt->setCode(subcode);
            pkt->setByteLength(4);
            pp->setOriginatorId(b.readUint16());
            uint16_t seqno = b.readUint16();

            char name[32];
            sprintf(name, "parsed-ping%d-reply", ntohs(seqno));
            pp->setName(name);

            pp->setByteLength(4 + b.getRemainder());
            pp->setDataArraySize(b.getRemainder());
            for (unsigned int i = 0; b.getRemainder() > 0; i++)
                pp->setData(i, b.readByte());
            pkt->encapsulate(pp);
            pkt->setName(pp->getName());
            break;
        }

        default: {
            EV_ERROR << "Can not parse ICMP packet: type " << type << " not supported.";
            delete pkt;
            return nullptr;
        }
    }
    uint16_t ccrc = TCPIPchecksum::checksum(b._getBuf(), b.getPos());
    if (ccrc)
        pkt->setBitError(true);
    return pkt;
}

} // namespace serializer

} // namespace inet

