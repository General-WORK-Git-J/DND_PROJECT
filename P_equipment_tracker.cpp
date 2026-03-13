#include "H_equipment_tracker.h"

Equipment_tracker::Equipment_tracker()
{
}

Equipment_tracker::Equipment_tracker(vector<equipment> item)
{
    character_items = item;
}

void Equipment_tracker::addItem(equipment* item)
{
    character_item_ptrs.push_back(item);
}

void Equipment_tracker::removeItem(int item_index)
{
    size_t iterator = item_index - 1;
    equipment* remove_ptr = character_item_ptrs[iterator];
    
    character_item_ptrs.erase(remove(character_item_ptrs.begin(),character_item_ptrs.end(), remove_ptr), character_item_ptrs.end());
}

void Equipment_tracker::DisplayItems()
{
    for (size_t i = 0; i < size(character_item_ptrs); ++i)
    {
        cout << i + 1 << ": " << endl;
        character_item_ptrs[i]->displayEquipmentDetails();
    }
}
