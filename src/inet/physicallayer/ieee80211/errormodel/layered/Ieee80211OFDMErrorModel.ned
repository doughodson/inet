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

package inet.physicallayer.ieee80211.errormodel.layered;

import inet.physicallayer.contract.layered.ILayeredErrorModel;


module Ieee80211OFDMErrorModel like ILayeredErrorModel
{
    parameters:
        double dataSymbolErrorRate = default(0/0);
        double dataBitErrorRate = default(0/0);
        double signalSymbolErrorRate = default(0/0);
        double signalBitErrorRate = default(0/0);
        @class(Ieee80211OFDMErrorModel);
}
