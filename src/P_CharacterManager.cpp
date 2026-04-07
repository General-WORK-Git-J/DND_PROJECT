#include "H_CharacterManager.h"
#include "H_Weapon.h"
#include "H_Armor.h"
#include "H_Gear.h"
#include <iostream>
#include <fstream>

void CharacterManager::createCharacter() {
    std::string name, race, characterClass, background, alignment;
    int lvl, age, weight;
    int c_hp, m_hp, t_hp;
    std::string h_dice;
    int str, dex, con, intl, wis, cha, init, prof;

    int new_AS[6];

    name = getValidStringInput("name");
    race = getValidStringInput("race");
    characterClass = getValidStringInput("class");
    background = getValidStringInput("background");
    alignment = getValidStringInput("alignment");

    std::cout << "Enter level: ";
    std::cin >> lvl;

    std::cout << "Enter age: ";
    std::cin >> age;

    std::cout << "Enter weight: ";
    std::cin >> weight;

    std::cout << "Enter Temporary health (if applicable, otherwise enter 0): ";
    std::cin >> t_hp;

    std::cout << "Enter Max Health: ";
    std::cin >> m_hp;
    c_hp = m_hp;

    std::cout << "Enter hit dice: ";
    std::cin >> h_dice;


    

    for (int i = 0; i < 6; i++)
    {
        int new_score;
        std::cout << "Enter " << Ability_scores[i];
        std::cin >> new_score;
        if (new_score >= 1 && new_score <= 20)
        {
            new_AS[i] = new_score;
        }
        else
        {
            std::cout << "Ability score must be between 1 and 20, please re-enter! " << std::endl;
            Invalidinput();
            i--;
        }
    }

    str = new_AS[0];
    dex = new_AS[1];
    con = new_AS[2];
    intl = new_AS[3];
    wis = new_AS[4];
    cha = new_AS[5];

    bool initiative_set = false;
    bool proficiency_set = false;

    while (initiative_set == false)
    {
    std::cout << "Enter initiative: " ;
    std::cin >> init;
        if (std::cin){ initiative_set = true;}

        else 
        {
            Invalidinput();
            std::cout << "Invalid initiative value, please re-enter! " << std::endl;
            
        }
    }

    while ( proficiency_set == false)
    {
        
    std::cout << "Enter proficiency: ";
    std::cin >> prof;
    if (prof >= 2)
    {proficiency_set = true;}

    else
    {
        Invalidinput();
        std::cout << "Proficiency must be minimum +2, please enter valid value! " << std::endl;
        
    }
    }



    characters.emplace_back(name, race, characterClass, background, alignment, lvl, age, weight, c_hp, m_hp, t_hp, h_dice, str, dex, con, intl, wis, cha, init, prof);

    std::cout << "Character created!\n";
}

void CharacterManager::viewCharacters() const {
    if (characters.empty()) {
        std::cout << "No characters available.\n";
        return;
    }

    for (size_t i = 0; i < characters.size(); i++) {
        std::cout << "\nIndex: " << i + 1 << std::endl;
        characters[i].display();
    }
}

