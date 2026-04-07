#include "H_Gear.h"
#include <iostream>

Gear::Gear(std::string name, std::string description, float weight,
           int quantity, int value, std::string rarity, bool requiresAttunement)
    : Item(name, description, weight, quantity, value, rarity, requiresAttunement) {}

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
