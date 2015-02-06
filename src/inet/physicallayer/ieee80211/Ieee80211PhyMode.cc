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

#include "inet/physicallayer/ieee80211/Ieee80211PhyMode.h"

namespace inet {

namespace physicallayer {

Ieee80211PhyMode Ieee80211PhyMode::GetDsssRate1Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_DSSS);
    mode.setBandwidth(Hz(22000000));
    mode.setChannelSpacing(Hz(5000000));
    mode.setDataRate(bps(1000000));
    mode.setCodeRate(CODE_RATE_UNDEFINED);
    mode.getModulation().setConstellationSize(2);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetDsssRate2Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_DSSS);
    mode.setBandwidth(Hz(22000000));
    mode.setChannelSpacing(Hz(5000000));
    mode.setDataRate(bps(2000000));
    mode.setCodeRate(CODE_RATE_UNDEFINED);
    mode.getModulation().setConstellationSize(2);
    return mode;
}

/**
 * Clause 18 rates (HR/DSSS)
 */
Ieee80211PhyMode Ieee80211PhyMode::GetDsssRate5_5Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_DSSS);
    mode.setBandwidth(Hz(22000000));
    mode.setChannelSpacing(Hz(5000000));
    mode.setDataRate(bps(5500000));
    mode.setCodeRate(CODE_RATE_UNDEFINED);
    mode.getModulation().setConstellationSize(4);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetDsssRate11Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_DSSS);
    mode.setBandwidth(Hz(22000000));
    mode.setChannelSpacing(Hz(5000000));
    mode.setDataRate(bps(11000000));
    mode.setCodeRate(CODE_RATE_UNDEFINED);
    mode.getModulation().setConstellationSize(4);
    return mode;
}

/**
 * Clause 19.5 rates (ERP-OFDM)
 * TODO: check bandwidth and channel spacing
 */
Ieee80211PhyMode Ieee80211PhyMode::GetErpOfdmRate6Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_ERP_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setDataRate(bps(6000000));
    mode.setCodeRate(CODE_RATE_1_2);
    mode.getModulation().setConstellationSize(2);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetErpOfdmRate9Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_ERP_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setDataRate(bps(9000000));
    mode.setCodeRate(CODE_RATE_3_4);
    mode.getModulation().setConstellationSize(2);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetErpOfdmRate12Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_ERP_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setDataRate(bps(12000000));
    mode.setCodeRate(CODE_RATE_1_2);
    mode.getModulation().setConstellationSize(4);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetErpOfdmRate18Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_ERP_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setDataRate(bps(18000000));
    mode.setCodeRate(CODE_RATE_3_4);
    mode.getModulation().setConstellationSize(4);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetErpOfdmRate24Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_ERP_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setDataRate(bps(24000000));
    mode.setCodeRate(CODE_RATE_1_2);
    mode.getModulation().setConstellationSize(16);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetErpOfdmRate36Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_ERP_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setDataRate(bps(36000000));
    mode.setCodeRate(CODE_RATE_3_4);
    mode.getModulation().setConstellationSize(16);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetErpOfdmRate48Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_ERP_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setDataRate(bps(48000000));
    mode.setCodeRate(CODE_RATE_2_3);
    mode.getModulation().setConstellationSize(64);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetErpOfdmRate54Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_ERP_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setDataRate(bps(54000000));
    mode.setCodeRate(CODE_RATE_3_4);
    mode.getModulation().setConstellationSize(64);
    return mode;
}

/**
 * Clause 17 rates (OFDM)
 */
Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate6Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(20000000));
    mode.setDataRate(bps(6000000));
    mode.setCodeRate(CODE_RATE_1_2);
    mode.getModulation().setConstellationSize(2);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate9Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(20000000));
    mode.setDataRate(bps(9000000));
    mode.setCodeRate(CODE_RATE_UNDEFINED);
    mode.getModulation().setConstellationSize(2);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate12Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(20000000));
    mode.setDataRate(bps(12000000));
    mode.setCodeRate(CODE_RATE_UNDEFINED);
    mode.getModulation().setConstellationSize(4);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate18Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(20000000));
    mode.setDataRate(bps(18000000));
    mode.setCodeRate(CODE_RATE_UNDEFINED);
    mode.getModulation().setConstellationSize(4);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate24Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(20000000));
    mode.setDataRate(bps(24000000));
    mode.setCodeRate(CODE_RATE_1_2);
    mode.getModulation().setConstellationSize(16);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate36Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(20000000));
    mode.setDataRate(bps(36000000));
    mode.setCodeRate(CODE_RATE_3_4);
    mode.getModulation().setConstellationSize(16);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate48Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(20000000));
    mode.setDataRate(bps(48000000));
    mode.setCodeRate(CODE_RATE_2_3);
    mode.getModulation().setConstellationSize(64);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate54Mbps()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(20000000));
    mode.setDataRate(bps(54000000));
    mode.setCodeRate(CODE_RATE_3_4);
    mode.getModulation().setConstellationSize(64);
    return mode;
}

