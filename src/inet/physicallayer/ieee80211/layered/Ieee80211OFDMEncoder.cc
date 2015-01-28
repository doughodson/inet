//
// Copyright (C) 2014 OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "inet/physicallayer/ieee80211/layered/Ieee80211OFDMEncoder.h"
#include "inet/common/ShortBitVector.h"
#include "inet/physicallayer/modulation/BPSKModulation.h"
#include "inet/physicallayer/modulation/QPSKModulation.h"
#include "inet/physicallayer/modulation/QAM16Modulation.h"
#include "inet/physicallayer/modulation/QAM64Modulation.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211Interleaver.h"
#include "inet/physicallayer/ieee80211/Ieee80211OFDMModulation.h"
#include "inet/physicallayer/common/layered/AdditiveScrambler.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211Interleaver.h"
#include "inet/physicallayer/common/layered/ConvolutionalCoder.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211OFDMDefs.h"

namespace inet {
namespace physicallayer {

const ITransmissionBitModel* Ieee80211OFDMEncoder::encode(const ITransmissionPacketModel* packetModel) const
{
    const BitVector *serializedPacket = packetModel->getSerializedPacket();
    BitVector *encodedBits = new BitVector(*serializedPacket);
    const IScrambling *scrambling = NULL;
    if (scrambler)
    {
        *encodedBits = scrambler->scramble(*encodedBits);
        scrambling = scrambler->getScrambling();
        EV_DEBUG << "Scrambled bits are: " << *encodedBits << endl;
    }
    const IForwardErrorCorrection *forwardErrorCorrection = NULL;
    if (fecEncoder)
    {
        *encodedBits = fecEncoder->encode(*encodedBits);
        forwardErrorCorrection = fecEncoder->getForwardErrorCorrection();
        EV_DEBUG << "FEC encoded bits are: " << *encodedBits << endl;
    }
    const IInterleaving *interleaving = NULL;
    if (interleaver)
    {
        *encodedBits = interleaver->interleave(*encodedBits);
        interleaving = interleaver->getInterleaving();
        EV_DEBUG << "Interleaved bits are: " << *encodedBits << endl;
    }
    return new TransmissionBitModel(encodedBits, forwardErrorCorrection, scrambling, interleaving);
}

Ieee80211OFDMEncoder::Ieee80211OFDMEncoder(const Ieee80211OFDMCode *code) :
        fecEncoder(NULL),
        interleaver(NULL),
        scrambler(NULL),
        code(code)
{
    channelSpacing = code->getChannelSpacing();
    if (code->getScrambling())
        scrambler = new AdditiveScrambler(code->getScrambling());
    if (code->getInterleaving())
        interleaver = new Ieee80211Interleaver(code->getInterleaving());
    if (code->getConvCode())
        fecEncoder = new ConvolutionalCoder(code->getConvCode());
}

Ieee80211OFDMEncoder::Ieee80211OFDMEncoder(const IFECCoder* fecEncoder, const IInterleaver* interleaver, const IScrambler* scrambler, Hz channelSpacing) :
        fecEncoder(fecEncoder),
        interleaver(interleaver),
        scrambler(scrambler),
        channelSpacing(channelSpacing)
{
    const ConvolutionalCode *fec = NULL;
    if (fecEncoder)
        fec = check_and_cast<const ConvolutionalCode *>(fecEncoder->getForwardErrorCorrection());
    const Ieee80211Interleaving *interleaving = NULL;
    if (interleaver)
        interleaving = check_and_cast<const Ieee80211Interleaving *>(interleaver->getInterleaving());
    const AdditiveScrambling *scrambling = NULL;
    if (scrambler)
        scrambling = check_and_cast<const AdditiveScrambling *>(scrambler->getScrambling());
    code = new Ieee80211OFDMCode(fec, interleaving, scrambling, channelSpacing);
}

Ieee80211OFDMEncoder::Ieee80211OFDMEncoder() :
        fecEncoder(NULL),
        interleaver(NULL),
        scrambler(NULL),
        code(NULL),
        channelSpacing(NaN)
{
}

Ieee80211OFDMEncoder::~Ieee80211OFDMEncoder()
{
    delete fecEncoder;
    delete interleaver;
    delete scrambler;
    delete code;
}

} /* namespace physicallayer */
} /* namespace inet */

