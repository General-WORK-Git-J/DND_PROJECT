#include "H_SpellBook.h"
#include <fstream>

void Spellbook::addSpell(const Spell& spell)
{
    knownSpells.push_back(spell);
}

void Spellbook::removeSpell(std::string name)
{
    for (auto it = knownSpells.begin(); it != knownSpells.end(); ++it)
    {
        if (it->getSpellName() == name)
        {
            knownSpells.erase(it);
            return;
        }
    }
}

void Spellbook::displayAllSpells() const
{
    for (const auto& spell : knownSpells)
    {
        spell.DisplaySpellProperties();
        std::cout << "------------------\n";
    }
}

std::vector<Spell> Spellbook::getSpellsByLevel(int level) const
{
    std::vector<Spell> result;

    for (const auto& spell : knownSpells)
    {
        if (spell.getSpellLevel() == level)
        {
            result.push_back(spell);
        }
    }

    return result;
}

std::vector<Spell> Spellbook::getAllSpells() const
{
    return knownSpells;
}

//-----------------------------------------------------//
// Save Spellbook to file
void Spellbook::saveSpellbook(const std::string& filename) const
{
    std::ofstream outFile(filename);

    if (!outFile)
    {
        std::cout << "Error opening file for writing!\n";
        return;
    }

    outFile << knownSpells.size() << "\n";

    for (const auto& spell : knownSpells)
    {
        spell.saveToFile(outFile);
    }

    outFile.close();
}

//-----------------------------------------------------//
// Load Spellbook from file
void Spellbook::loadSpellbook(const std::string& filename)
{
    std::ifstream inFile(filename);

    if (!inFile)
    {
        std::cout << "Error opening file for reading!\n";
        return;
    }

    knownSpells.clear();

    int count;
    inFile >> count;
    inFile.ignore();

    for (int i = 0; i < count; i++)
    {
        Spell spell;
        spell.loadFromFile(inFile);
        knownSpells.push_back(spell);
    }

    inFile.close();
}