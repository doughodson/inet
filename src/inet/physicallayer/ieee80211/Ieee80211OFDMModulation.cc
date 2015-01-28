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

#include "Ieee80211OFDMModulation.h"
#include "inet/physicallayer/modulation/BPSKModulation.h"
#include "inet/physicallayer/modulation/QPSKModulation.h"
#include "inet/physicallayer/modulation/QAM16Modulation.h"
#include "inet/physicallayer/modulation/QAM64Modulation.h"

namespace inet {
namespace physicallayer {

const APSKModulationBase* Ieee80211OFDMModulation::computeModulation(uint8_t rate) const
{
    // Table 18-6—Contents of the SIGNAL field
    // Table 18-4—Modulation-dependent parameters
    if (rate == 1101_b || rate == 1111_b)
        return &BPSKModulation::singleton;
    else if (rate == 0101_b || rate == 0111_b)
        return &QPSKModulation::singleton;
    else if (rate == 1001_b || rate == 1011_b)
        return &QAM16Modulation::singleton;
    else if(rate == 0001_b || rate == 0011_b)
        return &QAM64Modulation::singleton;
    else
        throw cRuntimeError("Unknown rate field = %d", rate);
}

bps Ieee80211OFDMModulation::computeHeaderBitrate(Hz channelSpacing) const
{
    // TODO: Revise, these are the minimum bitrates for each channel spacing.
    if (channelSpacing == MHz(20))
        return bps(6000000);
    else if (channelSpacing == MHz(10))
        return bps(3000000);
    else if (channelSpacing == MHz(5))
        return bps(1500000);
    else
        throw cRuntimeError("Invalid channel spacing %lf", channelSpacing.get());
}

simtime_t Ieee80211OFDMModulation::computeSlotTime(Hz channelSpacing) const
{
//    The slot time for the OFDM PHY shall be 9 μ s for 20 MHz channel spacing, shall be 13 μs for 10 MHz
//    channel spacing, and shall be 21 μs for 5 MHz channel spacing.
    if (channelSpacing == MHz(20))
        return 9.0 / 1000000.0;
    else if (channelSpacing == MHz(10))
        return 13.0 / 1000000.0;
    else if (channelSpacing == MHz(5))
        return 21.0 / 1000000.0;
    else
        throw cRuntimeError("Unknown channel spacing = %lf", channelSpacing);
}

simtime_t Ieee80211OFDMModulation::computeSymbolDuration(Hz channelSpacing) const
{
    // Table 18-12—Major parameters of the OFDM PHY
    if (channelSpacing == MHz(20))
        return 4.0 / 1000000.0;
    else if (channelSpacing == MHz(10))
        return 8.0 / 1000000.0;
    else if (channelSpacing == MHz(5))
        return 16.0 / 1000000.0;
    else
        throw cRuntimeError("Unknown channel spacing = %lf", channelSpacing);
}

simtime_t Ieee80211OFDMModulation::computeGuardInterval(Hz channelSpacing) const
{
    // Table 18-12—Major parameters of the OFDM PHY
    if (channelSpacing == MHz(20))
        return 0.8 / 1000000.0;
    else if (channelSpacing == MHz(10))
        return 1.6 / 1000000.0;
    else if (channelSpacing == MHz(5))
        return 3.2 / 1000000.0;
    else
        throw cRuntimeError("Unknown channel spacing = %lf", channelSpacing);
}

uint8_t Ieee80211OFDMModulation::calculateRateField(Hz channelSpacing, bps bitrate) const
{
    double rateFactor;
    if (channelSpacing == MHz(20))
        rateFactor = 1;
    else if (channelSpacing == MHz(10))
        rateFactor = 0.5;
    else if (channelSpacing == MHz(5))
        rateFactor = 0.25;
    else
        throw cRuntimeError("Unknown channel spacing = %lf", channelSpacing);
    if (bitrate == bps(6000000 * rateFactor))
        return 1101_b;
    else if (bitrate == bps(9000000 * rateFactor))
        return 1111_b;
    else if (bitrate == bps(12000000 * rateFactor))
        return 0101_b;
    else if (bitrate == bps(18000000 * rateFactor))
        return 0111_b;
    else if (bitrate == bps(24000000 * rateFactor))
        return 1001_b;
    else if (bitrate == bps(36000000 * rateFactor))
        return 1011_b;
    else if (bitrate == bps(48000000 * rateFactor))
        return 0001_b;
    else if (bitrate == bps(54000000 * rateFactor))
        return 0011_b;
    else
        throw cRuntimeError("%lf Hz channel spacing does not support %lf bps bitrate", channelSpacing.get(), bitrate.get());
}

bps Ieee80211OFDMModulation::computeDataBitrate(uint8_t rate, Hz channelSpacing) const
{
    double rateFactor;
    if (channelSpacing == MHz(20))
        rateFactor = 1;
    else if (channelSpacing == MHz(10))
        rateFactor = 0.5;
    else if (channelSpacing == MHz(5))
        rateFactor = 0.25;
    else
        throw cRuntimeError("Unknown channel spacing = %lf", channelSpacing);
    if (rate == 1101_b)
        return bps(6000000 * rateFactor);
    else if (rate == 1111_b)
        return bps(9000000 * rateFactor);
    else if (rate == 0101_b)
        return bps(12000000 * rateFactor);
    else if (rate == 0111_b)
        return bps(18000000 * rateFactor);
    else if (rate == 1001_b)
        return bps(24000000 * rateFactor);
    else if (rate == 1011_b)
        return bps(36000000 * rateFactor);
    else if (rate == 0001_b)
        return bps(48000000 * rateFactor);
    else if (rate == 0011_b)
        return bps(54000000 * rateFactor);
    else
        throw cRuntimeError("Invalid rate field: %d", rate);
}


Ieee80211OFDMModulation::Ieee80211OFDMModulation(uint8_t signalRateField, Hz channelSpacing) :
        signalRateField(signalRateField),
        channelSpacing(channelSpacing)
{
    modulationScheme = computeModulation(signalRateField);
    bitrate = computeDataBitrate(signalRateField, channelSpacing);
    slotTime = computeSlotTime(channelSpacing);
    symbolDuration = computeSymbolDuration(channelSpacing);
    guardInterval = computeGuardInterval(channelSpacing);
}

Ieee80211OFDMModulation::Ieee80211OFDMModulation(bps dataRate, Hz channelSpacing) :
        channelSpacing(channelSpacing),
        bitrate(dataRate)
{
    signalRateField = calculateRateField(channelSpacing, dataRate);
    modulationScheme = computeModulation(signalRateField);
    slotTime = computeSlotTime(channelSpacing);
    symbolDuration = computeSymbolDuration(channelSpacing);
    guardInterval = computeGuardInterval(channelSpacing);
}

Ieee80211OFDMModulation::Ieee80211OFDMModulation(Hz channelSpacing) :
        channelSpacing(channelSpacing)
{
    bitrate = computeHeaderBitrate(channelSpacing);
    modulationScheme = &BPSKModulation::singleton;
    signalRateField = 0;
    slotTime = computeSlotTime(channelSpacing);
    symbolDuration = computeSymbolDuration(channelSpacing);
    guardInterval = computeGuardInterval(channelSpacing);
}

} /* namespace physicallayer */
} /* namespace inet */