/* 10 MHz channel rates */
Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate3MbpsCS10MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(10000000));
    mode.setDataRate(bps(3000000));
    mode.setCodeRate(CODE_RATE_1_2);
    mode.getModulation().setConstellationSize(2);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate4_5MbpsCS10MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(10000000));
    mode.setDataRate(bps(4500000));
    mode.setCodeRate(CODE_RATE_3_4);
    mode.getModulation().setConstellationSize(2);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate6MbpsCS10MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(10000000));
    mode.setDataRate(bps(6000000));
    mode.setCodeRate(CODE_RATE_1_2);
    mode.getModulation().setConstellationSize(4);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate9MbpsCS10MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(10000000));
    mode.setDataRate(bps(9000000));
    mode.setCodeRate(CODE_RATE_3_4);
    mode.getModulation().setConstellationSize(4);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate12MbpsCS10MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(10000000));
    mode.setDataRate(bps(12000000));
    mode.setCodeRate(CODE_RATE_1_2);
    mode.getModulation().setConstellationSize(16);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate18MbpsCS10MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(10000000));
    mode.setDataRate(bps(18000000));
    mode.setCodeRate(CODE_RATE_3_4);
    mode.getModulation().setConstellationSize(16);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate24MbpsCS10MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(10000000));
    mode.setDataRate(bps(24000000));
    mode.setCodeRate(CODE_RATE_2_3);
    mode.getModulation().setConstellationSize(64);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate27MbpsCS10MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(10000000));
    mode.setDataRate(bps(27000000));
    mode.setCodeRate(CODE_RATE_3_4);
    mode.getModulation().setConstellationSize(64);
    return mode;
}

/* 5 MHz channel rates */
Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate1_5MbpsCS5MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(5000000));
    mode.setDataRate(bps(1500000));
    mode.setCodeRate(CODE_RATE_1_2);
    mode.getModulation().setConstellationSize(2);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate2_25MbpsCS5MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(5000000));
    mode.setDataRate(bps(2250000));
    mode.setCodeRate(CODE_RATE_3_4);
    mode.getModulation().setConstellationSize(2);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate3MbpsCS5MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(5000000));
    mode.setDataRate(bps(3000000));
    mode.setCodeRate(CODE_RATE_1_2);
    mode.getModulation().setConstellationSize(4);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate4_5MbpsCS5MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(5000000));
    mode.setDataRate(bps(4500000));
    mode.setCodeRate(CODE_RATE_3_4);
    mode.getModulation().setConstellationSize(4);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate6MbpsCS5MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(5000000));
    mode.setDataRate(bps(6000000));
    mode.setCodeRate(CODE_RATE_1_2);
    mode.getModulation().setConstellationSize(16);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate9MbpsCS5MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(5000000));
    mode.setDataRate(bps(9000000));
    mode.setCodeRate(CODE_RATE_3_4);
    mode.getModulation().setConstellationSize(16);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate12MbpsCS5MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(5000000));
    mode.setDataRate(bps(12000000));
    mode.setCodeRate(CODE_RATE_2_3);
    mode.getModulation().setConstellationSize(64);
    return mode;
}

Ieee80211PhyMode Ieee80211PhyMode::GetOfdmRate13_5MbpsCS5MHz()
{
    Ieee80211PhyMode mode;
    mode.setModulationClass(MOD_CLASS_OFDM);
    mode.setBandwidth(Hz(20000000));
    mode.setChannelSpacing(Hz(5000000));
    mode.setDataRate(bps(13500000));
    mode.setCodeRate(CODE_RATE_3_4);
    mode.getModulation().setConstellationSize(64);
    return mode;
}

simtime_t Ieee80211PhyMode::getPlcpHeaderDuration(Ieee80211PreambleMode preamble) const
{
    switch (getModulationClass()) {
        case MOD_CLASS_OFDM: {
            switch ((int)getChannelSpacing().get()) {
                case 20000000:
                default:
                    // IEEE Std 802.11-2007, section 17.3.3 and figure 17-4
                    // also section 17.3.2.3, table 17-4
                    // We return the duration of the SIGNAL field only, since the
                    // SERVICE field (which strictly speaking belongs to the PLCP
                    // header, see section 17.3.2 and figure 17-1) is sent using the
                    // payload mode.
                    return 4.0 / 1000000.0;

                case 10000000:
                    // IEEE Std 802.11-2007, section 17.3.2.3, table 17-4
                    return 8 / 1000000.0;

                case 5000000:
                    // IEEE Std 802.11-2007, section 17.3.2.3, table 17-4
                    return 16.0 / 1000000.0;
            }
            break;
        }

        case MOD_CLASS_ERP_OFDM:
            return 16.0 / 1000000.0;

        case MOD_CLASS_DSSS:
            if (preamble == IEEE80211_PREAMBLE_SHORT) {
                // IEEE Std 802.11-2007, section 18.2.2.2 and figure 18-2
                return 24.0 / 1000000.0;
            }
            else {    // IEEE80211_PREAMBLE_LONG
                      // IEEE Std 802.11-2007, sections 18.2.2.1 and figure 18-1
                return 48.0 / 1000000.0;
            }

        default:
            throw cRuntimeError("unsupported modulation class");
    }
}

