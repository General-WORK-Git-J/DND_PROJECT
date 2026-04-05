#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "H_Item.h"

class Inventory {
private:
    std::vector<Item> items;

public:

    // Item management
    void addItem(const Item& item);
    void removeItem(int index);
    void display() const;

    int size() const;
    Item getItem(int index) const; 
};

#endif