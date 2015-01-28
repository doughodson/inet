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

#include "inet/physicallayer/ieee80211/layered/Ieee80211TimingRelatedParameters.h"

namespace inet {
namespace physicallayer {

Ieee80211TimingRelatedParameters::Ieee80211TimingRelatedParameters(Hz channelSpacing) : channelSpacing(channelSpacing)
{
    if (channelSpacing != Hz(20000000) && channelSpacing != Hz(10000000) && channelSpacing != Hz(5000000))
        throw cRuntimeError("Channel spacing %f is not supported by the OFDM PHY", channelSpacing.get());
}

}
}
