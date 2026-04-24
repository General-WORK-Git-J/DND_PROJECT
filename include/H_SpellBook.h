#ifndef _SPELLBOOK_
#define _SPELLBOOK_

#include "H_spells.h"
#include <vector>

class Spellbook
{
private:
    std::vector<Spell> knownSpells;

public:
    void addSpell(const Spell& spell);
    void removeSpell(std::string name);
    bool updateSpell(size_t index, const Spell& spell);
    void displayAllSpells() const;
    void displaySpellsWithIndex() const;
    void saveSpellbook(const std::string& filename) const;
    void loadSpellbook(const std::string& filename);

    std::vector<Spell> getSpellsByLevel(int level) const;
    std::vector<Spell> getAllSpells() const;
};

#endif
