#ifndef __INET_IEEE80211DATARATE_H
#define __INET_IEEE80211DATARATE_H

#include "inet/physicallayer/ieee80211/Ieee80211Modulation.h"
#include "inet/physicallayer/ieee80211/Ieee80211OFDMCode.h"
#include "inet/physicallayer/ieee80211/Ieee80211PhyMode.h"

namespace inet {

namespace ieee80211 {

using namespace inet::physicallayer;

class INET_API Ieee80211Mode
{
  public:
    char mode;
    double bitrate;
    bool isMandatory;
    Ieee80211PhyMode phyMode;

  private:
    static const int descriptorSize;
    static const Ieee80211Mode data[];

  public:
    bool getIsMandatory() const { return isMandatory; }

  public:
    static int findIdx(char mode, double bitrate);
    static int getIdx(char mode, double bitrate);
    static int getMinIdx(char mode);
    static int getMaxIdx(char mode);
    static bool incIdx(int& idx);
    static bool decIdx(int& idx);
    static const Ieee80211Mode& getDescriptor(int idx);
    static Ieee80211PhyMode getModulation(char mode, double bitrate);
    static int size() { return descriptorSize; }
};

} // namespace ieee80211

} // namespace inet

#endif // ifndef __INET_IEEE80211DATARATE_H

