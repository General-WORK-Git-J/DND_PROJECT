#ifndef _SPELLSLOTS_
#define _SPELLSLOTS_

#include <map>


class SpellSlots
{
private:
    std::map<int, int> maxSlots;
    std::map<int, int> usedSlots;

public:
    void setSlots(int level, int max);
    bool useSlot(int level);
    void resetSlots();
    void displaySlots() const;
};

#endif