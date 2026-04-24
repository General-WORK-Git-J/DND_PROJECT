#include "H_Armor.h"
#include <iostream>


// Armour constructor
Armor::Armor(std::string name_, std::string description_, float weight_,
             int quantity_, int value_, std::string rarity_, bool requiresAttunement_,
             std::string armorType_, int baseAC_,
             int maxDexBonus_, int strRequirement_, bool stealthDisadvantage_)
    : Item(name_, description_, weight_, quantity_, value_, rarity_, requiresAttunement_),
      armorType(armorType_), baseAC(baseAC_), maxDexBonus(maxDexBonus_),
      strRequirement(strRequirement_), stealthDisadvantage(stealthDisadvantage_) {}

// Getters
std::string Armor::getArmorType() const       { return armorType; }
int         Armor::getBaseAC() const          { return baseAC; }
int         Armor::getMaxDexBonus() const     { return maxDexBonus; }
int         Armor::getStrRequirement() const  { return strRequirement; }
bool        Armor::getStealthDisadvantage() const { return stealthDisadvantage; }

std::string Armor::getItemTag() const { return "ARMOR"; }

// Display
void Armor::display() const {
    std::cout << "[Armor]\n";
    displayCommon();
    std::cout << "  Armor Type:  " << armorType << "\n";
    std::cout << "  Base AC:     " << baseAC << "\n";
    std::cout << "  Max Dex Bon: " << (maxDexBonus == -1 ? "No limit" : std::to_string(maxDexBonus)) << "\n";
    std::cout << "  Str Req:     " << (strRequirement == 0 ? "None" : std::to_string(strRequirement)) << "\n";
    std::cout << "  Stealth:     " << (stealthDisadvantage ? "Disadvantage" : "Normal") << "\n";
}

// Save/Load item
void Armor::saveData(std::ofstream& file) const {
    saveCommon(file);
    file << armorType << "\n";
    file << baseAC << "\n";
    file << maxDexBonus << "\n";
    file << strRequirement << "\n";
    file << stealthDisadvantage << "\n";
}


void Armor::loadData(std::ifstream& file) {
    loadCommon(file);
    std::getline(file, armorType);
    file >> baseAC >> maxDexBonus >> strRequirement >> stealthDisadvantage;
    file.ignore();
}
