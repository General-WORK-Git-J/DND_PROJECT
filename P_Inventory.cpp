#include "H_Inventory.h"
#include <iostream>

using namespace std;

void Inventory::addItem(const Item& item) {
    items.push_back(item);
}

void Inventory::removeItem(int index) {
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);
    }
}

void Inventory::display() const {
    if (items.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }

    for (size_t i = 0; i < items.size(); i++) {
        cout << i << ": ";
        items[i].display();
    }
}

int Inventory::size() const {
    return items.size();
}

Item Inventory::getItem(int index) const {
    return items[index];
}