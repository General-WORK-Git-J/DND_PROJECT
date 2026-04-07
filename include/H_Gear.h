#ifndef H_GEAR_H
#define H_GEAR_H

#include "H_Item.h"

class Gear : public Item {
public:
    Gear(std::string name = "", std::string description = "", float weight = 0.0f,
         int quantity = 1, int value = 0, std::string rarity = "Common", bool requiresAttunement = false);

    std::string getItemTag() const override;
    void display() const override;
    void saveData(std::ofstream& file) const override;
    void loadData(std::ifstream& file) override;
};

#endif
