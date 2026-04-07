#include "H_Item.h"
#include "H_Weapon.h"
#include "H_Armor.h"
#include "H_Gear.h"
#include <iostream>

Item::Item(std::string name, std::string description, float weight,
           int quantity, int value, std::string rarity, bool requiresAttunement)
    : name(name), description(description), weight(weight),
      quantity(quantity), value(value), rarity(rarity), requiresAttunement(requiresAttunement) {}

std::string Item::getName() const            { return name; }
std::string Item::getDescription() const     { return description; }
float       Item::getWeight() const          { return weight; }
int         Item::getQuantity() const        { return quantity; }
int         Item::getValue() const           { return value; }
std::string Item::getRarity() const          { return rarity; }
bool        Item::getRequiresAttunement() const { return requiresAttunement; }

void Item::setQuantity(int qty) { quantity = qty; }

void Item::displayCommon() const {
    std::cout << "  Name:        " << name << "\n";
    std::cout << "  Description: " << description << "\n";
    std::cout << "  Rarity:      " << rarity << "\n";
    std::cout << "  Weight:      " << weight << " lb\n";
    std::cout << "  Quantity:    " << quantity << "\n";
    std::cout << "  Value:       " << value << " gp\n";
    std::cout << "  Attunement:  " << (requiresAttunement ? "Yes" : "No") << "\n";
}

void Item::display() const {
    displayCommon();
}

void Item::saveCommon(std::ofstream& file) const {
    file << name << "\n";
    file << description << "\n";
    file << weight << "\n";
    file << quantity << "\n";
    file << value << "\n";
    file << rarity << "\n";
    file << requiresAttunement << "\n";
}

void Item::loadCommon(std::ifstream& file) {
    std::getline(file, name);
    std::getline(file, description);
    file >> weight >> quantity >> value;
    file.ignore();
    std::getline(file, rarity);
    file >> requiresAttunement;
    file.ignore();
}

void Item::saveData(std::ofstream& file) const {
    saveCommon(file);
}

void Item::loadData(std::ifstream& file) {
    loadCommon(file);
}

void Item::save(std::ofstream& file) const {
    file << getItemTag() << "\n";
    saveData(file);
}

std::unique_ptr<Item> Item::loadFromFile(std::ifstream& file) {
    std::string tag;
    std::getline(file, tag);

    std::unique_ptr<Item> item;
    if (tag == "WEAPON")      item = std::make_unique<Weapon>();
    else if (tag == "ARMOR")  item = std::make_unique<Armor>();
    else                      item = std::make_unique<Gear>();

    item->loadData(file);
    return item;
}
