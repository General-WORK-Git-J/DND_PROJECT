#include "H_Weapon.h"
#include <iostream>

Weapon::Weapon(std::string name, std::string description, float weight,
               int quantity, int value, std::string rarity, bool requiresAttunement,
               std::string damageDice, std::string damageType,
               std::string weaponCategory, std::string weaponType,
               std::string properties, std::string range)
    : Item(name, description, weight, quantity, value, rarity, requiresAttunement),
      damageDice(damageDice), damageType(damageType), weaponCategory(weaponCategory),
      weaponType(weaponType), properties(properties), range(range) {}

std::string Weapon::getDamageDice() const     { return damageDice; }
std::string Weapon::getDamageType() const     { return damageType; }
std::string Weapon::getWeaponCategory() const { return weaponCategory; }
std::string Weapon::getWeaponType() const     { return weaponType; }
std::string Weapon::getProperties() const     { return properties; }
std::string Weapon::getRange() const          { return range; }

std::string Weapon::getItemTag() const { return "WEAPON"; }

void Weapon::display() const {
    std::cout << "[Weapon]\n";
    displayCommon();
    std::cout << "  Damage:      " << damageDice << " " << damageType << "\n";
    std::cout << "  Category:    " << weaponCategory << " " << weaponType << "\n";
    std::cout << "  Properties:  " << properties << "\n";
    std::cout << "  Range:       " << range << "\n";
}

void Weapon::saveData(std::ofstream& file) const {
    saveCommon(file);
    file << damageDice << "\n";
    file << damageType << "\n";
    file << weaponCategory << "\n";
    file << weaponType << "\n";
    file << properties << "\n";
    file << range << "\n";
}

void Weapon::loadData(std::ifstream& file) {
    loadCommon(file);
    std::getline(file, damageDice);
    std::getline(file, damageType);
    std::getline(file, weaponCategory);
    std::getline(file, weaponType);
    std::getline(file, properties);
    std::getline(file, range);
}
