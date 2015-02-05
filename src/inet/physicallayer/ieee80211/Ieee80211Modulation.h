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

#ifndef __INET_IEEE80211MODULATION_H
#define __INET_IEEE80211MODULATION_H

#include "inet/physicallayer/base/PhysicalLayerDefs.h"

namespace inet {

namespace physicallayer {

enum ModulationClass {
    /** Modulation class unknown or unspecified. A WifiMode with this
       WifiModulationClass has not been properly initialised. */
    MOD_CLASS_UNKNOWN = 0,
    /** Infrared (IR) (Clause 16) */
    MOD_CLASS_IR,
    /** Frequency-hopping spread spectrum (FHSS) PHY (Clause 14) */
    MOD_CLASS_FHSS,
    /** DSSS PHY (Clause 15) and HR/DSSS PHY (Clause 18) */
    MOD_CLASS_DSSS,
    /** ERP-PBCC PHY (19.6) */
    MOD_CLASS_ERP_PBCC,
    /** DSSS-OFDM PHY (19.7) */
    MOD_CLASS_DSSS_OFDM,
    /** ERP-OFDM PHY (19.5) */
    MOD_CLASS_ERP_OFDM,
    /** OFDM PHY (Clause 17) */
    MOD_CLASS_OFDM,
    /** HT PHY (Clause 20) */
    MOD_CLASS_HT
};

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

/**
 * See IEEE Std 802.11-2007 section 18.2.2.
 */
enum Ieee80211PreambleMode {
    IEEE80211_PREAMBLE_LONG,
    IEEE80211_PREAMBLE_SHORT,
    IEEE80211_PREAMBLE_HT_MF,
    IEEE80211_PREAMBLE_HT_GF
};

/**
 * \brief represent a single transmission mode
 *
 * A WifiMode is implemented by a single integer which is used
 * to lookup in a global array the characteristics of the
 * associated transmission mode. It is thus extremely cheap to
 * keep a WifiMode variable around.
 */
class Ieee80211Modulation
{
  public:
    /**
     * \returns the number of Hz used by this signal
     */
    Hz getChannelSpacing(void) const { return channelSpacing; }
    void setChannelSpacing(Hz p) { channelSpacing = p; }
    Hz getBandwidth() const { return bandwidth; }
    void setBandwidth(Hz p) { bandwidth = p; }
    /**
     * \returns the physical bit rate of this signal.
     *
     * If a transmission mode uses 1/2 FEC, and if its
     * data rate is 3Mbs, the phy rate is 6Mbs
     */
    /// MANDATORY it is necessary set the dataRate before the codeRate
    void setCodeRate(enum CodeRate cRate)
    {
        codeRate = cRate;
        switch (cRate) {
            case CODE_RATE_5_6:
                phyRate = dataRate * 6 / 5;
                break;

            case CODE_RATE_3_4:
                phyRate = dataRate * 4 / 3;
                break;

            case CODE_RATE_2_3:
                phyRate = dataRate * 3 / 2;
                break;

            case CODE_RATE_1_2:
                phyRate = dataRate * 2 / 1;
                break;

            case CODE_RATE_UNDEFINED:
            default:
                phyRate = dataRate;
                break;
        }
    };
    bps getPhyRate(void) const { return phyRate; }
    /**
     * \returns the data bit rate of this signal.
     */
    bps getDataRate(void) const { return dataRate; }
    void setDataRate(bps p) { dataRate = p; }
    /**
     * \returns the coding rate of this transmission mode
     */
    enum CodeRate getCodeRate(void) const { return codeRate; }

    /**
     * \returns the size of the modulation constellation.
     */
    uint8_t getConstellationSize(void) const { return constellationSize; }
    void setConstellationSize(uint8_t p) { constellationSize = p; }

    /**
     * \returns true if this mode is a mandatory mode, false
     *          otherwise.
     */
    enum ModulationClass getModulationClass() const { return modulationClass; }
    void setModulationClass(enum ModulationClass p) { modulationClass = p; }

    void setIsMandatory(bool val) { isMandatory = val; }
    bool getIsMandatory() { return isMandatory; }
    Ieee80211Modulation()
    {
        isMandatory = false;
        channelSpacing = Hz(NaN);
        bandwidth = Hz(NaN);
        codeRate = CODE_RATE_UNDEFINED;
        dataRate = bps(NaN);
        phyRate = bps(NaN);
        constellationSize = 0;
        modulationClass = MOD_CLASS_UNKNOWN;
    }

