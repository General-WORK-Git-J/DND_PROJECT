#ifndef _CHARACTER_
#define _CHARACTER_



#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>
#include <cctype>

#include "H_stats.h"
#include "H_equipment.h"



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



    map<string, unique_ptr<equipment>> Equipment_item;

    Player_stats Character_stats;
    Player_stats* Character_stat_ptr;

    
    
    

    public:

    // Constructors
    Character();
    Character(string name, string char_class,string race, int age, int weight,int level, Player_stats AS); // Set up character object with an assigned stats object

    // Setters 
    void setCharName(string n);
    void setCharClass(string c);
    void setRace(string r);
    void setAge(int a);
    void setWeight(int w);
    void setLevel(int level);
    void setStatObj(Player_stats stat);
   




    void setCharacterComponents(string name);

    // Getters
    string getCharName();
    string getCharClass();
    string getRace();
    int getAge();
    int getWeight();
    int getLevel();
    Player_stats* getStatObj();
   
    void getDetails();
    void getStats();



    void addItem_to_Map(string new_item_id);
    void display_items_in_map();

    bool IsString(const string& input);
    




};

#endif