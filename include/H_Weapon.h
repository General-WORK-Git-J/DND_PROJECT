#ifndef H_WEAPON_H
#define H_WEAPON_H

#include "H_Item.h"

class Weapon : public Item {
private:
    std::string damageDice;    // e.g. "1d6"
    std::string damageType;    // e.g. "Slashing"
    std::string weaponCategory; // Simple / Martial
    std::string weaponType;    // Melee / Ranged
    std::string properties;    // e.g. "Finesse, Light"
    std::string range;         // e.g. "5 ft" or "80/320 ft"

public:
    Weapon(std::string name = "", std::string description = "", float weight = 0.0f,
           int quantity = 1, int value = 0, std::string rarity = "Common", bool requiresAttunement = false,
           std::string damageDice = "", std::string damageType = "",
           std::string weaponCategory = "Simple", std::string weaponType = "Melee",
           std::string properties = "None", std::string range = "5 ft");

    std::string getDamageDice() const;
    std::string getDamageType() const;
    std::string getWeaponCategory() const;
    std::string getWeaponType() const;
    std::string getProperties() const;
    std::string getRange() const;

    std::string getItemTag() const override;
    void display() const override;
    void saveData(std::ofstream& file) const override;
    void loadData(std::ifstream& file) override;
};

#endif
