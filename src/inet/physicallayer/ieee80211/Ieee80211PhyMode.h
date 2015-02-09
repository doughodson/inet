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

#ifndef __INET_IEEE80211PHYMODE_H
#define __INET_IEEE80211PHYMODE_H

#include "inet/physicallayer/ieee80211/Ieee80211Code.h"
#include "inet/physicallayer/ieee80211/Ieee80211Modulation.h"

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
 * See IEEE Std 802.11-2007 section 18.2.2.
 */
enum Ieee80211PreambleMode {
    IEEE80211_PREAMBLE_LONG,
    IEEE80211_PREAMBLE_SHORT,
    IEEE80211_PREAMBLE_HT_MF,
    IEEE80211_PREAMBLE_HT_GF
};

class INET_API Ieee80211PhyMode
{
  protected:
    Ieee80211PreambleMode preambleMode;
    Ieee80211Code code;
    Ieee80211Modulation modulation;

    // TODO: move?
    Hz channelSpacing;
    bps dataRate;
    bps phyRate;
    enum ModulationClass modulationClass;
    Hz bandwidth;

  public:
    Ieee80211PreambleMode getPreambleMode() { return preambleMode; }
    Ieee80211Code & getCode() { return code; }
    Ieee80211Modulation & getModulation() { return modulation; }

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
        code.setCodeRate(cRate);
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
     * \returns true if this mode is a mandatory mode, false
     *          otherwise.
     */
    enum ModulationClass getModulationClass() const { return modulationClass; }
    void setModulationClass(enum ModulationClass p) { modulationClass = p; }

    Ieee80211PhyMode();

    bool operator==(const Ieee80211PhyMode& b)
    {
        return *this == b;
    }

  public:
    static Ieee80211PhyMode GetDsssRate1Mbps();
    static Ieee80211PhyMode GetDsssRate2Mbps();
    static Ieee80211PhyMode GetDsssRate5_5Mbps();
    static Ieee80211PhyMode GetDsssRate11Mbps();
    static Ieee80211PhyMode GetErpOfdmRate6Mbps();
    static Ieee80211PhyMode GetErpOfdmRate9Mbps();
    static Ieee80211PhyMode GetErpOfdmRate12Mbps();
    static Ieee80211PhyMode GetErpOfdmRate18Mbps();
    static Ieee80211PhyMode GetErpOfdmRate24Mbps();
    static Ieee80211PhyMode GetErpOfdmRate36Mbps();
    static Ieee80211PhyMode GetErpOfdmRate48Mbps();
    static Ieee80211PhyMode GetErpOfdmRate54Mbps();
    static Ieee80211PhyMode GetOfdmRate6Mbps();
    static Ieee80211PhyMode GetOfdmRate9Mbps();
    static Ieee80211PhyMode GetOfdmRate12Mbps();
    static Ieee80211PhyMode GetOfdmRate18Mbps();
    static Ieee80211PhyMode GetOfdmRate24Mbps();
    static Ieee80211PhyMode GetOfdmRate36Mbps();
    static Ieee80211PhyMode GetOfdmRate48Mbps();
    static Ieee80211PhyMode GetOfdmRate54Mbps();
    static Ieee80211PhyMode GetOfdmRate3MbpsCS10MHz();
    static Ieee80211PhyMode GetOfdmRate4_5MbpsCS10MHz();
    static Ieee80211PhyMode GetOfdmRate6MbpsCS10MHz();
    static Ieee80211PhyMode GetOfdmRate9MbpsCS10MHz();
    static Ieee80211PhyMode GetOfdmRate12MbpsCS10MHz();
    static Ieee80211PhyMode GetOfdmRate18MbpsCS10MHz();
    static Ieee80211PhyMode GetOfdmRate24MbpsCS10MHz();
    static Ieee80211PhyMode GetOfdmRate27MbpsCS10MHz();
    static Ieee80211PhyMode GetOfdmRate1_5MbpsCS5MHz();
    static Ieee80211PhyMode GetOfdmRate2_25MbpsCS5MHz();
    static Ieee80211PhyMode GetOfdmRate3MbpsCS5MHz();
    static Ieee80211PhyMode GetOfdmRate4_5MbpsCS5MHz();
    static Ieee80211PhyMode GetOfdmRate6MbpsCS5MHz();
    static Ieee80211PhyMode GetOfdmRate9MbpsCS5MHz();
    static Ieee80211PhyMode GetOfdmRate12MbpsCS5MHz();
    static Ieee80211PhyMode GetOfdmRate13_5MbpsCS5MHz();

    virtual simtime_t getPlcpHeaderDuration(Ieee80211PreambleMode preamble) const;
    virtual simtime_t getPlcpPreambleDuration(Ieee80211PreambleMode preamble) const;
    virtual simtime_t getPreambleAndHeader(Ieee80211PreambleMode preamble) const;
    virtual simtime_t getPayloadDuration(uint64_t size) const;
    virtual simtime_t calculateTxDuration(uint64_t size, Ieee80211PreambleMode preamble) const;
    virtual simtime_t getSlotDuration(Ieee80211PreambleMode preamble) const;
    virtual simtime_t getSifsTime(Ieee80211PreambleMode preamble) const;
    virtual simtime_t get_aPHY_RX_START_Delay(Ieee80211PreambleMode preamble) const;

    Ieee80211PhyMode getPlcpHeaderMode(Ieee80211PreambleMode preamble) const;
};

bool operator==(const Ieee80211PhyMode& a, const Ieee80211PhyMode& b);

} // namespace physicallayer

} // namespace inet

#endif // ifndef __INET_IEEE80211PHYMODE_H