simtime_t Ieee80211PhyMode::getPlcpPreambleDuration(Ieee80211PreambleMode preamble) const
{
    switch (getModulationClass()) {
        case MOD_CLASS_OFDM: {
            switch ((int)getChannelSpacing().get()) {
                case 20000000:
                default:
                    // IEEE Std 802.11-2007, section 17.3.3,  figure 17-4
                    // also section 17.3.2.3, table 17-4
                    return 16.0 / 1000000.0;

                case 10000000:
                    // IEEE Std 802.11-2007, section 17.3.3, table 17-4
                    // also section 17.3.2.3, table 17-4
                    return 32.0 / 1000000.0;

                case 5000000:
                    // IEEE Std 802.11-2007, section 17.3.3
                    // also section 17.3.2.3, table 17-4
                    return 64.0 / 1000000.0;
            }
            break;
        }

        case MOD_CLASS_ERP_OFDM:
            return 4.0 / 1000000.0;

        case MOD_CLASS_DSSS:
            if (preamble == IEEE80211_PREAMBLE_SHORT) {
                // IEEE Std 802.11-2007, section 18.2.2.2 and figure 18-2
                return 72.0 / 1000000.0;
            }
            else {    // IEEE80211_PREAMBLE_LONG
                      // IEEE Std 802.11-2007, sections 18.2.2.1 and figure 18-1
                return 144.0 / 1000000.0;
            }

        default:
            throw cRuntimeError("unsupported modulation class");
    }
}

//
// Compute the Payload duration in function of the modulation type
//
simtime_t Ieee80211PhyMode::getPayloadDuration(uint64_t size) const
{
    simtime_t val;
    switch (getModulationClass()) {
        case MOD_CLASS_OFDM:
        case MOD_CLASS_ERP_OFDM: {
            // IEEE Std 802.11-2007, section 17.3.2.3, table 17-4
            // corresponds to T_{SYM} in the table
            simtime_t symbolDurationUs;
            switch ((int)getChannelSpacing().get()) {
                case 20000000:
                default:
                    symbolDurationUs = 4;
                    break;

                case 10000000:
                    symbolDurationUs = 8;
                    break;

                case 5000000:
                    symbolDurationUs = 16;
                    break;
            }
            // IEEE Std 802.11-2007, section 17.3.2.2, table 17-3
            // corresponds to N_{DBPS} in the table
            double numDataBitsPerSymbol = getDataRate().get() * symbolDurationUs.dbl() / 1e6;
            // IEEE Std 802.11-2007, section 17.3.5.3, equation (17-11)
            int numSymbols = lrint(ceil((16 + size + 6.0) / numDataBitsPerSymbol));

            // Add signal extension for ERP PHY
            double aux;
            if (getModulationClass() == MOD_CLASS_ERP_OFDM)
                aux = numSymbols * symbolDurationUs.dbl() + 6;
            else
                aux = numSymbols * symbolDurationUs.dbl();
            val = (aux / 1000000.0);
            return val;
        }

        case MOD_CLASS_DSSS:
            // IEEE Std 802.11-2007, section 18.2.3.5
            double aux;
            aux = lrint(ceil((size) / (getDataRate().get() / 1.0e6)));
            val = (aux / 1000000.0);
            return val;
            break;

        default:
            throw cRuntimeError("unsupported modulation class");
    }
}

//
// Return the physical header duration, useful for the mac
//
simtime_t Ieee80211PhyMode::getPreambleAndHeader(Ieee80211PreambleMode preamble) const
{
    return getPlcpPreambleDuration(preamble) + getPlcpHeaderDuration(preamble);
}

simtime_t Ieee80211PhyMode::calculateTxDuration(uint64_t size, Ieee80211PreambleMode preamble) const
{
    simtime_t duration = getPlcpPreambleDuration(preamble)
        + getPlcpHeaderDuration(preamble)
        + getPayloadDuration(size);
    return duration;
}

