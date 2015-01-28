//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef __INET_IEEE80211OFDMMODULATION_H
#define __INET_IEEE80211OFDMMODULATION_H

#include "inet/physicallayer/contract/IModulation.h"
#include "inet/physicallayer/base/APSKModulationBase.h"
#include "inet/common/Units.h"
#include "inet/common/INETUtils.h"

namespace inet {
namespace physicallayer {

using namespace units::values;
using namespace utils;

class INET_API Ieee80211OFDMModulation : public IModulation
{
    protected:
        const APSKModulationBase *modulationScheme;
        uint8_t signalRateField;
        Hz channelSpacing;
        bps bitrate;
        simtime_t slotTime; // todo
        simtime_t symbolDuration; // todo
        simtime_t guardInterval; // todo

    protected:
        const APSKModulationBase* computeModulation(uint8_t rate) const;
        bps computeDataBitrate(uint8_t rate, Hz channelSpacing) const;
        bps computeHeaderBitrate(Hz channelSpacing) const;
        uint8_t calculateRateField(Hz channelSpacing, bps bitrate) const;
        simtime_t computeSlotTime(Hz channelSpacing) const;
        simtime_t computeSymbolDuration(Hz channelSpacing) const;
        simtime_t computeGuardInterval(Hz channelSpacing) const;

    public:
        virtual void printToStream(std::ostream& stream) const { stream << "Ieee80211OFDMModulation"; }
        virtual double calculateBER(double snir, Hz bandwidth, bps bitrate) const { return modulationScheme->calculateBER(snir, bandwidth, bitrate); }
        virtual double calculateSER(double snir, Hz bandwidth, bps bitrate) const { return modulationScheme->calculateSER(snir, bandwidth, bitrate); }
        virtual Hz getChannelSpacing() const { return channelSpacing; }
        const bps getBitrate() const { return bitrate; }
        uint8_t getSignalRateField() const { return signalRateField; }
        const APSKModulationBase* getModulationScheme() const { return modulationScheme; }
        Ieee80211OFDMModulation(Hz channelSpacing); // header
        Ieee80211OFDMModulation(uint8_t signalRateField, Hz channelSpacing); // data
        Ieee80211OFDMModulation(bps dataRate, Hz channelSpacing); // data
};

} /* namespace physicallayer */
} /* namespace inet */

#endif /* __INET_IEEE80211OFDMMODULATION_H */
