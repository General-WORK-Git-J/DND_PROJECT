#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <memory>
#include "H_Item.h"

class Inventory {
private:
    std::vector<std::unique_ptr<Item>> items;

public:
    void addItem(std::unique_ptr<Item> item);
    void removeItem(int index);
    void display() const;

    int size() const;
    const Item& getItem(int index) const;

    void save(std::ofstream& file) const;
    void load(std::ifstream& file);
};

#endif
