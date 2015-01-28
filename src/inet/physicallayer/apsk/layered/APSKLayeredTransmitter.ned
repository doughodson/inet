//
// Copyright (C) 2014 OpenSim Ltd
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

package inet.physicallayer.apsk.layered;

import inet.physicallayer.contract.ITransmitter;
import inet.physicallayer.contract.layered.IDigitalAnalogConverter;
import inet.physicallayer.contract.layered.IEncoder;
import inet.physicallayer.contract.layered.IModulator;
import inet.physicallayer.contract.layered.IPulseShaper;

module APSKLayeredTransmitter like ITransmitter
{
    parameters:
        string levelOfDetail @enum("packet","bit","symbol","sample") = default("symbol");
        string encoderType = default("");
        string modulatorType = default("");
        string pulseShaperType = default("");
        string digitalAnalogConverterType = default("");
        string modulation;
        double bitrate @unit(bps);
        double power @unit(W);
        double carrierFrequency @unit(Hz);
        double bandwidth @unit(Hz);
        *.bitrate = bitrate;
        *.modulation = modulation;
        @display("i=block/wtx");
        @class(APSKLayeredTransmitter);

    submodules:
        encoder: <encoderType> like IEncoder if encoderType != "" {
            @display("p=100,50");
        }
        modulator: <modulatorType> like IModulator if modulatorType != "" {
            @display("p=100,150");
        }
        pulseShaper: <pulseShaperType> like IPulseShaper if pulseShaperType != "" {
            @display("p=100,250");
        }
        digitalAnalogConverter: <digitalAnalogConverterType> like IDigitalAnalogConverter if digitalAnalogConverterType != "" {
            @display("p=100,350");
        }
}
