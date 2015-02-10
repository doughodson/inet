#ifndef __INET_IEEE80211MODE_H
#define __INET_IEEE80211MODE_H

#include "inet/physicallayer/ieee80211/Ieee80211PhyMode.h"

namespace inet {

namespace ieee80211 {

using namespace inet::physicallayer;

class INET_API Ieee80211Mode
{
  protected:
    const bool isMandatory;
    // TODO: separate header phy mode and payload phy mode?
    const Ieee80211PhyMode phyMode;

  public:
    Ieee80211Mode(bool isMandatory, const Ieee80211PhyMode phyMode);

    bool getIsMandatory() const { return isMandatory; }
    const Ieee80211PhyMode *getPhyMode() const { return &phyMode; }
};

} // namespace ieee80211

} // namespace inet

#endif // ifndef __INET_IEEE80211MODE_H

