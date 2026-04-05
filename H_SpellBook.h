#ifndef _SPELLBOOK_
#define _SPELLBOOK_

#include "H_Spells.h"
#include <vector>

class Spellbook
{
private:
    std::vector<Spell> knownSpells;

public:
    void addSpell(const Spell& spell);
    void removeSpell(std::string name);
    void displayAllSpells() const;
    void saveSpellbook(const std::string& filename) const;
    void loadSpellbook(const std::string& filename);

    std::vector<Spell> getSpellsByLevel(int level) const;
    std::vector<Spell> getAllSpells() const;
};

#endif