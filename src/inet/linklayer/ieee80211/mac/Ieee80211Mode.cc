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

#include "inet/linklayer/ieee80211/mac/Ieee80211Mode.h"

namespace inet {

namespace ieee80211 {

Ieee80211Mode::Ieee80211Mode(bool isMandatory, const Ieee80211PhyMode phyMode) :
    isMandatory(isMandatory),
    phyMode(phyMode)
{
}

} // namespace ieee80211

} // namespace inet

