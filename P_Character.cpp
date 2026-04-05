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
    for (size_t i = 0; i < inventory.size(); i++) 
    {
        Item item = inventory.getItem(i + 1);
        file << item.getName() << endl;
        file << item.getType() << endl;
        file << item.getValue() << endl;
    }
    // --- SPELLBOOK ---
    file << "SPELLBOOK\n";

    // Save spellbook to temp file
    spellbook.saveSpellbook("temp_spell.txt");

    // Copy into main file
    ifstream temp("temp_spell.txt");
    string line;
    while (getline(temp, line))
    {
        file << line << endl;
    }
    temp.close();

    // --- SPELLSLOTS (placeholder for now) ---
    file << "SPELLSLOTS\n";
}

// Display
void Character::display() const {



    std::cout << "\n=== Character Sheet ===\n";
    std::cout << "Name: " << name << std::endl;
    std::cout << "Race: " << race << endl;
    std::cout << "Class: " << characterClass << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Background: " << background << std::endl;
    std::cout << "Alignment: " << alignment << std::endl;
    std::cout << "Weight: " << weight << std::endl;
    std::cout << "Current HP/Max HP: " << current_hp << "/" << max_hp << std::endl;
    std::cout << "Temp HP: " << temp_hp << std::endl;
    std::cout << "Hit dice: " << level << hit_dice << std::endl;
    std::cout << "STR: " << strength << "(" << ((strength/2)-5)  << ")" << std::endl;
    std::cout << "DEX: " << dexterity << "(" << ((dexterity/2)-5) << ")" << std::endl;
    std::cout << "CON: " << constitution << "(" << ((constitution/2)-5)<< ")" << std::endl;
    std::cout << "INT: " << intelligence << "(" << ((intelligence/2)-5) << ")" << std::endl;
    std::cout << "WIS: " << wisdom << "(" << ((wisdom/2)-5) << ")" << std::endl;
    std::cout << "CHA: " << charisma << "(" <<((charisma/2)-5) << ")" << std::endl;
    std::cout << "INIT: " << Initiative << std::endl;
    std::cout << "PROF: " << proficiency << std::endl;
    std::cout << "=======================\n";
}


// Getters

std::string Character::getName() const {return name;}
std::string Character::getRace() const {return race;}
std::string Character::getClass() const {return characterClass;}
std::string Character::getBackground() const{return background;}
std::string Character::getAlignment() const{return alignment;}
int Character::getLevel() const {return level;}
int Character::getAge() const{return age;}
int Character::getWeight() const{return weight;}
int Character::getCurrentHP() const{return current_hp;}
int Character::getMaxHP() const{return max_hp;}
int Character::getTempHP() const{return temp_hp;}
std::string Character::getHitDice() const{return hit_dice;}
int Character::getStrength() const {return strength;}
int Character::getDexterity() const {return dexterity;}
int Character::getConstitution() const {return constitution;}
int Character::getIntelligence() const {return intelligence;}
int Character::getWisdom() const {return wisdom;}
int Character::getCharisma() const {return charisma;}
int Character::getInitiative() const {return Initiative;}
int Character::getProficiency() const {return proficiency;}

int Character::getAbilityModifier(int& ability_score)
{
    int Ab_mod;
    int Ab_check = ability_score;
    Ab_mod = (Ab_check - 10)/2; 
    return Ab_mod;
}

// Setters

void Character::setName(const std::string& n) { name = n; }
void Character::setRace(const std::string& r) { race = r; }
void Character::setClass(const std::string& c) { characterClass = c; }
void Character::setBackground(const std::string& b) { background = b;}
void Character::setAlignment(const std::string& a) {alignment = a;}
void Character::setLevel(int lvl){level = lvl;}
void Character::setAge(int a){age = a;}
void Character::setWeight(int w){weight = w;}
void Character::setCurrentHP(int c_hp){current_hp = c_hp;}
void Character::setMaxHP(int m_hp){max_hp = m_hp;}
void Character::setTempHP(int t_hp){temp_hp = t_hp;}
void Character::setHitDice(const std::string& new_hit_dice){hit_dice = new_hit_dice;}
void Character::setStrength(int str) { strength = str; }
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
            std::cout << "Not an ability";
        }
    }
    else 
    {
    std::cout << "Ability score must be between 1 and 20" << std::endl;
    std::cin.clear();
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

//-----------------------------------------------------//
// Spellbook
Spellbook& Character::getSpellbook()
{
    return spellbook;
}

SpellSlots& Character::getSpellSlots()
{
    return spellSlots;
}

void Character::showSpells() const
{
    std::cout << "\n=== Spellbook ===\n";
    spellbook.displayAllSpells();

    std::cout << "\n=== Spell Slots ===\n";
    spellSlots.displaySlots();
}