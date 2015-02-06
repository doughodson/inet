//
// Copyright (C) 2005 Christian Dankbar, Irene Ruengeler, Michael Tuexen, Andras Varga
// Copyright (C) 2009 Thomas Reschka
// Copyright (C) 2010 Zoltan Bojthe
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

#include <algorithm>    // std::min

#include "inet/common/serializer/ipv4/IPv4Serializer.h"

#include "inet/common/serializer/headers/in.h"
#include "inet/common/serializer/headers/in_systm.h"
#include "inet/common/serializer/ipv4/headers/ip.h"
#include "inet/common/serializer/ipv4/ICMPSerializer.h"
#include "inet/common/serializer/ipv4/IGMPSerializer.h"
#include "inet/linklayer/common/Ieee802Ctrl_m.h"
#include "inet/networklayer/common/IPProtocolId_m.h"

#ifdef WITH_UDP
#include "inet/common/serializer/udp/UDPSerializer.h"
#endif // ifdef WITH_UDP

#ifdef WITH_SCTP
#include "inet/common/serializer/sctp/SCTPSerializer.h"    //I.R.
#endif // ifdef WITH_SCTP

#include "inet/common/serializer/TCPIPchecksum.h"

#ifdef WITH_TCP_COMMON
#include "inet/transportlayer/tcp_common/TCPSegment.h"
#include "inet/common/serializer/tcp/TCPSerializer.h"    //I.R.
#endif // ifdef WITH_TCP_COMMON

#if defined(_MSC_VER)
#undef s_addr    /* MSVC #definition interferes with us */
#endif // if defined(_MSC_VER)

#if !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32) && !defined(__CYGWIN__) && !defined(_WIN64)
#include <netinet/in.h>    // htonl, ntohl, ...
#endif // if !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32) && !defined(__CYGWIN__) && !defined(_WIN64)

// This in_addr field is defined as a macro in Windows and Solaris, which interferes with us
#undef s_addr

namespace inet {

namespace serializer {

Register_Serializer(IPv4Datagram, ETHERTYPE, ETHERTYPE_IPv4, IPv4Serializer);

void IPv4Serializer::serialize(const cPacket *pkt, Buffer &b, Context& context)
{
    b.seek(serialize(check_and_cast<const IPv4Datagram *>(pkt), b._getBuf(), b._getBufSize(), true));
}

int IPv4Serializer::serialize(const IPv4Datagram *dgram, unsigned char *buf, unsigned int bufsize, bool hasCalcChkSum)
{
    Context c;
    int packetLength;
    struct ip *ip = (struct ip *)buf;

    ip->ip_hl = IP_HEADER_BYTES >> 2;
    ip->ip_v = dgram->getVersion();
    ip->ip_tos = dgram->getTypeOfService();
    ip->ip_id = htons(dgram->getIdentification());
    uint16_t ip_off = dgram->getFragmentOffset() / 8;
    if (dgram->getMoreFragments())
        ip_off |= IP_MF;
    if (dgram->getDontFragment())
        ip_off |= IP_DF;
    ip->ip_off = htons(ip_off);
    ip->ip_ttl = dgram->getTimeToLive();
    ip->ip_p = dgram->getTransportProtocol();
    ip->ip_src.s_addr = htonl(dgram->getSrcAddress().getInt());
    ip->ip_dst.s_addr = htonl(dgram->getDestAddress().getInt());
    ip->ip_sum = 0;
    c.l3AddressesPtr = &ip->ip_src.s_addr;
    c.l3AddressesLength = sizeof(ip->ip_src.s_addr) + sizeof(ip->ip_dst.s_addr);

    if (dgram->getHeaderLength() > IP_HEADER_BYTES)
        EV_ERROR << "Serializing an IPv4 packet with options. Dropping the options.\n";

    packetLength = dgram->getHeaderLength();

    const cPacket *encapPacket = dgram->getEncapsulatedPacket();
    Buffer subBuffer(buf + packetLength, bufsize - packetLength);
    SerializerBase::serialize(encapPacket, subBuffer, c, IP_PROT, dgram->getTransportProtocol(), 0);
    packetLength += subBuffer.getPos();

    ip->ip_len = htons(packetLength);
    ip->ip_sum = TCPIPchecksum::checksum(buf, IP_HEADER_BYTES);

    return packetLength;
}

cPacket* IPv4Serializer::parse(Buffer &b, Context& c)
{
    IPv4Datagram *dest = new IPv4Datagram("parsed-ipv4");
    unsigned int bufsize = b.getRemainder();
    struct ip *ip = static_cast<struct ip *>(b.accessNBytes(sizeof(struct ip)));
    if (!ip ) {
        delete dest;
        return nullptr;
    }
    unsigned int totalLength, headerLength;
    c.l3AddressesPtr = &ip->ip_src.s_addr;
    c.l3AddressesLength = sizeof(ip->ip_src.s_addr) + sizeof(ip->ip_dst.s_addr);

    dest->setVersion(ip->ip_v);
    dest->setHeaderLength(IP_HEADER_BYTES);
    dest->setSrcAddress(IPv4Address(ntohl(ip->ip_src.s_addr)));
    dest->setDestAddress(IPv4Address(ntohl(ip->ip_dst.s_addr)));
    dest->setTransportProtocol(ip->ip_p);
    dest->setTimeToLive(ip->ip_ttl);
    dest->setIdentification(ntohs(ip->ip_id));
    uint16_t ip_off = ntohs(ip->ip_off);
    dest->setMoreFragments((ip_off & IP_MF) != 0);
    dest->setDontFragment((ip_off & IP_DF) != 0);
    dest->setFragmentOffset((ntohs(ip->ip_off) & IP_OFFMASK) * 8);
    dest->setTypeOfService(ip->ip_tos);
    totalLength = ntohs(ip->ip_len);
    headerLength = ip->ip_hl << 2;

    if (TCPIPchecksum::checksum(ip, IP_HEADER_BYTES) != 0)
        dest->setBitError(true);

    if (headerLength > sizeof(struct ip)) {
        EV_ERROR << "Handling a captured IPv4 packet with options. Dropping the options.\n";
    }
    b.seek(headerLength);

    if (totalLength > bufsize)
        EV << "Can not handle IPv4 packet of total length " << totalLength << "(captured only " << bufsize << " bytes).\n";

    dest->setByteLength(IP_HEADER_BYTES);

    cPacket *encapPacket = SerializerBase::parse(b, c, IP_PROT, dest->getTransportProtocol(), 0);

    ASSERT(encapPacket);
    dest->encapsulate(encapPacket);
    dest->setName(encapPacket->getName());
    return dest;
}

} // namespace serializer

} // namespace inet

