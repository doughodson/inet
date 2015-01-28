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

#ifndef __INET_IEEE80211OFDMCODE_H
#define __INET_IEEE80211OFDMCODE_H

#include "inet/common/INETDefs.h"
#include "inet/common/Units.h"
#include "inet/physicallayer/ieee80211/Ieee80211OFDMModulation.h"
#include "inet/physicallayer/contract/IModulation.h"
#include "inet/physicallayer/common/layered/AdditiveScrambling.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211Interleaving.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211ConvolutionalCode.h"

namespace inet {
namespace physicallayer {

using namespace units::values;

class INET_API Ieee80211OFDMCode
{
    protected:
        Hz channelSpacing;
        const ConvolutionalCode *convCode;
        const Ieee80211Interleaving *interleaving;
        const AdditiveScrambling *scrambling;

    protected:
        const Ieee80211ConvolutionalCode *computeFec(uint8_t rate) const;
        const Ieee80211Interleaving *computeInterleaving(const IModulation *modulationScheme) const;
        const AdditiveScrambling *computeScrambling() const;

    public:
        const ConvolutionalCode *getConvCode() const { return convCode; }
        const Ieee80211Interleaving *getInterleaving() const { return interleaving; }
        const AdditiveScrambling *getScrambling() const { return scrambling; }
        const Hz getChannelSpacing() const { return channelSpacing; }

        Ieee80211OFDMCode(Hz channelSpacing);
        Ieee80211OFDMCode(uint8_t signalFieldRate, Hz channelSpacing);
        Ieee80211OFDMCode(const ConvolutionalCode *convCode, const Ieee80211Interleaving *interleaving, const AdditiveScrambling *scrambling, Hz channelSpacing);
        ~Ieee80211OFDMCode();
};

} /* namespace physicallayer */
} /* namespace inet */

#endif /* __INET_IEEE80211OFDMCODE_H */
