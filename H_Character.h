#ifndef _CHARACTER_
#define _CHARACTER_



#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "H_stats.h"
#include "H_equipment_tracker.h"


using namespace std;


class Character
{
    private:

    // Member variables
    string Name;
    string Class;
    string Race; 
    int Age;
    int Weight;
    int Level;

    vector <equipment*> equipment_items;

    Player_stats Character_stats;
    Player_stats* Character_stat_ptr;

    Equipment_tracker Character_equipment;
    Equipment_tracker* Character_equip_ptr;
    
    

    public:

    // Constructors
    Character();
    Character(string name, string char_class,string race, int age, int weight,int level, Player_stats AS, Equipment_tracker ET); // Set up character object with an assigned stats object

    // Setters 
    void setCharName(string n);
    void setCharClass(string c);
    void setRace(string r);
    void setAge(int a);
    void setWeight(int w);
    void setLevel(int level);
    void setStatObj(Player_stats stat);
    void setEquipmentTrackObj(Equipment_tracker equip);




    void setCharacterComponents();

    // Getters
    string getCharName();
    string getCharClass();
    string getRace();
    int getAge();
    int getWeight();
    int getLevel();
    Player_stats* getStatObj();
    Equipment_tracker* getEquipmentTrackerObj();
    void getDetails();
    void getStats();


    void addItem(equipment* item);
    void removeItem(int item_index);


    void displayEquipment();




};

#endif