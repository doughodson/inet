//
// Copyright (C) 2015 OpenSim Ltd.
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

#ifndef __INET_IEEE80211TIMINGRELATEDPARAMETERS_H
#define __INET_IEEE80211TIMINGRELATEDPARAMETERS_H

#include "inet/common/INETDefs.h"
#include "inet/common/Units.h"

namespace inet {
namespace physicallayer {

using namespace units::values;

/*
 * Reference: 18.3.2.4 Timing related parameters
 */
class INET_API Ieee80211TimingRelatedParameters
{
    protected:
        Hz channelSpacing;

    public:
        Ieee80211TimingRelatedParameters(Hz channelSpacing);

        int getNumberOfDataSubcarriers() const { return 48; }
        int getNumberOfPilotSubcarriers() const { return 4; }
        int getNumberOfTotalSubcarriers() const { return getNumberOfDataSubcarriers() + getNumberOfPilotSubcarriers(); }
        Hz getChannelSpacing() const { return channelSpacing; }
        Hz getSubcarrierFrequencySpacing() const { return channelSpacing / 64; }
        simtime_t getFFTTransformPeriod() const { return simtime_t(1 / getSubcarrierFrequencySpacing().get()); }
        simtime_t getPreambleDuration() const { return getShortTrainingSequenceDuration() + getLongTrainingSequenceDuration(); }
        simtime_t getSignalDuration() const { return getSymbolInterval(); }
        simtime_t getGIDuration() const { return getFFTTransformPeriod() / 4; }
        simtime_t getTrainingSymbolGIDuration() const { return getFFTTransformPeriod() / 2; }
        simtime_t getSymbolInterval() const { return getGIDuration() + getFFTTransformPeriod(); }
        simtime_t getShortTrainingSequenceDuration() const { return 10 * getFFTTransformPeriod() / 4; }
        simtime_t getLongTrainingSequenceDuration() const { return getTrainingSymbolGIDuration() + 2 * getFFTTransformPeriod(); }
};

} /* namespace physicallayer */
} /* namespace inet */

#endif // ifndef __INET_IEEE80211TIMINGRELATEDPARAMETERS_H
