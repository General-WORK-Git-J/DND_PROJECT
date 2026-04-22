#include "H_Weapon.h"
#include <iostream>

Weapon::Weapon(std::string name_, std::string description_, float weight_,
               int quantity_, int value_, std::string rarity_, bool requiresAttunement_,
               std::string damageDice_, std::string damageType_,
               std::string weaponCategory_, std::string weaponType_,
               std::string properties_, std::string range_)
    : Item(name_, description_, weight_, quantity_, value_, rarity_, requiresAttunement_),
      damageDice(damageDice_), damageType(damageType_), weaponCategory(weaponCategory_),
      weaponType(weaponType_), properties(properties_), range(range_) {}

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
