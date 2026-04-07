#include "H_SpellSlots.h"
#include <iostream>

void SpellSlots::setSlots(int level, int max)
{
    maxSlots[level] = max;
    usedSlots[level] = 0;
}

bool SpellSlots::useSlot(int level)
{
    if (usedSlots[level] < maxSlots[level])
    {
        usedSlots[level]++;
        return true;
    }
    return false;
}

void SpellSlots::resetSlots()
{
    for (auto& slot : usedSlots)
    {
        slot.second = 0;
    }
}

void SpellSlots::displaySlots() const
{
    for (const auto& slot : maxSlots)
    {
        int level = slot.first;
        std::cout << "Level " << level
                  << ": " << usedSlots.at(level)
                  << "/" << maxSlots.at(level) << "\n";
    }
}