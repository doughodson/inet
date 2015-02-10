#ifndef __INET_IEEE80211MODESET_H
#define __INET_IEEE80211MODESET_H

#include "inet/linklayer/ieee80211/mac/Ieee80211Mode.h"

namespace inet {

namespace ieee80211 {

class INET_API Ieee80211ModeSet
{
  protected:
    const char name;
    const std::vector<Ieee80211Mode> modes;

  public:
    static const std::vector<Ieee80211ModeSet> modeSets;

  protected:
    int getModeIndex(const Ieee80211Mode *mode) const;

  public:
    Ieee80211ModeSet(char name, const std::vector<Ieee80211Mode> modes);

    const char getName() const { return name; }

    const Ieee80211Mode *getMode(bps bitrate) const;
    const Ieee80211Mode *getSlowestMode() const;
    const Ieee80211Mode *getFastestMode() const;
    const Ieee80211Mode *getSlowerMode(const Ieee80211Mode *mode) const;
    const Ieee80211Mode *getFasterMode(const Ieee80211Mode *mode) const;

    static const Ieee80211ModeSet *getModeSet(char mode);
};

} // namespace ieee80211

} // namespace inet

#endif // ifndef __INET_IEEE80211MODESET_H

