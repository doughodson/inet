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

#ifndef __INET_IEEE80211OFDMMODULATOR_H
#define __INET_IEEE80211OFDMMODULATOR_H

#include "inet/physicallayer/contract/layered/IModulator.h"
#include "inet/physicallayer/common/layered/SignalBitModel.h"
#include "inet/physicallayer/common/layered/SignalSymbolModel.h"
#include "inet/physicallayer/base/APSKModulationBase.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211OFDMSymbol.h"
#include "inet/physicallayer/ieee80211/Ieee80211OFDMModulation.h"

namespace inet {

namespace physicallayer {

class INET_API Ieee80211OFDMModulator : public IModulator
{
  protected:
    const Ieee80211OFDMModulation *ofdmModulation;
    const APSKModulationBase *modulationScheme;
    static const int polarityVector[127];

  protected:
    int getSubcarrierIndex(int ofdmSymbolIndex) const;
    void insertPilotSubcarriers(Ieee80211OFDMSymbol *ofdmSymbol, int symbolID) const;

  public:
    virtual const ITransmissionSymbolModel *modulate(const ITransmissionBitModel *bitModel) const;
    const IModulation *getModulationScheme() const { return modulationScheme; }
    const Ieee80211OFDMModulation *getOFDMModulation() const { return ofdmModulation; }
    void printToStream(std::ostream& stream) const { stream << "Ieee80211OFDMModulator"; }
    Ieee80211OFDMModulator(const Ieee80211OFDMModulation *ofdmModulation);
    Ieee80211OFDMModulator(const APSKModulationBase *modulationScheme);
    ~Ieee80211OFDMModulator();
};

} // namespace physicallayer
} // namespace inet

#endif /* __INET_IEEE80211OFDMMODULATOR_H */
