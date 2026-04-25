#ifndef CHARACTER_MANAGER_H
#define CHARACTER_MANAGER_H

#include <vector>
#include "H_Character.h"

class CharacterManager {
private:

    std::vector<Character> characters;
    std::string Ability_scores[6] = {"Strength: ", "Dexterity: ", "Constitution: ", "Intelligence: ", "Wisdom: ", "Charisma: "};
    std::string EditCharDetailsArray[9] = {"Name", "Race", "Class", "Background", "Alignment", "Age", "Weight", "Level", "Speed"};
    std::string EditHpArray[4] = {"Max Hp", "Current Hp", "Temporary Hp", "Hit Dice"};

public:

    // Character management
    void createCharacter();
    void viewCharacters() const;
    void editCharacter();
    void manageGlobalSpells();
    bool hasCharacters() const;

    // Utilities
    std::string getValidStringInput(const std::string& value_to_get); // Re-usable method to get a string input with built in error checking
    std::string getValidNameInput(const std::string& value_to_get); // Like getValidStringInput but also allows digits and symbols
    std::string getValidHitDiceInput(); // Gets a valid hit dice input in the format dN (e.g. d12)
    int getValidIntegerInput(const std::string& value_to_get); // Re-usable method to get a postive non-zero integer input
    bool isValidString(const std::string& input); // Checks to see if an input is a valid string then returns a bool
    bool isValidName(const std::string& input); // Like isValidString but also allows digits and symbols
    bool isValidHitDice(const std::string& input); // Checks for hit dice format: 'd' followed by digits (e.g. d6, d12)
    void Invalidinput(); // Re-usable method to clear the input buffer fo invalid inputs;
    
    

    // Save/Load
    void saveCharacter(const Character& c) const;
    void saveAll() const;
    void loadAll();
    std::vector<std::string> listCharacterNames() const;


    // Inventory
    void manageInventory(Character& c);
    void manageFeatures(Character& c);


};

#endif
