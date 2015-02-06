//
// Copyright (C) 2005,2006 INRIA, 2014 OpenSim Ltd.
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
// Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
//

#ifndef __INET_IEEE80211CODE_H
#define __INET_IEEE80211CODE_H

#include "inet/physicallayer/base/PhysicalLayerDefs.h"

namespace inet {

namespace physicallayer {

/**
 * This enumeration defines the various convolutional coding rates
 * used for the OFDM transmission modes in the IEEE 802.11
 * standard. DSSS (for example) rates which do not have an explicit
 * coding stage in their generation should have this parameter set to
 * WIFI_CODE_RATE_UNDEFINED.
 */
enum CodeRate {
    /** No explicit coding (e.g., DSSS rates) */
    CODE_RATE_UNDEFINED,
    /** Rate 3/4 */
    CODE_RATE_3_4,
    /** Rate 2/3 */
    CODE_RATE_2_3,
    /** Rate 1/2 */
    CODE_RATE_1_2,
    /** Rate 5/6 */
    CODE_RATE_5_6
};

class INET_API Ieee80211Code
{
  protected:
    enum CodeRate codeRate;

  public:
    Ieee80211Code()
    {
        codeRate = CODE_RATE_UNDEFINED;
    }

    enum CodeRate getCodeRate(void) const { return codeRate; }
    void setCodeRate(enum CodeRate cRate) { codeRate = cRate; };
};

} // namespace physicallayer

} // namespace inet

#endif // ifndef __INET_IEEE80211CODE_H

