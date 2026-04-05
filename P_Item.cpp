#include "H_Item.h"
#include <iostream>

using namespace std;

Item::Item(string n, string t, int v) 
{
    name = n;
    type = t;
    value = v;
}

std::string Item::getName() const {return name;}
std::string Item::getType() const {return type;}
int Item::getValue() const {return value;}

void Item::display() const {
    std::cout << name << " (" << type << ") - Value: " << value << std::endl;
}