    bool operator==(const Ieee80211Modulation& b)
    {
        return *this == b;
    }

  private:
    bool isMandatory;
    Hz channelSpacing;
    enum CodeRate codeRate;
    bps dataRate;
    bps phyRate;
    uint8_t constellationSize;
    enum ModulationClass modulationClass;
    Hz bandwidth;

  public:
    static Ieee80211Modulation GetDsssRate1Mbps();
    static Ieee80211Modulation GetDsssRate2Mbps();
    static Ieee80211Modulation GetDsssRate5_5Mbps();
    static Ieee80211Modulation GetDsssRate11Mbps();
    static Ieee80211Modulation GetErpOfdmRate6Mbps();
    static Ieee80211Modulation GetErpOfdmRate9Mbps();
    static Ieee80211Modulation GetErpOfdmRate12Mbps();
    static Ieee80211Modulation GetErpOfdmRate18Mbps();
    static Ieee80211Modulation GetErpOfdmRate24Mbps();
    static Ieee80211Modulation GetErpOfdmRate36Mbps();
    static Ieee80211Modulation GetErpOfdmRate48Mbps();
    static Ieee80211Modulation GetErpOfdmRate54Mbps();
    static Ieee80211Modulation GetOfdmRate6Mbps();
    static Ieee80211Modulation GetOfdmRate9Mbps();
    static Ieee80211Modulation GetOfdmRate12Mbps();
    static Ieee80211Modulation GetOfdmRate18Mbps();
    static Ieee80211Modulation GetOfdmRate24Mbps();
    static Ieee80211Modulation GetOfdmRate36Mbps();
    static Ieee80211Modulation GetOfdmRate48Mbps();
    static Ieee80211Modulation GetOfdmRate54Mbps();
    static Ieee80211Modulation GetOfdmRate3MbpsCS10MHz();
    static Ieee80211Modulation GetOfdmRate4_5MbpsCS10MHz();
    static Ieee80211Modulation GetOfdmRate6MbpsCS10MHz();
    static Ieee80211Modulation GetOfdmRate9MbpsCS10MHz();
    static Ieee80211Modulation GetOfdmRate12MbpsCS10MHz();
    static Ieee80211Modulation GetOfdmRate18MbpsCS10MHz();
    static Ieee80211Modulation GetOfdmRate24MbpsCS10MHz();
    static Ieee80211Modulation GetOfdmRate27MbpsCS10MHz();
    static Ieee80211Modulation GetOfdmRate1_5MbpsCS5MHz();
    static Ieee80211Modulation GetOfdmRate2_25MbpsCS5MHz();
    static Ieee80211Modulation GetOfdmRate3MbpsCS5MHz();
    static Ieee80211Modulation GetOfdmRate4_5MbpsCS5MHz();
    static Ieee80211Modulation GetOfdmRate6MbpsCS5MHz();
    static Ieee80211Modulation GetOfdmRate9MbpsCS5MHz();
    static Ieee80211Modulation GetOfdmRate12MbpsCS5MHz();
    static Ieee80211Modulation GetOfdmRate13_5MbpsCS5MHz();

    simtime_t getPlcpHeaderDuration(Ieee80211PreambleMode preamble);
    simtime_t getPlcpPreambleDuration(Ieee80211PreambleMode preamble);
    simtime_t getPreambleAndHeader(Ieee80211PreambleMode preamble);
    simtime_t getPayloadDuration(uint64_t size);
    simtime_t calculateTxDuration(uint64_t size, Ieee80211PreambleMode preamble);
    simtime_t getSlotDuration(Ieee80211PreambleMode preamble);
    simtime_t getSifsTime(Ieee80211PreambleMode preamble);
    simtime_t get_aPHY_RX_START_Delay(Ieee80211PreambleMode preamble);
    Ieee80211Modulation getPlcpHeaderMode(Ieee80211PreambleMode preamble);
};

bool operator==(const Ieee80211Modulation& a, const Ieee80211Modulation& b);

} // namespace physicallayer

} // namespace inet

#endif // ifndef __INET_IEEE80211MODULATION_H

