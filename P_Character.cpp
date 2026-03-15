#include "H_Character.h"
#include "H_stats.h"
#include "H_equipment_tracker.h"


//Constructor definitions
Character::Character()
{
    Name = "";
    Age = 0;
    Weight = 0;
    Level = 1;
}

Character::Character(string name,string char_class,string race, int age, int weight, int level, Player_stats AS, Equipment_tracker ET)
{
    Name = name;
    Class = char_class;
    Age = age;
    Weight = weight;
    Level = level;
    Character_stats = AS;
    Character_equipment = ET;
}


//Setter definitions
void Character::setCharName(string n)
{
    Name = n;
}

void Character::setCharClass(string c)
{
    Class = c;
}

void Character::setRace(string r)
{
    Race = r;
}

void Character::setAge(int a)
{
    Age = a;
}

void Character::setWeight(int w)
{
    Weight = w;
}

void Character::setLevel(int l)
{
    Level = l;
}

void Character::setStatObj(Player_stats stat)
{
    
    Character_stat_ptr = &stat;
}

void Character::setEquipmentTrackObj(Equipment_tracker equip)
{
    Character_equip_ptr = &equip;
}

void Character::setCharacterComponents()
{
    string name;
    string char_class;
    string race;
    int age;
    int weight;
    int level;

    cout << "Enter character name: ";
    cin >> name;
    setCharName(name);

    cout << "Enter character class: ";
    cin >> char_class;
    setCharClass(char_class);

    cout << "Enter character race: ";
    cin >> race;
    setRace(race);

    cout << "Enter character age: ";
    cin >> age;
    setAge(age);

    cout << "Enter character weight (kg): ";
    cin >> weight;
    setWeight(weight);

    cout << "Enter character level: ";
    cin >> level;
    setLevel(level);
    
    }

//Getter definitions
string Character::getCharName()
{
    return Name;
}

string Character::getCharClass()
{
    return Class;
}

string Character::getRace()
{
    return Race;
}

int Character::getAge()
{
    return Age;
}

int Character::getWeight()
{
    return Weight;
}

int Character::getLevel()
{
    return Level;
}

Player_stats* Character::getStatObj()
{
    return Character_stat_ptr;
}

Equipment_tracker* Character::getEquipmentTrackerObj()
{
    return Character_equip_ptr;
}

void Character::getDetails()
{
    cout << "Name: " << getCharName() << endl;
    cout << "Class: " << getCharClass() << endl;
    cout << "Race: " << getRace() << endl;
    cout << "Age: "<< getAge() << endl;
    cout << "Weight: " << getWeight() << endl;
    cout << "Level: " << getLevel() << endl;
}

void Character::getStats()

{
     
    Character_stats.displayAbilityScores();
}

void Character::addItem(equipment* item)
{
    equipment_items.push_back(item);
}

void Character::removeItem(int item_index)
{
    size_t iterator = item_index - 1;
    equipment* remove_ptr = equipment_items[iterator];
    
    equipment_items.erase(remove(equipment_items.begin(),equipment_items.end(), remove_ptr), equipment_items.end());
}

void Character::displayEquipment()
{
      for (size_t i = 0; i < size(equipment_items); ++i)
    {
        cout << i + 1 << ": " << endl;
        equipment_items[i]->displayEquipmentDetails();
    }
}

