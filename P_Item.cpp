#include "H_Item.h"
#include <iostream>

using namespace std;

Item::Item(string n, string t, int v) {
    name = n;
    type = t;
    value = v;
}

string Item::getName() const { return name; }
string Item::getType() const { return type; }
int Item::getValue() const { return value; }

void Item::display() const {
    cout << name << " (" << type << ") - Value: " << value << endl;
}