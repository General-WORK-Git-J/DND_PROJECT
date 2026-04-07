#ifndef H_ARMOR_H
#define H_ARMOR_H

#include "H_Item.h"

class Armor : public Item {
private:
    std::string armorType;     // Light / Medium / Heavy / Shield
    int baseAC;
    int maxDexBonus;           // -1 means no limit
    int strRequirement;        // 0 means no requirement
    bool stealthDisadvantage;

public:
    Armor(std::string name = "", std::string description = "", float weight = 0.0f,
          int quantity = 1, int value = 0, std::string rarity = "Common", bool requiresAttunement = false,
          std::string armorType = "Light", int baseAC = 10,
          int maxDexBonus = -1, int strRequirement = 0, bool stealthDisadvantage = false);

    std::string getArmorType() const;
    int getBaseAC() const;
    int getMaxDexBonus() const;
    int getStrRequirement() const;
    bool getStealthDisadvantage() const;

    std::string getItemTag() const override;
    void display() const override;
    void saveData(std::ofstream& file) const override;
    void loadData(std::ifstream& file) override;
};

#endif
