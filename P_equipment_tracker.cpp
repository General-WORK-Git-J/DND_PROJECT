#include "H_equipment_tracker.h"

Equipment_tracker::Equipment_tracker()
{
}

Equipment_tracker::Equipment_tracker(vector<equipment> item)
{
    character_items = item;
}

void Equipment_tracker::addItem(equipment item)
{
    character_items.push_back(item);
}

void Equipment_tracker::removeItem(size_t item_index)
{
     if (item_index - 1 < character_items.size())
    {
        character_items.erase(character_items.begin() + (item_index - 1));
    }
    else
    {
        std::cout << "Invalid item index\n";
    }
}

void Equipment_tracker::DisplayItems()
{
    for (size_t i = 0; i < character_items.size(); ++i)
    {
        cout << i + 1 << ": " << endl;
        character_items[i].displayEquipmentDetails();
    }
}
