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

#include "Ieee80211OFDMCode.h"
#include "inet/physicallayer/modulation/BPSKModulation.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211OFDMDefs.h"

namespace inet {
namespace physicallayer {

const Ieee80211ConvolutionalCode* Ieee80211OFDMCode::computeFec(uint8_t rate) const
{
    // Table 18-6—Contents of the SIGNAL field
    // Table 18-4—Modulation-dependent parameters
    if (rate == 1101_b || rate == 0101_b || rate == 1001_b)
        return new Ieee80211ConvolutionalCode(1, 2);
    else if (rate == 1111_b || rate == 0111_b || rate == 1011_b || rate == 0111_b)
        return new Ieee80211ConvolutionalCode(3, 4);
    else if (rate == 0001_b)
        return new Ieee80211ConvolutionalCode(2, 3);
    else
        throw cRuntimeError("Unknown rate field  = %d", rate);
}

const Ieee80211Interleaving* Ieee80211OFDMCode::computeInterleaving(const IModulation *modulationScheme) const
{
    const IAPSKModulation *dataModulationScheme = dynamic_cast<const IAPSKModulation*>(modulationScheme);
    ASSERT(dataModulationScheme != NULL);
    return new Ieee80211Interleaving(dataModulationScheme->getCodeWordSize() * NUMBER_OF_OFDM_DATA_SUBCARRIERS, dataModulationScheme->getCodeWordSize()); // FIXME: memory leak
}

Ieee80211OFDMCode::Ieee80211OFDMCode(uint8_t signalFieldRate, Hz channelSpacing) :
        channelSpacing(channelSpacing)
{
    convCode = computeFec(signalFieldRate);
    Ieee80211OFDMModulation ofdmModulation(signalFieldRate, channelSpacing);
    interleaving = computeInterleaving(ofdmModulation.getModulationScheme());
    scrambling = computeScrambling();
}

const AdditiveScrambling* Ieee80211OFDMCode::computeScrambling() const
{
    // Default scrambling
    return new AdditiveScrambling("1011101", "0001001");
}

Ieee80211OFDMCode::Ieee80211OFDMCode(Hz channelSpacing) :
        channelSpacing(channelSpacing),
        scrambling(NULL)
{
    convCode = new Ieee80211ConvolutionalCode(1,2);
    interleaving = new Ieee80211Interleaving(NUMBER_OF_OFDM_DATA_SUBCARRIERS, 1);
}

Ieee80211OFDMCode::Ieee80211OFDMCode(const ConvolutionalCode* convCode, const Ieee80211Interleaving* interleaving, const AdditiveScrambling* scrambling, Hz channelSpacing) :
        channelSpacing(channelSpacing),
        convCode(convCode),
        interleaving(interleaving),
        scrambling(scrambling)
{
}

Ieee80211OFDMCode::~Ieee80211OFDMCode()
{
    delete convCode;
    delete interleaving;
    delete scrambling;
}

} /* namespace physicallayer */
} /* namespace inet */

