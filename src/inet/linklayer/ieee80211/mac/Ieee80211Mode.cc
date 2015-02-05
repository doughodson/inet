// Copyright (C) 2012 OpenSim Ltd
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
// @author: Zoltan Bojthe
//

#include <algorithm>

#include "inet/linklayer/ieee80211/mac/Ieee80211Mode.h"

#include "inet/physicallayer/ieee80211/Ieee80211Modulation.h"

namespace inet {

namespace ieee80211 {

using namespace inet::physicallayer;

/* Bit rates for 802.11b/g/a/p.
 * Must be ordered by mode, bitrate.
 */
const Ieee80211Mode Ieee80211Mode::data[] = {
    { 'a', 6000000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate6Mbps() },
    { 'a', 9000000, false, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate9Mbps() },
    { 'a', 12000000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate12Mbps() },
    { 'a', 18000000, false, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate18Mbps() },
    { 'a', 24000000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate24Mbps() },
    { 'a', 36000000, false, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate36Mbps() },
    { 'a', 48000000, false, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate48Mbps() },
    { 'a', 54000000, false, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate54Mbps() },

    { 'b', 1000000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetDsssRate1Mbps() },
    { 'b', 2000000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetDsssRate2Mbps() },
    { 'b', 5500000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetDsssRate5_5Mbps() },
    { 'b', 11000000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetDsssRate11Mbps() },

    { 'g', 1000000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetDsssRate1Mbps() },
    { 'g', 2000000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetDsssRate2Mbps() },
    { 'g', 5500000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetDsssRate5_5Mbps() },
    { 'g', 6000000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetErpOfdmRate6Mbps() },
    { 'g', 9000000, false, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetErpOfdmRate9Mbps() },
    { 'g', 11000000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetDsssRate11Mbps() },
    { 'g', 12000000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetErpOfdmRate12Mbps() },
    { 'g', 18000000, false, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetErpOfdmRate18Mbps() },
    { 'g', 24000000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetErpOfdmRate24Mbps() },
    { 'g', 36000000, false, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetErpOfdmRate36Mbps() },
    { 'g', 48000000, false, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetErpOfdmRate48Mbps() },
    { 'g', 54000000, false, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetErpOfdmRate54Mbps() },

    { 'p', 3000000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate3MbpsCS10MHz() },
    { 'p', 4500000, false, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate4_5MbpsCS10MHz() },
    { 'p', 6000000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate6MbpsCS10MHz() },
    { 'p', 9000000, false, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate9MbpsCS10MHz() },
    { 'p', 12000000, true, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate12MbpsCS10MHz() },
    { 'p', 18000000, false, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate18MbpsCS10MHz() },
    { 'p', 24000000, false, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate24MbpsCS10MHz() },
    { 'p', 27000000, false, Ieee80211Code::getCodeRate1per2(), Ieee80211Modulation::GetOfdmRate27MbpsCS10MHz() },
};

const int Ieee80211Mode::descriptorSize = sizeof(Ieee80211Mode::data) / sizeof(Ieee80211Mode::data[0]);

#if 0
// linear search

int Ieee80211Mode::findIdx(char mode, double bitrate)
{
    for (int i = 0; i < descriptorSize; i++) {
        if (data[i].mode == mode) {
            if (data[i].bitrate == bitrate)
                return i;
            if (data[i].bitrate > bitrate)
                break;
        }
        if (data[i].mode > mode)
            break;
    }
    return -1;
}

int Ieee80211Mode::getMinIdx(char mode)
{
    for (int i = 0; i < descriptorSize; i++) {
        if (data[i].mode == mode)
            return i;
        if (data[i].mode > mode)
            break;
    }
    throw cRuntimeError("mode '%c' not valid", mode);
}

int Ieee80211Mode::getMaxIdx(char mode)
{
    int idx = -1;
    for (int i = 0; i < descriptorSize; i++) {
        if (data[i].mode == mode)
            idx = i;
        if (data[i].mode > mode)
            break;
    }
    if (idx == -1)
        throw cRuntimeError("mode '%c' not valid", mode);
    return idx;
}

#else // if 0

namespace {
bool ieee80211DescriptorCompareModeBitrate(const Ieee80211Mode& a, const Ieee80211Mode& b)
{
    // return a < b;
    return (a.mode < b.mode) || ((a.mode == b.mode) && (a.bitrate < b.bitrate));
}

bool ieee80211DescriptorCompareMode(const Ieee80211Mode& a, const Ieee80211Mode& b)
{
    // return a < b;
    return a.mode < b.mode;
}
} // namespace {

int Ieee80211Mode::findIdx(char mode, double bitrate)
{
    Ieee80211Mode d;
    d.mode = mode;
    d.bitrate = bitrate;

    const Ieee80211Mode *found = std::lower_bound(data, &data[descriptorSize], d, ieee80211DescriptorCompareModeBitrate);
    if (found->mode == mode && found->bitrate == bitrate)
        return (int)(found - data);
    return -1;
}

int Ieee80211Mode::getMinIdx(char mode)
{
    Ieee80211Mode d;
    d.mode = mode;

    const Ieee80211Mode *found = std::lower_bound(data, &data[descriptorSize], d, ieee80211DescriptorCompareMode);
    if (found->mode == mode)
        return (int)(found - data);
    throw cRuntimeError("mode '%c' not valid", mode);
}

int Ieee80211Mode::getMaxIdx(char mode)
{
    Ieee80211Mode d;
    d.mode = mode;

    const Ieee80211Mode *found = std::upper_bound(data, &data[descriptorSize], d, ieee80211DescriptorCompareMode);
    if (found > data)
        --found;
    if (found->mode == mode)
        return (int)(found - data);
    throw cRuntimeError("mode '%c' not valid", mode);
}

#endif // if 0

int Ieee80211Mode::getIdx(char mode, double bitrate)
{
    int idx = findIdx(mode, bitrate);
    if (idx == -1)
        throw cRuntimeError("mode '%c':%g bps not valid", mode, bitrate);
    return idx;
}

bool Ieee80211Mode::incIdx(int& idx)
{
    ASSERT(idx >= 0 && idx < descriptorSize);

    if (data[idx].mode != data[idx + 1].mode)
        return false;
    ++idx;
    return true;
}

bool Ieee80211Mode::decIdx(int& idx)
{
    ASSERT(idx >= 0 && idx < descriptorSize);

    if (idx == 0 || data[idx].mode != data[idx - 1].mode)
        return false;
    --idx;
    return true;
}

const Ieee80211Mode& Ieee80211Mode::getDescriptor(int idx)
{
    ASSERT(idx >= 0 && idx < descriptorSize);

    return data[idx];
}

Ieee80211Modulation Ieee80211Mode::getModulation(char mode, double bitrate)
{
    int i = getIdx(mode, bitrate);
    return getDescriptor(i).modulation;
}

} // namespace ieee80211

} // namespace inet

