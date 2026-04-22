#include "H_CharacterManager.h"
#include "H_Weapon.h"
#include "H_Armor.h"
#include "H_Gear.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>

// Anonymous namespace keeps these helpers private to this .cpp file.
namespace {
// Returns a lowercase copy so string comparisons can ignore letter casing.
std::string toLowerCopy(const std::string& value)
{
    std::string result = value;
    for (char& c : result)
    {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return result;
}

// Warlocks are the only class here whose spell slots reset on a short rest.
bool isWarlockClass(const Character& character)
{
    return toLowerCopy(character.getClass()) == "warlock";
}
}

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

    bool level_set = false;
    while (!level_set) {
        lvl = getValidIntegerInput("level (1-20)");
        if (lvl >= 1 && lvl <= 20) level_set = true;
        else { Invalidinput(); std::cout << "Level must be between 1 and 20\n"; }
    }

    age    = getValidIntegerInput("age");
    weight = getValidIntegerInput("weight");
    m_hp   = getValidIntegerInput("max health");
    c_hp   = m_hp;

    std::cout << "Enter Temporary health (0 if none): ";
    while (!(std::cin >> t_hp) || t_hp < 0) {
        Invalidinput();
        std::cout << "Enter a non-negative integer: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    h_dice = getValidHitDiceInput();


    

    for (int i = 0; i < 6; i++)
    {
        int new_score;
        std::cout << "Enter " << Ability_scores[i];
        if (std::cin >> new_score && new_score >= 1 && new_score <= 20)
        {
            new_AS[i] = new_score;
        }
        else
        {
            Invalidinput();
            std::cout << "Ability score must be between 1 and 20, please re-enter!\n";
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

    std::cout << "\n=== Characters ===\n";
    for (size_t i = 0; i < characters.size(); i++)
        std::cout << i + 1 << ". " << characters[i].getName() << "\n";
    std::cout << "0. Back\nChoice: ";

    int choice;
    std::cin >> choice;
    if (choice < 1 || choice > static_cast<int>(characters.size())) return;
    characters[choice - 1].display();
}

void CharacterManager::editCharacter() {
    if (characters.empty()) {
        std::cout << "No characters to edit.\n";
        return;
    }

    int index;
    std::cout << "Enter character index: ";
    std::cin >> index;

    if (index < 1 || index > static_cast<int>(characters.size())) {
        std::cout << "Invalid index.\n";
        return;
    }

    Character& c = characters[index - 1];

    int choice;
    do {
        std::cout << "\n1.Character details \n2.Character health \n3.Inventory \n4.Ability scores \n5.Spells \n6.Features and skills \n0.Back \nChoice: ";
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
                std::cout << "1. View Global Spells\n";
                std::cout << "2. Create New Spell\n";
                std::cout << "3. Add Existing Spell to Character\n";
                std::cout << "4. View Character Spellbook\n";
                std::cout << "5. Cast Spell\n";
                std::cout << "6. Edit Spell Slots\n";
                std::cout << "7. Long Rest\n";
                std::cout << "8. Short Rest\n";
                std::cout << "0. Back\n";
                std::cin >> spellChoice;

                if (spellChoice == 1)
                {
                    int viewChoice;

                    Spellbook global;
                    global.loadSpellbook("data/SpellBook.txt");

                    std::cout << "\n=== View Spells ===\n";
                    std::cout << "1. View All\n";
                    std::cout << "2. Filter by Level\n";
                    std::cout << "0. Back\n";
                    std::cin >> viewChoice;

                    if (viewChoice == 1)
                    {
                        global.displayAllSpells();
                    }
                    else if (viewChoice == 2)
                    {
                        int level;
                        std::cout << "Enter spell level: ";
                        std::cin >> level;

                        auto spells = global.getSpellsByLevel(level);

                        if (spells.empty())
                        {
                            std::cout << "No spells found at that level.\n";
                        }
                        else
                        {
                            for (size_t i = 0; i < spells.size(); i++)
                            {
                                std::cout << i + 1 << ". "
                                        << spells[i].getSpellName()
                                        << "\n";
                            }
                        }
                    }
                }
                else if (spellChoice == 2)
                {
                    std::string name, type, effect, time, range, comp, duration, save, desc;
                    int level;

                    std::cin.ignore(); // Clears leftover newline

                    std::cout << "Spell name: "; std::getline(std::cin, name); //Name of spell
                    std::cout << "Type: "; std::getline(std::cin, type); // Abjuration, Conjuration, Divination, Enchantment, Evocation, Illusion, Necromancy, Transmutation
                    std::cout << "Effect: "; std::getline(std::cin, effect); // Damage, Healing, Utility, Control, Summoning, Buff, Debuff

                    std::cout << "Level: "; std::cin >> level; // Spell level (0 for cantrips)
                    std::cin.ignore(); // clear newline after int input

                    std::cout << "Cast time: "; std::getline(std::cin, time); // Action, Bonus Action, Reaction, etc.
                    std::cout << "Range: "; std::getline(std::cin, range); // Touch, Self, 30 ft, 60 ft, etc.
                    std::cout << "Components: "; std::getline(std::cin, comp); // V, S, M (with optional material description)
                    std::cout << "Duration: "; std::getline(std::cin, duration); // Instantaneous, Concentration (up to 1 minute), etc.
                    std::cout << "Saving throw: "; std::getline(std::cin, save); // None, Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma
                    std::cout << "Description: "; std::getline(std::cin, desc); // Detailed spell description

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

                    int level;
                    std::cout << "Enter spell level to filter (0-9): ";
                    std::cin >> level;

                    if (std::cin.fail())
                    {
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        std::cout << "Invalid input.\n";
                        continue;
                    }

                    auto spells = global.getSpellsByLevel(level);

                    if (spells.empty())
                    {
                        std::cout << "No spells of that level.\n";
                        continue;
                    }

                    // Display Spells
                    std::cout << "\n=== Filtered Spells ===\n";
                    for (size_t i = 0; i < spells.size(); i++)
                    {
                        std::cout << i + 1 << ". "
                                << spells[i].getSpellName()
                                << " (Level " << spells[i].getSpellLevel() << ")\n";
                    }

                    int spellNum;
                    std::cout << "Select spell number: ";
                    std::cin >> spellNum;

                    if (std::cin.fail())
                    {
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        std::cout << "Invalid input.\n";
                        continue;
                    }

                    if (spellNum > 0 && spellNum <= static_cast<int>(spells.size()))
                    {
                        c.getSpellbook().addSpell(spells[spellNum - 1]);
                        std::cout << "Spell added to character!\n";
                    }
                    else
                    {
                        std::cout << "Invalid selection.\n";
                    }
                }
                else if (spellChoice == 4)
                {
                    c.showSpells();
                }
                else if (spellChoice == 5)
                {
                    // Casting uses the character's own known spells, not the global spell list.
                    auto knownSpells = c.getSpellbook().getAllSpells();

                    if (knownSpells.empty())
                    {
                        std::cout << "Character has no spells in their spellbook.\n";
                        continue;
                    }

                    c.getSpellbook().displaySpellsWithIndex();
                    std::cout << "Select spell number: ";

                    int selectedSpell = 0;
                    std::cin >> selectedSpell;

                    if (std::cin.fail() || selectedSpell < 1 || selectedSpell > static_cast<int>(knownSpells.size()))
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid spell selection.\n";
                        continue;
                    }

                    const Spell& spellToCast = knownSpells[selectedSpell - 1];
                    const int spellLevel = spellToCast.getSpellLevel();

                    if (spellLevel == 0)
                    {
                        std::cout << spellToCast.getSpellName() << " is a cantrip and does not use a spell slot.\n";
                        continue;
                    }

                    // Allow upcasting, but never casting below the spell's base level.
                    std::cout << "Cast " << spellToCast.getSpellName()
                              << " using what slot level? (" << spellLevel << "-9): ";

                    int slotLevel = 0;
                    std::cin >> slotLevel;

                    if (std::cin.fail() || slotLevel < spellLevel || slotLevel > 9)
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid slot level.\n";
                        continue;
                    }

                    if (c.getSpellSlots().useSlot(slotLevel))
                    {
                        std::cout << spellToCast.getSpellName() << " cast using a level "
                                  << slotLevel << " slot.\n";
                        std::cout << "Remaining level " << slotLevel << " slots: "
                                  << c.getSpellSlots().getCurrentSlots(slotLevel) << "/"
                                  << c.getSpellSlots().getMaxSlots(slotLevel) << "\n";
                    }
                    else
                    {
                        std::cout << "No level " << slotLevel << " spell slots remaining.\n";
                    }
                }
                else if (spellChoice == 6)
                {
                    int slotEditChoice = -1;

                    do
                    {
                        std::cout << "\n=== Edit Spell Slots ===\n";
                        c.getSpellSlots().displaySlots();
                        std::cout << "1. Set max slots for a level\n";
                        std::cout << "2. Set current slots for a level\n";
                        std::cout << "0. Back\n";
                        std::cout << "Choice: ";
                        std::cin >> slotEditChoice;

                        if (slotEditChoice == 1 || slotEditChoice == 2)
                        {
                            int slotLevel = 0;
                            std::cout << "Spell level (1-9): ";
                            std::cin >> slotLevel;

                            if (std::cin.fail() || slotLevel < 1 || slotLevel > 9)
                            {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid spell level.\n";
                                continue;
                            }

                            if (slotEditChoice == 1)
                            {
                                int maxSlots = 0;
                                std::cout << "New max slots: ";
                                std::cin >> maxSlots;

                                if (std::cin.fail() || maxSlots < 0)
                                {
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    std::cout << "Invalid slot count.\n";
                                    continue;
                                }

                                c.getSpellSlots().setSlots(slotLevel, maxSlots);
                                // Explicitly keep zero-max levels at zero current slots.
                                if (maxSlots == 0)
                                {
                                    c.getSpellSlots().setCurrentSlots(slotLevel, 0);
                                }
                                std::cout << "Max slots updated for level " << slotLevel << ".\n";
                            }
                            else
                            {
                                int currentSlots = 0;
                                std::cout << "New current slots: ";
                                std::cin >> currentSlots;

                                if (std::cin.fail() || currentSlots < 0)
                                {
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    std::cout << "Invalid slot count.\n";
                                    continue;
                                }

                                c.getSpellSlots().setCurrentSlots(slotLevel, currentSlots);
                                std::cout << "Current slots updated for level " << slotLevel << ".\n";
                            }
                        }
                    } while (slotEditChoice != 0);
                }
                else if (spellChoice == 7)
                {
                    c.getSpellSlots().resetSlots();
                    c.setCurrentHP(c.getMaxHP());
                    c.recoverHitDice();
                    std::cout << "Long rest complete. HP, spell slots, and hit dice restored.\n";
                    std::cout << "Hit dice: " << c.getHitDiceNum() << "/" << c.getLevel() << c.getHitDice() << "\n";
                }
                else if (spellChoice == 8)
                {
                    if (isWarlockClass(c))
                    {
                        c.getSpellSlots().resetSlots();
                        std::cout << "Short rest complete. Warlock spell slots restored to full.\n";
                    }
                    else
                    {
                        std::cout << "Short rest complete. Spell slots unchanged for "
                                  << c.getClass() << ".\n";
                    }

                    // All classes can spend hit dice during a short rest.
                    std::cout << "Hit dice available: " << c.getHitDiceNum()
                              << "/" << c.getLevel() << c.getHitDice() << "\n";
                    if (c.getHitDiceNum() > 0 && c.getCurrentHP() < c.getMaxHP())
                    {
                        std::cout << "Spend hit dice to recover HP? (0 = No): ";
                        int toSpend = 0;
                        std::cin >> toSpend;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (toSpend > 0 && toSpend <= c.getHitDiceNum())
                        {
                            std::cout << "Enter total HP recovered (roll " << toSpend
                                      << c.getHitDice() << " + CON modifier per die): ";
                            int hpGained = 0;
                            std::cin >> hpGained;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            if (hpGained > 0)
                            {
                                int newHp = c.getCurrentHP() + hpGained;
                                c.setCurrentHP(newHp > c.getMaxHP() ? c.getMaxHP() : newHp);
                            }
                            c.spendHitDice(toSpend);
                            std::cout << "HP: " << c.getCurrentHP() << "/" << c.getMaxHP()
                                      << "  Hit dice remaining: " << c.getHitDiceNum() << "\n";
                        }
                    }
                }
            } while (spellChoice != 0);
        }
        else if (choice == 6)
        {
            manageFeatures(c);
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
    while (true)
    {
        std::cout << "Enter new " << value_to_get << ": ";
        if (std::cin >> new_input && new_input > 0)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return new_input;
        }
        Invalidinput();
        std::cout << value_to_get << " must be a positive integer greater than 0\n";
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
        int h_dice_num = 0;
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
        file >> h_dice >> h_dice_num;

        file >> str >> dex >> con >> intl >> wis >> cha >> init >> prof;
        file.ignore();

        Character c(name, race, characterClass, background, alignment, lvl, age, weight, c_hp, m_hp, t_hp, h_dice, str, dex, con, intl, wis, cha, init, prof);
        if (h_dice_num > 0) c.setHitDiceNum(h_dice_num);

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

        std::string spellSlotMarker;
        std::streampos featureMarkerPos = file.tellg();
        std::getline(file, spellSlotMarker);
        if (spellSlotMarker == "SPELLSLOTS")
        {
            std::streampos spellSlotDataPos = file.tellg();
            std::string slotCountLine;

            if (std::getline(file, slotCountLine))
            {
                std::istringstream countParser(slotCountLine);
                int slotCount = 0;

                if (countParser >> slotCount)
                {
                    // Newer saves include a slot-count header and full slot data.
                    file.seekg(spellSlotDataPos);
                    c.getSpellSlots().load(file);
                }
                else
                {
                    // Older saves only had the marker, so leave slots empty and keep parsing.
                    file.clear();
                    file.seekg(spellSlotDataPos);
                }
            }
            else
            {
                file.clear();
            }
        }
        else
        {
            file.clear();
            file.seekg(featureMarkerPos);
        }

        std::streampos nextCharacterPos = file.tellg();
        std::string featureMarker;
        std::getline(file, featureMarker);
        if (featureMarker == "FEATURES")
        {
            c.getFeatures().load(file);
        }
        else
        {
            file.clear();
            file.seekg(nextCharacterPos);
        }

        std::streampos equippedPos = file.tellg();
        std::string equippedMarker;
        std::getline(file, equippedMarker);
        if (equippedMarker == "EQUIPPED")
        {
            int armorIdx = -1, shieldIdx = -1;
            file >> armorIdx >> shieldIdx;
            file.ignore();
            c.setEquippedArmorIndex(armorIdx);
            c.setEquippedShieldIndex(shieldIdx);
        }
        else
        {
            file.clear();
            file.seekg(equippedPos);
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
        std::cout << "5. Equip armor / shield\n";
        std::cout << "6. Unequip armor / shield\n";
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::string iName, iDesc, iRarity;
            float iWeight;
            int iQty, iValue;
            bool iAttune;

            iName = getValidStringInput("name");
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
        else if (choice == 5) {
            if (c.getInventory().size() == 0) {
                std::cout << "Inventory is empty.\n";
            } else {
                c.showInventory();
                std::cout << "Enter item number to equip (0 to cancel): ";
                int idx;
                std::cin >> idx;
                if (idx > 0 && idx <= c.getInventory().size()) {
                    c.equipArmor(idx);
                    c.equipShield(idx);
                    std::cout << "Equipped. AC is now " << c.getAC() << ".\n";
                }
            }
        }
        else if (choice == 6) {
            std::cout << "1. Unequip armor\n2. Unequip shield\nChoice: ";
            int uChoice;
            std::cin >> uChoice;
            if (uChoice == 1) { c.unequipArmor();  std::cout << "Armor unequipped.\n"; }
            if (uChoice == 2) { c.unequipShield(); std::cout << "Shield unequipped.\n"; }
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

void CharacterManager::manageFeatures(Character& c)
{
    int choice = -1;

    do
    {
        // This submenu acts as a lightweight tracker rather than a rules engine.
        std::cout << "\n=== Features And Skills ===\n";
        std::cout << "1. View all\n";
        std::cout << "2. Add feat\n";
        std::cout << "3. Remove feat\n";
        std::cout << "4. Add racial trait\n";
        std::cout << "5. Remove racial trait\n";
        std::cout << "6. View skills\n";
        std::cout << "7. Edit skill proficiency\n";
        std::cout << "8. Edit skill proficiency\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1)
        {
            c.showFeatures();
        }
        else if (choice == 2)
        {
            std::string feat;
            std::cout << "Feat name: ";
            std::getline(std::cin, feat);
            if (!feat.empty())
            {
                c.getFeatures().addFeat(feat);
                std::cout << "Feat added.\n";
            }
        }
        else if (choice == 3)
        {
            std::cout << "\n=== Feats ===\n";
            c.getFeatures().displayFeats();
            std::cout << "Index to remove: ";
            int index = 0;
            std::cin >> index;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (c.getFeatures().removeFeat(index))
            {
                std::cout << "Feat removed.\n";
            }
            else
            {
                std::cout << "Invalid index.\n";
            }
        }
        else if (choice == 4)
        {
            std::string trait;
            std::cout << "Racial trait name: ";
            std::getline(std::cin, trait);
            if (!trait.empty())
            {
                c.getFeatures().addRacialTrait(trait);
                std::cout << "Racial trait added.\n";
            }
        }
        else if (choice == 5)
        {
            std::cout << "\n=== Racial Traits ===\n";
            c.getFeatures().displayRacialTraits();
            std::cout << "Index to remove: ";
            int index = 0;
            std::cin >> index;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (c.getFeatures().removeRacialTrait(index))
            {
                std::cout << "Racial trait removed.\n";
            }
            else
            {
                std::cout << "Invalid index.\n";
            }
        }
        else if (choice == 6)
        {
            std::cout << "\n=== Skills ===\n";
            c.getFeatures().displaySkills(c.getStrength(), c.getDexterity(), c.getConstitution(),
                                          c.getIntelligence(), c.getWisdom(), c.getCharisma(),
                                          c.getProficiency());
        }
        else if (choice == 7)
        {
            const auto& skills = c.getFeatures().getSkills();
            // Skills are selected by index here, but stored internally by name.
            c.getFeatures().displaySkills(c.getStrength(), c.getDexterity(), c.getConstitution(),
                                          c.getIntelligence(), c.getWisdom(), c.getCharisma(),
                                          c.getProficiency());
            std::cout << "Skill number: ";

            int skillIndex = 0;
            std::cin >> skillIndex;
            if (std::cin.fail() || skillIndex < 1 || skillIndex > static_cast<int>(skills.size()))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid skill selection.\n";
                continue;
            }

            std::cout << "Rank (0=None, 1=Proficient, 2=Expertise): ";
            int rankValue = 0;
            std::cin >> rankValue;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (std::cin.fail() || rankValue < 0 || rankValue > 2)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid rank.\n";
                continue;
            }

            c.getFeatures().setSkillRank(skills[skillIndex - 1].name,
                                         static_cast<SkillRank>(rankValue));
            std::cout << "Skill updated.\n";
        }

        else if (choice == 8)
        {
            std::cout << "\n=== Saving Throws ===\n";
            c.getFeatures().displaySaves(c.getStrength(), c.getDexterity(), c.getConstitution(),
                                         c.getIntelligence(), c.getWisdom(), c.getCharisma(),
                                         c.getProficiency());
            std::cout << "Enter ability to toggle (STR/DEX/CON/INT/WIS/CHA) or 0 to cancel: ";
            std::string ability;
            std::getline(std::cin, ability);
            if (ability != "0" && !ability.empty())
            {
                bool current = c.getFeatures().getSaveProficiency(ability);
                if (c.getFeatures().setSaveProficiency(ability, !current))
                    std::cout << ability << " saving throw " << (!current ? "proficient" : "not proficient") << ".\n";
                else
                    std::cout << "Invalid ability. Use STR, DEX, CON, INT, WIS, or CHA.\n";
            }

        }
    } while (choice != 0);
}
