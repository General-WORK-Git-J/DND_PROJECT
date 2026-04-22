#ifndef SPELLSLOTS_H
#define SPELLSLOTS_H

#include <map>
#include <fstream>


class SpellSlots
{
private:
    std::map<int, int> maxSlots;
    std::map<int, int> currentSlots;

public:
    void setSlots(int level, int max);
    void setCurrentSlots(int level, int current);
    bool useSlot(int level);
    void resetSlots();
    int getMaxSlots(int level) const;
    int getCurrentSlots(int level) const;
    bool hasAvailableSlot(int level) const;
    bool hasAnySlots() const;
    void displaySlots() const;
    void save(std::ofstream& file) const;
    void load(std::ifstream& file);
};

#endif // SPELLSLOTS_H