void CharacterManager::editCharacter() {
    if (characters.empty()) {
        std::cout << "No characters to edit.\n";
        return;
    }

    int index;
    std::cout << "Enter character index: ";
    std::cin >> index;

    if (index - 1 < 0 || index - 1 >= characters.size()) {
        std::cout << "Invalid index.\n";
        return;
    }

    Character& c = characters[index - 1];

    int choice;
    do {
        std::cout << "\n1.Character details 2.Character health 3.Inventory 4.Ability scores 5.Spells 0.Back\nChoice: ";
        std::cin >> choice;

        if (choice == 1) 
        {
            int char_edit_choice;
            std::cout << "What would you like to change? " << std::endl;
            for (int i = 0; i < 8; i++)
            {
                std::cout << i + 1 << "." << EditCharDetailsArray[i] << std::endl;
            }
            std::cout << "Choice: ";
            std::cin >> char_edit_choice;
            switch (char_edit_choice)
            {

            case 1: //Name
                {
                    std::string new_name = getValidStringInput("Name");
                    c.setName(new_name);
                    break;
                }

            case 2: //Race
                {
                    std::string new_race = getValidStringInput("Race");
                    c.setRace(new_race);
                    break;
                }
                  
            case 3: //Class
                {
                    std::string new_class = getValidStringInput("Class");
                    c.setClass(new_class);
                    break;
                }
            
            case 4: //Background
                {
                    std::string new_background = getValidStringInput("Background");
                    c.setBackground(new_background);
                    break;
                    
                }
            case 5: //Alignment
                {
                    std::string new_alignment = getValidStringInput("Alignment");
                    c.setAlignment(new_alignment);
                    std::cout << "Alignment set" << std::endl;
                    break;
                }
            case 6: //Age
                {
                    int new_age = getValidIntegerInput("Age");
                    c.setAge(new_age);
                    std::cout << "New age set" << std::endl;
                    break;
                }

                case 7: //Weight
                {
                    int new_weight = getValidIntegerInput("Weight");
                    c.setWeight(new_weight);
                    std::cout << "New weight set" << std::endl;
                    break;
                }

                case 8: //Level
                {
                    bool level_set = false;
                    while (level_set == false)
                    {
                        int new_level = getValidIntegerInput("Level");
                        if (new_level >= 1 && new_level <=20)
                        {
                            c.setLevel(new_level);
                            level_set = true;
                        }
                        else 
                        {
                            Invalidinput();
                            std::cout << "Level must be between 1 and 20" << std::endl;
                        }
                    }
                    break;
                }
                
                

        
            }

            
            
        }
        else if (choice == 2)
        {
            int health_edit_choice;
            std::cout << "What would you like to change? " << std::endl;
            for (int i = 0; i < 4; i++)
            {
                std::cout << i + 1 << "." << EditHpArray[i] << std::endl;
            }
            std::cout << "Choice: ";
            std::cin >> health_edit_choice;

            switch(health_edit_choice)
            {
                case 1: //Max Health
                {
                    int new_max_health = getValidIntegerInput("Max health");
                    int max_hp_diff = c.getMaxHP() - new_max_health; 
              
                    if (new_max_health < c.getMaxHP()) // Check to se if max health is being reduced 
                    {
                        c.setMaxHP(new_max_health);

                        // Do Calc to adjust current health accordingly
                        int adjust_current_hp = c.getCurrentHP() - max_hp_diff;
                        c.setCurrentHP(adjust_current_hp);
                    }
                    else 
                    {
                        c.setMaxHP(new_max_health);
                    }
                    std::cout << "New max health set" << std::endl;

                    break;
                }
                case 2: //Current Health
                {
                 
                    bool current_health_set = false;
                    while (current_health_set == false)
                    {
                        int new_current_health = getValidIntegerInput("Current health");
                        if (new_current_health <= c.getMaxHP())
                        {
                            c.setCurrentHP(new_current_health);
                            current_health_set = true;
                        }
                        else 
                        {
                            Invalidinput();
                            std::cout << "Current health cannot exceed max health (Max health: " << c.getMaxHP() << ")" << std::endl;
                        }
                    }
                    break;
                }
                case 3: //Temporary Health
                {
                    int new_temp_health = getValidIntegerInput("Temporary Heath");
                    c.setTempHP(new_temp_health);
                    std::cout << "New temp health set" << std::endl;
                    break;
                }
                case 4: //Hit Dice
                {
                    std::string new_hit_dice = getValidHitDiceInput();
                    c.setHitDice(new_hit_dice);
                    std::cout << "New hit dice set" << std::endl;
                    break;
                }
            }

            
        }

        else if (choice == 3) 
        {
            manageInventory(c);
        }
        else if (choice == 4) 
        {
            std::cout << "What stat would you like to change? "  << std::endl;
            for (int i = 0; i < 6; i++)
            {
                std::cout << i + 1 << ". " << Ability_scores[i] << std::endl;
            }
            int val;
            int abil;
            std::cin >> abil;
            std::cout << "New " << Ability_scores[abil - 1]<< std::endl;
            std::cin >> val;
            c.setStats(val, abil);
        }
        else if (choice == 5){
        int spellChoice;

            do {
                std::cout << "\n=== Spells ===\n";
                std::cout << "1. View Spells\n";
                std::cout << "2. Create New Spell\n";
                std::cout << "3. Add Existing Spell to Character\n";
                std::cout << "0. Back\n";
                std::cin >> spellChoice;

                if (spellChoice == 1)
                {
                    c.showSpells();
                }
                else if (spellChoice == 2)
                {
                    std::string name, type, effect, time, range, comp, duration, save, desc;
                    int level;

                    std::cout << "Spell name: "; std::cin >> name; //Name of spell
                    std::cout << "Type: "; std::cin >> type; //Abjuration, Conjuration, Divination, Enchantment, Evocation, Illusion, Necromancy, Transmutation
                    std::cout << "Effect: "; std::cin >> effect; //Damage, Healing, Utility, Control, Summoning, Buff, Debuff
                    std::cout << "Level: "; std::cin >> level; //Spell level (0 for cantrips)
                    std::cout << "Cast time: "; std::cin >> time; //Action, Bonus Action, Reaction, etc.
                    std::cout << "Range: "; std::cin >> range; //Touch, Self, 30 ft, 60 ft, etc.
                    std::cout << "Components: "; std::cin >> comp; //V, S, M (with optional material description)
                    std::cout << "Duration: "; std::cin >> duration; //Instantaneous, Concentration (up to 1 minute), etc.
                    std::cout << "Saving throw: "; std::cin >> save; //None, Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma
                    std::cout << "Description: "; std::cin >> desc; //Detailed spell description

                    Spell s(name, type, effect, level, time, range, comp, duration, save, desc);
                    // Save to Spellbook
                    Spellbook global;
                    global.loadSpellbook("data/SpellBook.txt");

                    global.addSpell(s);
                    global.saveSpellbook("data/SpellBook.txt");

                    std::cout << "Spell added to global spellbook!\n";
                }
                else if (spellChoice == 3)
                {
                    Spellbook global;
                    global.loadSpellbook("data/SpellBook.txt");

                    std::cout << "\n=== Global Spell List ===\n";
                    global.displayAllSpells();

                    std::string spellName;
                    std::cout << "Enter spell name to add: ";
                    std::cin >> spellName;

                    // Find spell
                    auto spells = global.getSpellsByLevel(0);

                    bool found = false;

                    for (const auto& s : spells)
                    {
                        if (s.getSpellName() == spellName)
                        {
                            c.getSpellbook().addSpell(s);
                            std::cout << "Spell added to character!\n";
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        std::cout << "Spell not found.\n";
                    }
                }
            } while (spellChoice != 0);
        }
        else 
        {
            std::cout << "Exiting edit menu " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    } while (choice != 0);
}

std::string CharacterManager::getValidStringInput(const std::string& value_to_get)
{
    std::string new_input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true)
    {
        std::cout << "Enter new " << value_to_get << std::endl;
        std::getline(std::cin, new_input);
        if (isValidString(new_input))
        {
            return new_input;
        }
        else
        {
            Invalidinput();
            std::cout << "Invalid " << value_to_get << std::endl;
        }
    }
}

bool CharacterManager::isValidString(const std::string &input)
{
    if (input.empty()) return false;
    bool hasLetter = false;
    for (char c : input)
    {
        if (!std::isalpha(c) && c != ' ' && c != '-' && c != '\'') return false;
        if (std::isalpha(c)) hasLetter = true;
    }
    return hasLetter;
}

bool CharacterManager::isValidHitDice(const std::string& input)
{
    // Must start with 'd' and be followed by at least one digit (e.g. d6, d12, d100)
    if (input.size() < 2 || input[0] != 'd') return false;
    for (size_t i = 1; i < input.size(); i++)
    {
        if (!std::isdigit(input[i])) return false;
    }
    return true;
}

std::string CharacterManager::getValidHitDiceInput()
{
    std::string new_input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true)
    {
        std::cout << "Enter new Hit Dice (e.g. d6, d8, d12): " << std::endl;
        std::getline(std::cin, new_input);
        if (isValidHitDice(new_input))
        {
            return new_input;
        }
        else
        {
            Invalidinput();
            std::cout << "Hit Dice must be in the format dN (e.g. d12)" << std::endl;
        }
    }
}

