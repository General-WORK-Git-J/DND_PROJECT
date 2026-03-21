#include "H_Character.h"
#include <iostream>

using namespace std;

// Constructor
Character::Character(string n, string r, string c,string b, string a,
     int lvl, int new_age, int new_weight,int c_hp, int m_hp,int t_hp, string h_dice, int str, int dex, int con, int intl, int wis, int cha, int init, int prof) {
    name = n;
    race = r;
    characterClass = c;
    background = b;
    alignment = a;
    level = lvl;
    age = new_age;
    weight = new_weight;
    current_hp = c_hp;
    max_hp = m_hp;
    temp_hp = t_hp;
    hit_dice = h_dice;
    strength = str;
    dexterity = dex;
    constitution = con;
    intelligence = intl;
    wisdom = wis;
    charisma = cha;
    Initiative = init;
    proficiency = prof;
}



// Save character to file
void Character::save(ofstream& file) const {
    file << name << endl;
    file << race << endl;
    file << characterClass << endl;
    file << background << endl;
    file << alignment << endl;
    file << level << " "
         << age << " "
         << weight << endl;
    file << current_hp << " "
         << max_hp << " "
         << temp_hp << endl;
    file << hit_dice << endl;
    file << strength << " "
         << dexterity << " "
         << constitution << " "
         << intelligence << " "
         << wisdom << " "
         << charisma << " "
         << Initiative << " "
         << proficiency << endl;
    file << inventory.size() << endl;
    for (int i = 0; i < inventory.size(); i++) 
    {
        Item item = inventory.getItem(i);
        file << item.getName() << endl;
        file << item.getType() << endl;
        file << item.getValue() << endl;
    }
}

// Display
void Character::display() const {



    cout << "\n=== Character Sheet ===\n";
    cout << "Name: " << name << endl;
    cout << "Race: " << race << endl;
    cout << "Class: " << characterClass << endl;
    cout << "Level: " << level << endl;
    cout << "Age: " << age << endl;
    cout << "Background: " << background << endl;
    cout << "Alignment: " << alignment << endl;
    cout << "Weight: " << weight << endl;
    cout << "Current HP/Max HP: " << current_hp << "/" << max_hp << endl;
    cout << "Temp HP: " << temp_hp << endl;
    cout << "Hit dice: " << level << hit_dice << endl;
    cout << "STR: " << strength << "(" << ((strength/2)-5)  << ")" << endl;
    cout << "DEX: " << dexterity << "(" << ((dexterity/2)-5) << ")" <<endl;
    cout << "CON: " << constitution << "(" << ((constitution/2)-5)<< ")" << endl;
    cout << "INT: " << intelligence << "(" << ((intelligence/2)-5) << ")" << endl;
    cout << "WIS: " << wisdom << "(" << ((wisdom/2)-5) << ")" << endl;
    cout << "CHA: " << charisma << "(" <<((charisma/2)-5) << ")" <<endl;
    cout << "INIT: " << Initiative << endl;
    cout << "PROF: " << proficiency << endl;
    cout << "=======================\n";
}


// Getters

string Character::getName() const { return name; }
string Character::getRace() const { return race; }
string Character::getClass() const { return characterClass; }
string Character::getBackground() const{return background;}
string Character::getAlignment() const{return alignment;}
int Character::getLevel() const { return level; }
int Character::getAge() const{return age;}
int Character::getWeight() const{return weight;}
int Character::getCurrentHP() const{return current_hp;}
int Character::getMaxHP() const{return max_hp;}
int Character::getTempHP() const{return temp_hp;}
int Character::getStrength() const { return strength; }
int Character::getDexterity() const { return dexterity; }
int Character::getConstitution() const { return constitution; }
int Character::getIntelligence() const { return intelligence; }
int Character::getWisdom() const { return wisdom; }
int Character::getCharisma() const { return charisma; }
int Character::getInitiative() const { return Initiative; }
int Character::getProficiency() const { return proficiency; }

int Character::getAbilityModifier(int& ability_score)
{
    int Ab_mod;
    int Ab_check = ability_score;
    Ab_mod = (Ab_check - 10)/2; 
    return Ab_mod;
}

// Setters

void Character::setName(const string& n) { name = n; }
void Character::setRace(const string& r) { race = r; }
void Character::setClass(const string& c) { characterClass = c; }
void Character::setBackground(const string& b) { background = b;}
void Character::setAlignment(const string& a) {alignment = a;}
void Character::setLevel(int lvl){level = lvl;}
void Character::setAge(int a){age = a;}
void Character::setWeight(int w){weight = w;}
void Character::setCurrentHP(int c_hp){current_hp = c_hp;}
void Character::setMaxHP(int m_hp){max_hp = m_hp;}
void Character::setTempHP(int t_hp){temp_hp = t_hp;}
void Character::setStrength(int str) {strength = str;}
void Character::setDexterity(int dex) {dexterity = dex;}
void Character::setConstitution(int con) {constitution = con;}
void Character::setIntelligence(int intl) {intelligence = intl;}
void Character::setWisdom(int wis) {wisdom = wis;}
void Character::setCharisma(int cha) {charisma = cha;}
void Character::setInitiative(int init) {Initiative = init;}
void Character::setProficiency(int prof) {proficiency = prof;}



// Inventory
void Character::addItem(const Item& item) {
    inventory.addItem(item);
}

void Character::removeItem(int index) {
    inventory.removeItem(index);
}

void Character::showInventory() const {
    inventory.display();
}

void Character::clearInventory() {
    while (inventory.size() > 0) {
        inventory.removeItem(0);
    }
}

// Ability scores
void Character::setStats(int AS, int Ability)
{
    if(AS <= 20 && AS > 0)
    {
        switch (Ability)
        {
        case 1:
            strength = AS;
            break;

        case 2:
            dexterity = AS;
            break;

        case 3:
            constitution = AS;
            break;

        case 4:
            intelligence = AS;
            break;

        case 5:
            wisdom = AS;
            break;

        case 6:
            charisma = AS;
            break;

        default:
            cout << "Not an ability";
        }
    }
    else 
    {
    cout << "Ability score must be between 1 and 20" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}