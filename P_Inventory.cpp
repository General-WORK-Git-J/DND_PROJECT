#include "H_Inventory.h"
#include <iostream>

void Inventory::addItem(const Item& item) {
    items.push_back(item);
}

void Inventory::removeItem(int index) {
    if (index - 1 >= 0 && index - 1 < items.size()) {
        items.erase(items.begin() + index - 1);
    }
}

void Inventory::display() const {
    if (items.empty()) {
        std::std::cout << "Inventory is empty.\n";
        return;
    }

    for (size_t i = 0; i < items.size(); i++) {
        std::cout << i + 1 << ": ";
        items[i].display();
    }
}

int Inventory::size() const {
    return items.size();
}

Item Inventory::getItem(int index) const {
    return items[index - 1];
}