int CharacterManager::getValidIntegerInput(const std::string& value_to_get)
{
    int new_input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true)
    {
        std::cout << "Enter new " << value_to_get << std::endl;
        std::cin >> new_input;
        if (new_input > 0)
        {
            return new_input;
        }
        else
        {
            Invalidinput();
            std::cout << value_to_get << " must be a positive integer greater than 0" << std::endl;
        }
    }
}

void CharacterManager::Invalidinput()
{
    std::cout << "Not a valid Input!" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}

void CharacterManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file) {
        std::cout << "Error saving file\n";
        return;
    }

    file << characters.size() << std::endl;

    for (const auto& c : characters) {
        c.save(file);
    }

    std::cout << "Saved successfully.\n";
}

void CharacterManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "No save file found.\n";
        return;
    }

    characters.clear();

    int count;
    file >> count;
    file.ignore();

    for (int i = 0; i < count; i++) {
        std::string name, race, characterClass, background, alignment;
        int lvl, age, weight;
        int c_hp, m_hp, t_hp;
        std::string h_dice;
        int str, dex, con, intl, wis, cha, init, prof;

        std::getline(file, name);
        std::getline(file, race);
        std::getline(file, characterClass);
        std::getline(file, background);
        std::getline(file, alignment);
        
        file >> lvl;
        file >> age;
        file >> weight;
        file >> c_hp;
        file >> m_hp;
        file >> t_hp;
        file >> h_dice;

        file >> str >> dex >> con >> intl >> wis >> cha >> init >> prof;
        file.ignore();

        Character c(name, race, characterClass, background, alignment, lvl, age, weight, c_hp, m_hp, t_hp, h_dice, str, dex, con, intl, wis, cha, init, prof );
    

    // --- INVENTORY ---
        c.getInventory().load(file);

        // --- WALLET ---
        std::string walletMarker;
        std::getline(file, walletMarker);
        if (walletMarker == "WALLET")
        {
            c.getWallet().load(file);
        }

        // --- SPELLBOOK ---
        std::string marker;
        std::getline(file, marker);

        if (marker == "SPELLBOOK")
        {
            std::ofstream temp("data/temp_spell.txt");

            std::string line;
            while (std::getline(file, line) && line != "SPELLSLOTS")
            {
                temp << line << std::endl;
            }

            temp.close();
            c.getSpellbook().loadSpellbook("data/temp_spell.txt");
        }

        characters.push_back(std::move(c));
        
    }

    std::cout << "Loaded successfully.\n";
}

