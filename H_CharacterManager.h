#ifndef CHARACTER_MANAGER_H
#define CHARACTER_MANAGER_H

#include <vector>
#include "H_Character.h"

class CharacterManager {
private:

    std::vector<Character> characters;
    std::string Ability_scores[6] = {"Strength: ", "Dexterity: ", "Constitution: ", "Intelligence: ", "Wisdom: ", "Charisma: "};
    std::string EditCharDetailsArray[7] = {"Name", "Race", "Class", "Background", "Alignment", "Level", "Age"};
    std::string EditHpArray[6] = {"Max Hp", "Current Hp", "Temperary Hp", "Hit Dice"};

public:

    // Character management
    void createCharacter();
    void viewCharacters() const;
    void editCharacter();
    bool isValidString(const std::string& input);
    
    

    // Save/Load
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);


    // Inventory
    void manageInventory(Character& c);


};

#endif