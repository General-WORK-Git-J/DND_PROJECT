#include "H_Armor.h"
#include <iostream>

Armor::Armor(std::string name, std::string description, float weight,
             int quantity, int value, std::string rarity, bool requiresAttunement,
             std::string armorType, int baseAC,
             int maxDexBonus, int strRequirement, bool stealthDisadvantage)
    : Item(name, description, weight, quantity, value, rarity, requiresAttunement),
      armorType(armorType), baseAC(baseAC), maxDexBonus(maxDexBonus),
      strRequirement(strRequirement), stealthDisadvantage(stealthDisadvantage) {}

std::string Armor::getArmorType() const       { return armorType; }
int         Armor::getBaseAC() const          { return baseAC; }
int         Armor::getMaxDexBonus() const     { return maxDexBonus; }
int         Armor::getStrRequirement() const  { return strRequirement; }
bool        Armor::getStealthDisadvantage() const { return stealthDisadvantage; }

std::string Armor::getItemTag() const { return "ARMOR"; }

void Armor::display() const {
    std::cout << "[Armor]\n";
    displayCommon();
    std::cout << "  Armor Type:  " << armorType << "\n";
    std::cout << "  Base AC:     " << baseAC << "\n";
    std::cout << "  Max Dex Bon: " << (maxDexBonus == -1 ? "No limit" : std::to_string(maxDexBonus)) << "\n";
    std::cout << "  Str Req:     " << (strRequirement == 0 ? "None" : std::to_string(strRequirement)) << "\n";
    std::cout << "  Stealth:     " << (stealthDisadvantage ? "Disadvantage" : "Normal") << "\n";
}

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