// inventory
void CharacterManager::manageInventory(Character& c) {
    int choice;

    do {
        std::cout << "\n=== Inventory ===\n";
        std::cout << "1. View\n";
        std::cout << "2. Add Item\n";
        std::cout << "3. Remove Item\n";
        std::cout << "4. Currency\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 1) {
            c.showInventory();
        }
        else if (choice == 2) {
            std::cout << "Item type:\n1. Weapon\n2. Armor\n3. Gear\nChoice: ";
            int typeChoice;
            std::cin >> typeChoice;

            std::string iName, iDesc, iRarity;
            float iWeight;
            int iQty, iValue;
            bool iAttune;

            iName = getValidStringInput("name");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Description: "; std::getline(std::cin, iDesc);
            iRarity = getValidStringInput("rarity (Common/Uncommon/Rare/Very Rare/Legendary)");
            std::cout << "Weight (lb): "; std::cin >> iWeight;
            std::cout << "Quantity: ";    std::cin >> iQty;
            std::cout << "Value (gp): "; std::cin >> iValue;
            std::cout << "Requires attunement? (1=Yes 0=No): "; std::cin >> iAttune;

            if (typeChoice == 1) {
                std::string dmgDice, dmgType, wCat, wType, props, range;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Damage dice (e.g. 1d6): "; std::getline(std::cin, dmgDice);
                std::cout << "Damage type (e.g. Slashing): "; std::getline(std::cin, dmgType);
                std::cout << "Category (Simple/Martial): "; std::getline(std::cin, wCat);
                std::cout << "Type (Melee/Ranged): "; std::getline(std::cin, wType);
                std::cout << "Properties (e.g. Finesse, Light): "; std::getline(std::cin, props);
                std::cout << "Range (e.g. 5 ft / 80/320 ft): "; std::getline(std::cin, range);
                c.addItem(std::make_unique<Weapon>(iName, iDesc, iWeight, iQty, iValue, iRarity, iAttune,
                                                   dmgDice, dmgType, wCat, wType, props, range));
            }
            else if (typeChoice == 2) {
                std::string aType;
                int baseAC, maxDex, strReq;
                bool stealthDis;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Armor type (Light/Medium/Heavy/Shield): "; std::getline(std::cin, aType);
                std::cout << "Base AC: "; std::cin >> baseAC;
                std::cout << "Max Dex bonus (-1 for no limit): "; std::cin >> maxDex;
                std::cout << "Strength requirement (0 for none): "; std::cin >> strReq;
                std::cout << "Stealth disadvantage? (1=Yes 0=No): "; std::cin >> stealthDis;
                c.addItem(std::make_unique<Armor>(iName, iDesc, iWeight, iQty, iValue, iRarity, iAttune,
                                                  aType, baseAC, maxDex, strReq, stealthDis));
            }
            else {
                c.addItem(std::make_unique<Gear>(iName, iDesc, iWeight, iQty, iValue, iRarity, iAttune));
            }
            std::cout << "Item added.\n";
        }
        else if (choice == 3) {
            int index;
            std::cout << "Index to remove: ";
            std::cin >> index;
            c.removeItem(index);
        }
        else if (choice == 4) {
            int currChoice;
            do {
                std::cout << "\n=== Currency ===\n";
                c.showCurrency();
                std::cout << "1. Add currency\n";
                std::cout << "2. Spend currency\n";
                std::cout << "0. Back\n";
                std::cout << "Choice: ";
                std::cin >> currChoice;

                if (currChoice == 1 || currChoice == 2) {
                    int pp, gp, ep, sp, cp;
                    std::cout << "Platinum: "; std::cin >> pp;
                    std::cout << "Gold: ";     std::cin >> gp;
                    std::cout << "Electrum: "; std::cin >> ep;
                    std::cout << "Silver: ";   std::cin >> sp;
                    std::cout << "Copper: ";   std::cin >> cp;

                    int sign = (currChoice == 2) ? -1 : 1;
                    c.getWallet().adjustPlatinum(sign * pp);
                    c.getWallet().adjustGold(sign * gp);
                    c.getWallet().adjustElectrum(sign * ep);
                    c.getWallet().adjustSilver(sign * sp);
                    c.getWallet().adjustCopper(sign * cp);

                    std::cout << (currChoice == 1 ? "Currency added.\n" : "Currency spent.\n");
                }
            } while (currChoice != 0);
        }

    } while (choice != 0);
}