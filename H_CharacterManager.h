#ifndef CHARACTER_MANAGER_H
#define CHARACTER_MANAGER_H

#include <vector>
#include "H_Character.h"

class CharacterManager {
private:
    std::vector<Character> characters;

    std::string Ability_scores[6] = {"Strength: ", "Dexterity: ", "Constitution: ", "Intelligence: ", "Wisdom: ", "Charisma: "};

public:
    void createCharacter();
    void viewCharacters() const;
    void editCharacter();

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    void manageInventory(Character& c);
};

#endif