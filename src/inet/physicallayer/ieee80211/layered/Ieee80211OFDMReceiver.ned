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

package inet.physicallayer.ieee80211.layered;

import inet.physicallayer.contract.IReceiver;
import inet.physicallayer.contract.layered.IAnalogDigitalConverter;
import inet.physicallayer.contract.layered.IDecoder;
import inet.physicallayer.contract.layered.IDemodulator;
import inet.physicallayer.contract.layered.ILayeredErrorModel;
import inet.physicallayer.contract.layered.IPulseFilter;

module Ieee80211OFDMReceiver like IReceiver
{
    parameters:
        bool isCompliant = default(true);
        string levelOfDetail @enum("bit","symbol","sample") = default("symbol");
        string errorModelType = default("");
        string signalDecoderType = default("");
        string decoderType = default("");
        string signalDemodulation = default("");
        string signalDemodulatorType = default("");
        string dataDemodulation = default("");
        string demodulatorType = default("");
        string shaperFilterType = default("");
        string analogDigitalConverterType = default("");
        double energyDetection @unit(dBm); // TODO: @unit(W) + dBm/dBW <--> W
        double sensitivity @unit(dBm); // TODO: @unit(W) + dBm/dBW <--> W
        double carrierFrequency @unit(Hz);
        double bandwidth @unit(Hz);
        double snirThreshold @unit(dB);
        double channelSpacing @unit(Hz);
        **.channelSpacing = channelSpacing;
        demodulator.modulationScheme = dataDemodulation;
        signalDemodulator.modulationScheme = signalDemodulation;
        @class(Ieee80211OFDMReceiver);

    submodules:
        errorModel: <errorModelType> like ILayeredErrorModel if errorModelType != "" {
            @display("p=240,350");
        }
        decoder: <decoderType> like IDecoder if decoderType != "" {
            @display("p=100,50");
        }
        signalDecoder: <signalDecoderType> like IDecoder if signalDecoderType != "" {
            @display("p=229,50");
        }
        signalDemodulator: <signalDemodulatorType> like IDemodulator if signalDemodulatorType != "" {
            @display("p=229,150");
        }
        demodulator: <demodulatorType> like IDemodulator if demodulatorType != "" {
            @display("p=100,150");
        }
        shaperFilter: <shaperFilterType> like IPulseFilter if shaperFilterType != "" {
            @display("p=100,250");
        }
        analogDigitalConverter: <analogDigitalConverterType> like IAnalogDigitalConverter if analogDigitalConverterType != "" {
            @display("p=100,350");
        }
}
