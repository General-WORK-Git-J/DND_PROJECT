#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item { 
private:
    std::string name;
    std::string type;
    int value;

public:

    // Constructors
    Item(std::string n = "", std::string t = "", int v = 0);

    // Getters
    std::string getName() const;
    std::string getType() const;
    int getValue() const;

    void display() const;
};

#endif