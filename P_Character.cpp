#include "H_Character.h"
#include "H_stats.h"
#include "H_equipment.h"



//Constructor definitions
Character::Character()
{
    Name = "";
    Age = 0;
    Weight = 0;
    Level = 1;
}

Character::Character(string name,string char_class,string race, int age, int weight, int level, Player_stats AS)
{
    Name = name;
    Class = char_class;
    Age = age;
    Weight = weight;
    Level = level;
    Character_stats = AS;
   
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



void Character::setCharacterComponents(string name)
{
    
    string char_class;
    string race;
    int age;
    int weight;
    int level;

    setCharName(name);

    for (int i = 1; i <=5; i++)
    {
    switch (i)
        {

        case 1:
        cout << "Enter character class: ";
        cin >> char_class;
        if (IsString(char_class))
            {
            setCharClass(char_class);
            }
            else 
            {
                cout << "Not a valid input, please enter a string" << endl;
                i--;
            }
        break;

        case 2:
        cout << "Enter character race: ";
        cin >> race;
        if (IsString(race))
            {
            setCharClass(race);
            }
            else 
            {
                cout << "Not a valid input, please enter a string" << endl;
                i--;
            }
        break;

        case 3:
        cout << "Enter character age: ";
        cin >> age;
        if (age > 0)
        {
        setAge(age);
        }
        else 
        {
            cout << "Not a valid input, please enter an integer greater than 0" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            i--;
        }
        break;

        case 4:
        cout << "Enter character weight (kg): ";
        cin >> weight;
        if (weight > 0)
        {
        setWeight(weight);
        }
        else
        {
            cout << "Not a valid input, please enter an integer greater than 0" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            i--;
        }
        break;

        case 5:
        cout << "Enter character level: ";
        cin >> level;
        if (level >=1 && level <= 20)
        {
        setLevel(level);
        }
        else 
        {
            cout << "Level must be between 1 and 20, please enter a valid number" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            i--;
        }
        break;


        default:
        break;
        }
    }   
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





void Character::addItem_to_Map(string new_id)
{
    Equipment_item.emplace(new_id,make_unique<equipment>(new_id, "test_use"));
}

void Character::display_items_in_map()
{
  for (const auto& [key, item] : Equipment_item)
{
    cout << "Key: " << key << endl;

    if (item)
    {
        item->displayEquipmentDetails();
    }
}
}

bool Character::IsString(const string &input)
{
    for (char c : input) {
        if (isdigit(c)) {  // if any character is a digit
            return false;
        }
    }
    return true;
}


