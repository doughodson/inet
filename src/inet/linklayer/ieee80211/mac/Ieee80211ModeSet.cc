// Copyright (C) 2012 OpenSim Ltd
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
// @author: Zoltan Bojthe
//

#include "inet/linklayer/ieee80211/mac/Ieee80211ModeSet.h"

namespace inet {

namespace ieee80211 {

using namespace inet::physicallayer;

const std::vector<Ieee80211ModeSet> Ieee80211ModeSet::modeSets = {
    Ieee80211ModeSet('a', {
        Ieee80211Mode(true, Ieee80211PhyMode::GetOfdmRate6Mbps()),
        Ieee80211Mode(false, Ieee80211PhyMode::GetOfdmRate9Mbps()),
        Ieee80211Mode(true, Ieee80211PhyMode::GetOfdmRate12Mbps()),
        Ieee80211Mode(false, Ieee80211PhyMode::GetOfdmRate18Mbps()),
        Ieee80211Mode(true, Ieee80211PhyMode::GetOfdmRate24Mbps()),
        Ieee80211Mode(false, Ieee80211PhyMode::GetOfdmRate36Mbps()),
        Ieee80211Mode(false, Ieee80211PhyMode::GetOfdmRate48Mbps()),
        Ieee80211Mode(false, Ieee80211PhyMode::GetOfdmRate54Mbps()),
    }),
    Ieee80211ModeSet('b', {
        Ieee80211Mode(true, Ieee80211PhyMode::GetDsssRate1Mbps()),
        Ieee80211Mode(true, Ieee80211PhyMode::GetDsssRate2Mbps()),
        Ieee80211Mode(true, Ieee80211PhyMode::GetDsssRate5_5Mbps()),
        Ieee80211Mode(true, Ieee80211PhyMode::GetDsssRate11Mbps()),
    }),
    Ieee80211ModeSet('g', {
        Ieee80211Mode(true, Ieee80211PhyMode::GetDsssRate1Mbps()),
        Ieee80211Mode(true, Ieee80211PhyMode::GetDsssRate2Mbps()),
        Ieee80211Mode(true, Ieee80211PhyMode::GetDsssRate5_5Mbps()),
        Ieee80211Mode(true, Ieee80211PhyMode::GetErpOfdmRate6Mbps()),
        Ieee80211Mode(false, Ieee80211PhyMode::GetErpOfdmRate9Mbps()),
        Ieee80211Mode(true, Ieee80211PhyMode::GetDsssRate11Mbps()),
        Ieee80211Mode(true, Ieee80211PhyMode::GetErpOfdmRate12Mbps()),
        Ieee80211Mode(false, Ieee80211PhyMode::GetErpOfdmRate18Mbps()),
        Ieee80211Mode(true, Ieee80211PhyMode::GetErpOfdmRate24Mbps()),
        Ieee80211Mode(false, Ieee80211PhyMode::GetErpOfdmRate36Mbps()),
        Ieee80211Mode(false, Ieee80211PhyMode::GetErpOfdmRate48Mbps()),
        Ieee80211Mode(false, Ieee80211PhyMode::GetErpOfdmRate54Mbps()),
    }),
    Ieee80211ModeSet('p', {
        Ieee80211Mode(true, Ieee80211PhyMode::GetOfdmRate3MbpsCS10MHz()),
        Ieee80211Mode(false, Ieee80211PhyMode::GetOfdmRate4_5MbpsCS10MHz()),
        Ieee80211Mode(true, Ieee80211PhyMode::GetOfdmRate6MbpsCS10MHz()),
        Ieee80211Mode(false, Ieee80211PhyMode::GetOfdmRate9MbpsCS10MHz()),
        Ieee80211Mode(true, Ieee80211PhyMode::GetOfdmRate12MbpsCS10MHz()),
        Ieee80211Mode(false, Ieee80211PhyMode::GetOfdmRate18MbpsCS10MHz()),
        Ieee80211Mode(false, Ieee80211PhyMode::GetOfdmRate24MbpsCS10MHz()),
        Ieee80211Mode(false, Ieee80211PhyMode::GetOfdmRate27MbpsCS10MHz()),
    }),
};

Ieee80211ModeSet::Ieee80211ModeSet(char name, const std::vector<Ieee80211Mode> modes) :
    name(name),
    modes(modes)
{
}

int Ieee80211ModeSet::getModeIndex(const Ieee80211Mode *mode) const
{
    for (int index = 0; index < (int)modes.size(); index++) {
        if (modes[index].getPhyMode()->getDataRate() == mode->getPhyMode()->getDataRate())
            return index;
    }
    return -1;
}

const Ieee80211Mode *Ieee80211ModeSet::getMode(bps bitrate) const
{
    for (int index = 0; index < (int)modes.size(); index++) {
        if (modes[index].getPhyMode()->getDataRate() == bitrate)
            return &modes[index];
    }
    return nullptr;
}

const Ieee80211Mode *Ieee80211ModeSet::getSlowestMode() const
{
    return &modes.front();
}

const Ieee80211Mode *Ieee80211ModeSet::getFastestMode() const
{
    return &modes.back();
}

const Ieee80211Mode *Ieee80211ModeSet::getSlowerMode(const Ieee80211Mode *mode) const
{
    int index = getModeIndex(mode);
    if (index > 0)
        return &modes[index - 1];
    else
        return nullptr;
}

const Ieee80211Mode *Ieee80211ModeSet::getFasterMode(const Ieee80211Mode *mode) const
{
    int index = getModeIndex(mode);
    if (index < (int)modes.size() - 1)
        return &modes[index + 1];
    else
        return nullptr;
}

const Ieee80211ModeSet *Ieee80211ModeSet::getModeSet(char mode) {
    for (int index = 0; index < (int)Ieee80211ModeSet::modeSets.size(); index++) {
        const Ieee80211ModeSet *modeSet = &Ieee80211ModeSet::modeSets[index];
        if (modeSet->getName() == mode)
            return modeSet;
    }
    return nullptr;
}

} // namespace ieee80211

} // namespace inet

