#include "H_Character.h"
#include "H_Weapon.h"
#include "H_Armor.h"
#include "H_Gear.h"
#include <iostream>

// Constructor
Character::Character(std::string n, std::string r, std::string c, std::string b, std::string a,
     int lvl, int new_age, int new_weight, int c_hp, int m_hp, int t_hp, std::string h_dice, int str, int dex, int con, int intl, int wis, int cha, int init, int prof) {
    name = n;
    race = r;
    characterClass = c;
    background = b;
    alignment = a;
    level = lvl;
    hit_die_num = lvl;
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
void Character::save(std::ofstream& file) const {
    file << name << std::endl;
    file << race << std::endl;
    file << characterClass << std::endl;
    file << background << std::endl;
    file << alignment << std::endl;
    file << level << " "
         << age << " "
         << weight << std::endl;
    file << current_hp << " "
         << max_hp << " "
         << temp_hp << std::endl;
    file << hit_dice << " " << hit_die_num << std::endl;
    file << strength << " "
         << dexterity << " "
         << constitution << " "
         << intelligence << " "
         << wisdom << " "
         << charisma << " "
         << Initiative << " "
         << proficiency << std::endl;
    inventory.save(file);
    // --- WALLET ---
    file << "WALLET\n";
    wallet.save(file);

    // --- SPELLBOOK ---
    file << "SPELLBOOK\n";

    // Save spellbook to temp file
    spellbook.saveSpellbook("data/temp_spell.txt");

    // Copy into main file
    std::ifstream temp("data/temp_spell.txt");
    std::string line;
    while (std::getline(temp, line))
    {
        file << line << std::endl;
    }
    temp.close();

    // Spell slots are stored after the spellbook marker block for each character.
    file << "SPELLSLOTS\n";
    spellSlots.save(file);

    // Features stores feats, racial traits, and the character's skill ranks.
    file << "FEATURES\n";
    features.save(file);
}

// Display
void Character::display() const {



    auto mod = [](int score) -> std::string {
        int m = (score / 2) - 5;
        return (m >= 0 ? "+" : "") + std::to_string(m);
    };

    std::cout << "\n=== Character Sheet ===\n";
    std::cout << "Name: "       << name           << "\n";
    std::cout << "Race: "       << race           << "\n";
    std::cout << "Class: "      << characterClass << "\n";
    std::cout << "Level: "      << level          << "\n";
    std::cout << "Age: "        << age            << "\n";
    std::cout << "Background: " << background     << "\n";
    std::cout << "Alignment: "  << alignment      << "\n";
    std::cout << "Weight: "     << weight         << " lbs\n";
    std::cout << "HP: "         << current_hp << "/" << max_hp;
    if (temp_hp > 0) std::cout << "  (+" << temp_hp << " temp)";
    std::cout << "\n";
    std::cout << "Hit Dice: "   << hit_die_num << "/" << level << hit_dice << "\n";
    std::cout << "STR: " << strength     << " (" << mod(strength)     << ")\n";
    std::cout << "DEX: " << dexterity    << " (" << mod(dexterity)    << ")\n";
    std::cout << "CON: " << constitution << " (" << mod(constitution) << ")\n";
    std::cout << "INT: " << intelligence << " (" << mod(intelligence) << ")\n";
    std::cout << "WIS: " << wisdom       << " (" << mod(wisdom)       << ")\n";
    std::cout << "CHA: " << charisma     << " (" << mod(charisma)     << ")\n";
    std::cout << "Initiative: +" << Initiative << "\n";
    std::cout << "Proficiency: +" << proficiency << "\n";
    std::cout << "Feats: " << features.getFeats().size() << "\n";
    std::cout << "Racial Traits: " << features.getRacialTraits().size() << "\n";
    std::cout << "Items: " << inventory.size() << " carried\n";
    std::cout << "Currency: ";
    wallet.display();
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
    return (ability_score / 2) - 5;
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
int Character::getHitDiceNum() const { return hit_die_num; }
void Character::setHitDiceNum(int n) { hit_die_num = (n < 0 ? 0 : (n > level ? level : n)); }

void Character::spendHitDice(int count)
{
    if (count < 1 || count > hit_die_num) return;
    hit_die_num -= count;
}

void Character::recoverHitDice()
{
    // On a long rest, recover half the character's total hit dice (rounded up).
    int recovered = (level + 1) / 2;
    hit_die_num = (hit_die_num + recovered > level) ? level : hit_die_num + recovered;
}
void Character::setStrength(int str) { strength = str; }
void Character::setDexterity(int dex) {dexterity = dex;}
void Character::setConstitution(int con) {constitution = con;}
void Character::setIntelligence(int intl) {intelligence = intl;}
void Character::setWisdom(int wis) {wisdom = wis;}
void Character::setCharisma(int cha) {charisma = cha;}
void Character::setInitiative(int init) {Initiative = init;}
void Character::setProficiency(int prof) {proficiency = prof;}



// Inventory
void Character::addItem(std::unique_ptr<Item> item) {
    inventory.addItem(std::move(item));
}

Inventory& Character::getInventory() { return inventory; }

void Character::removeItem(int index) {
    inventory.removeItem(index);
}

void Character::showInventory() const {
    inventory.display();
}

void Character::clearInventory() {
    while (inventory.size() > 0) {
        inventory.removeItem(1);
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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

//-----------------------------------------------------//
// Wallet
Wallet& Character::getWallet() { return wallet; }

void Character::showCurrency() const {
    std::cout << "\n=== Currency ===\n";
    wallet.display();
}

CharacterFeatures& Character::getFeatures()
{
    return features;
}

const CharacterFeatures& Character::getFeatures() const
{
    return features;
}

void Character::showFeatures() const
{
    // Present all tracked feature-style character data together in one place.
    std::cout << "\n=== Feats ===\n";
    features.displayFeats();

    std::cout << "\n=== Racial Traits ===\n";
    features.displayRacialTraits();

    std::cout << "\n=== Skills ===\n";
    features.displaySkills(strength, dexterity, constitution,
                           intelligence, wisdom, charisma,
                           proficiency);
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
