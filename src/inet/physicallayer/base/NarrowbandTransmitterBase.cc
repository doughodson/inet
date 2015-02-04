//
// Copyright (C) 2013 OpenSim Ltd.
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

#include "inet/physicallayer/base/NarrowbandTransmitterBase.h"
#include "inet/physicallayer/base/APSKModulationBase.h"

namespace inet {

namespace physicallayer {

NarrowbandTransmitterBase::NarrowbandTransmitterBase() :
    modulation(nullptr),
    headerBitLength(-1),
    carrierFrequency(Hz(sNaN)),
    bandwidth(Hz(sNaN)),
    bitrate(sNaN),
    power(W(sNaN))
{
}

NarrowbandTransmitterBase::~NarrowbandTransmitterBase()
{
}

void NarrowbandTransmitterBase::initialize(int stage)
{
    TransmitterBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        modulation = APSKModulationBase::findModulation(par("modulation"));
        headerBitLength = par("headerBitLength");
        carrierFrequency = Hz(par("carrierFrequency"));
        bandwidth = Hz(par("bandwidth"));
        bitrate = bps(par("bitrate"));
        power = W(par("power"));
    }
}

void NarrowbandTransmitterBase::printToStream(std::ostream& stream) const
{
    stream << "modulation = { " << modulation << " }, "
           << "headerBitLength = " << headerBitLength << ", "
           << "carrierFrequency = " << carrierFrequency << ", "
           << "bandwidth = " << bandwidth << ", "
           << "bitrate = " << bitrate << ", "
           << "power = " << power;
}

} // namespace physicallayer

} // namespace inet

