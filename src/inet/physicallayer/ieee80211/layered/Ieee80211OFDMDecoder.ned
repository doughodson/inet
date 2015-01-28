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

package inet.physicallayer.ieee80211.layered;

import inet.physicallayer.contract.layered.IDecoder;
import inet.physicallayer.contract.layered.IFECCoder;
import inet.physicallayer.contract.layered.IInterleaver;
import inet.physicallayer.contract.layered.IScrambler;

module Ieee80211OFDMDecoder like IDecoder
{
    parameters:
        string fecType = default("");
        string deinterleaverType = default("");
        string descramblerType = default("");
        double channelSpacing @unit(Hz);
        @class(Ieee80211OFDMDecoderModule);

    submodules:
        descrambler: <descramblerType> like IScrambler if descramblerType != "" {
            @display("p=72,196");
        }
        fecDecoder: <fecType> like IFECCoder if fecType != "" {
            @display("p=72,106");
        }
        deinterleaver: <deinterleaverType> like IInterleaver if deinterleaverType != "" {
            @display("p=72,29");
        }
}
