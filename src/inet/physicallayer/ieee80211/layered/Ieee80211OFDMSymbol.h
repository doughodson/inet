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

#ifndef __INET_OFDMSYMBOL_H
#define __INET_OFDMSYMBOL_H

#include "inet/physicallayer/contract/layered/ISymbol.h"
#include "inet/physicallayer/apsk/layered/APSKSymbol.h"

namespace inet {
namespace physicallayer {

class INET_API Ieee80211OFDMSymbol : public ISymbol
{
    protected:
        std::vector<const APSKSymbol *> subcarrierSymbols;

    public:
        Ieee80211OFDMSymbol(const Ieee80211OFDMSymbol& otherSymbol);
        friend std::ostream& operator<<(std::ostream& out, const Ieee80211OFDMSymbol& symbol);
        Ieee80211OFDMSymbol(const std::vector<const APSKSymbol *>& subcarrierSymbols) : subcarrierSymbols(subcarrierSymbols) {}
        Ieee80211OFDMSymbol() { subcarrierSymbols.resize(53, NULL); } // (48 + 4 + 1), but one of them is skipped.
        const std::vector<const APSKSymbol *>& getSubCarrierSymbols() const { return subcarrierSymbols; }
        int symbolSize() const { return subcarrierSymbols.size(); }
        void pushAPSKSymbol(const APSKSymbol* apskSymbol, int subcarrierIndex);
        void clearSymbols() { subcarrierSymbols.resize(53, NULL); }
        ~Ieee80211OFDMSymbol();
};

} /* namespace physicallayer */
} /* namespace inet */

#endif /* __INET_OFDMSYMBOL_H */