Ieee80211PhyMode Ieee80211PhyMode::getPlcpHeaderMode(Ieee80211PreambleMode preamble) const
{
    switch (getModulationClass()) {
        case MOD_CLASS_OFDM: {
            switch ((int)getChannelSpacing().get()) {
                case 5000000:
                    return Ieee80211PhyMode::GetOfdmRate1_5MbpsCS5MHz();

                case 10000000:
                    return Ieee80211PhyMode::GetOfdmRate3MbpsCS10MHz();

                default:
                    // IEEE Std 802.11-2007, 17.3.2
                    // actually this is only the first part of the PlcpHeader,
                    // because the last 16 bits of the PlcpHeader are using the
                    // same mode of the payload
                    return Ieee80211PhyMode::GetOfdmRate6Mbps();
            }
            break;
        }

        case MOD_CLASS_ERP_OFDM:
            return Ieee80211PhyMode::GetErpOfdmRate6Mbps();

        case MOD_CLASS_DSSS:
            if (preamble == IEEE80211_PREAMBLE_LONG) {
                // IEEE Std 802.11-2007, sections 15.2.3 and 18.2.2.1
                return Ieee80211PhyMode::GetDsssRate1Mbps();
            }
            else {    // IEEE80211_PREAMBLE_SHORT
                      // IEEE Std 802.11-2007, section 18.2.2.2
                return Ieee80211PhyMode::GetDsssRate2Mbps();
            }

        default:
            throw cRuntimeError("unsupported modulation class");
    }
}

simtime_t Ieee80211PhyMode::getSlotDuration(Ieee80211PreambleMode preamble) const
{
    switch (getModulationClass()) {
        case MOD_CLASS_OFDM: {
            switch ((int)getChannelSpacing().get()) {
                case 5000000:
                    return 21.0 / 1000000.0;

                case 10000000:
                    return 13.0 / 1000000.0;

                default:
                    // IEEE Std 802.11-2007, 17.3.2
                    // actually this is only the first part of the PlcpHeader,
                    // because the last 16 bits of the PlcpHeader are using the
                    // same mode of the payload
                    return 9.0 / 1000000.0;
            }
            break;
        }

        case MOD_CLASS_ERP_OFDM:
            if (preamble == IEEE80211_PREAMBLE_LONG) {
                // IEEE Std 802.11-2007, sections 15.2.3 and 18.2.2.1
                return 20.0 / 1000000.0;
            }
            else {    // IEEE80211_PREAMBLE_SHORT
                      // IEEE Std 802.11-2007, section 18.2.2.2
                return 9.0 / 1000000.0;
            }

        case MOD_CLASS_DSSS:
            return 20.0 / 1000000.0;

        default:
            throw cRuntimeError("unsupported modulation class");
    }
}

simtime_t Ieee80211PhyMode::getSifsTime(Ieee80211PreambleMode preamble) const
{
    switch (getModulationClass()) {
        case MOD_CLASS_OFDM: {
            switch ((int)getChannelSpacing().get()) {
                case 5000000:
                    return 64.0 / 1000000.0;

                case 10000000:
                    return 32.0 / 1000000.0;

                default:
                    // IEEE Std 802.11-2007, 17.3.2
                    // actually this is only the first part of the PlcpHeader,
                    // because the last 16 bits of the PlcpHeader are using the
                    // same mode of the payload
                    return 16.0 / 1000000;
            }
            break;
        }

        case MOD_CLASS_ERP_OFDM:
            // IEEE Std 802.11-2007, sections 15.2.3 and 18.2.2.1
            return 10.0 / 1000000.0;

        case MOD_CLASS_DSSS:
            return 10.0 / 1000000.0;

        default:
            throw cRuntimeError("unsupported modulation class");
    }
}

simtime_t Ieee80211PhyMode::get_aPHY_RX_START_Delay(Ieee80211PreambleMode preamble) const
{
    switch (getModulationClass()) {
        case MOD_CLASS_OFDM: {
            switch ((int)getChannelSpacing().get()) {
                case 5000000:
                    return 97.0 / 1000000.0;

                case 10000000:
                    return 49.0 / 1000000.0;

                default:
                    // IEEE Std 802.11-2007, 17.3.2
                    // actually this is only the first part of the PlcpHeader,
                    // because the last 16 bits of the PlcpHeader are using the
                    // same mode of the payload
                    return 25.0 / 1000000.0;
            }
        }

        case MOD_CLASS_ERP_OFDM:
            // IEEE Std 802.11-2007, section 18.2.2.2
            return 24.0 / 1000000.0;

        case MOD_CLASS_DSSS:
            if (preamble == IEEE80211_PREAMBLE_LONG) {
                // IEEE Std 802.11-2007, sections 15.2.3 and 18.2.2.1
                return 192.0 / 1000000.0;
            }
            else {    // IEEE80211_PREAMBLE_SHORT
                      // IEEE Std 802.11-2007, section 18.2.2.2
                return 96.0 / 1000000.0;
            }

        default:
            throw cRuntimeError("unsupported modulation class");
    }
}

} // namespace physicallayer

} // namespace inet

