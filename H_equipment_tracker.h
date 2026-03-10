#ifndef _EQUIPMENT_TRACKER_
#define _EQUIPMENT_TRACKER_

#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

#include "H_equipment.h"

using namespace std;

class Equipment_tracker
{
    private:

    vector <equipment> character_items;
    vector <equipment*> character_item_ptrs;

    public:

    // Constructors
    Equipment_tracker();
    Equipment_tracker(vector <equipment> item);

    // add and remove from equipment list 
    void addItem(equipment* item);
    void removeItem(int item_index);

    // Display items in characters possession

    void DisplayItems();
};





#endif 