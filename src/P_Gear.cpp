#include "H_Gear.h"
#include <iostream>

Gear::Gear(std::string name_, std::string description_, float weight_,
           int quantity_, int value_, std::string rarity_, bool requiresAttunement_)
    : Item(name_, description_, weight_, quantity_, value_, rarity_, requiresAttunement_) {}

std::string Gear::getItemTag() const { return "GEAR"; }

void Gear::display() const {
    std::cout << "[Gear]\n";
    displayCommon();
}

void Gear::saveData(std::ofstream& file) const {
    saveCommon(file);
}

void Gear::loadData(std::ifstream& file) {
    loadCommon(file);
}
