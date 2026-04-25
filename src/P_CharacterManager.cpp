#include "H_CharacterManager.h"
#include "H_Weapon.h"
#include "H_Armor.h"
#include "H_Gear.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <limits>
#include <filesystem>

// Main file for managing character utilities

// Indexing in c++ is 0-based, so first element in a container is element 0.
// But for display purposes it is converted to 1-based, and then converted back to 0-based for actual element referencing.

// All numeric values (damage, health, stats etc.) in DND are whole integers, though in the event that division occurs, such as when an attack does half damage 
// or a potion does half healing and the resulting value isnt a whole number, the numeric value is rounded up or down to a whole number at the Dungeon masters 
//discretion. This simplifies the numeric based data management, and means we dont ever have to use floats or doubles (yay)


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

Spellbook loadGlobalSpellbook()
{
    Spellbook global;
    global.loadSpellbook("data/SpellBook.txt");
    return global;
}

void saveGlobalSpellbook(const Spellbook& spellbook)
{
    spellbook.saveSpellbook("data/SpellBook.txt");
}
}

void CharacterManager::createCharacter() {

    // Initialize variables
    std::string name, race, characterClass, background, alignment;
    int lvl, age, weight;
    int c_hp, m_hp, t_hp;
    std::string h_dice;
    int str, dex, con, intl, wis, cha, init, prof;

    int new_AS[6];

    // Get string based information
    name = getValidNameInput("name");
    race = getValidStringInput("race");
    characterClass = getValidStringInput("class");
    background = getValidStringInput("background");
    alignment = getValidStringInput("alignment");
    
    // Get level
    bool level_set = false;
    while (!level_set) {
        lvl = getValidIntegerInput("level (1-20)");
        if (lvl >= 1 && lvl <= 20) level_set = true;
        else { Invalidinput(); std::cout << "Level must be between 1 and 20\n"; }
    }

    // Get integer based information.
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


    
    // Get ability scores 
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

    // Assign new ability scores
    str = new_AS[0];
    dex = new_AS[1];
    con = new_AS[2];
    intl = new_AS[3];
    wis = new_AS[4];
    cha = new_AS[5];

    // Get prof and intitiative
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

    while (proficiency_set == false)
    {
        
    std::cout << "Enter proficiency: ";
    std::cin >> prof;
    if (prof >= 2) // Proficiency bonus is +2 at level one, cannot be lower
        {proficiency_set = true;}

    else
        {
        Invalidinput();
        std::cout << "Proficiency must be minimum +2, please enter valid value! " << std::endl;
        
        }
    }


    // Build character using constructor and place into vector
    characters.emplace_back(name, race, characterClass, background, alignment, lvl, age, weight, c_hp, m_hp, t_hp, h_dice, str, dex, con, intl, wis, cha, init, prof);

    std::cout << "Character created!\n";
}

bool CharacterManager::hasCharacters() const
{
    return !characters.empty();
}

void CharacterManager::viewCharacters() const {
    // Check for characters
    if (characters.empty()) {
        std::cout << "No characters available.\n";
        return;
    }

    // List Characters by name
    std::cout << "\n=== Characters ===\n";
    for (size_t i = 0; i < characters.size(); i++)
        std::cout << i + 1 << ". " << characters[i].getName() << "\n";
    std::cout << "0. Back\nChoice: ";

    int choice;
    std::cin >> choice;
    if (choice < 1 || choice > static_cast<int>(characters.size())) return;
    // Show all details of chosen character
    characters[choice - 1].display();  
}

void CharacterManager::manageGlobalSpells()
{
    int choice = -1;

    do
    {
        std::cout << "\n=== Global Spells ===\n";
        std::cout << "1. View Spells By Level\n";
        std::cout << "2. Add Spell\n";
        std::cout << "3. Edit Spell\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (std::cin.fail())
        {
            Invalidinput();
            continue;
        }

        if (choice == 1)
        {
            int level = 0;
            std::cout << "Enter spell level: ";
            std::cin >> level;

            if (std::cin.fail())
            {
                Invalidinput();
                continue;
            }

            Spellbook global = loadGlobalSpellbook();
            auto spells = global.getSpellsByLevel(level);

            if (spells.empty())
            {
                std::cout << "No spells found at that level.\n";
            }
            else
            {
                std::cout << "\n=== Spells At Level " << level << " ===\n";
                for (const auto& spell : spells)
                {
                    spell.DisplaySpellProperties();
                    std::cout << "------------------\n";
                }
            }
        }
        else if (choice == 2)
        {
            std::string name, type, effect, time, range, comp, duration, save, desc;
            int level = 0;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Spell name: ";
            std::getline(std::cin, name);
            std::cout << "Type: ";
            std::getline(std::cin, type);
            std::cout << "Effect: ";
            std::getline(std::cin, effect);
            std::cout << "Level: ";
            std::cin >> level;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Cast time: ";
            std::getline(std::cin, time);
            std::cout << "Range: ";
            std::getline(std::cin, range);
            std::cout << "Components: ";
            std::getline(std::cin, comp);
            std::cout << "Duration: ";
            std::getline(std::cin, duration);
            std::cout << "Saving throw: ";
            std::getline(std::cin, save);
            std::cout << "Description: ";
            std::getline(std::cin, desc);

            Spellbook global = loadGlobalSpellbook();
            global.addSpell(Spell(name, type, effect, level, time, range, comp, duration, save, desc));
            saveGlobalSpellbook(global);
            std::cout << "Spell added to global spellbook!\n";
        }
        else if (choice == 3)
        {
            Spellbook global = loadGlobalSpellbook();
            auto spells = global.getAllSpells();

            if (spells.empty())
            {
                std::cout << "No spells available to edit.\n";
                continue;
            }

            global.displaySpellsWithIndex();
            std::cout << "Select spell number: ";

            int spellNum = 0;
            std::cin >> spellNum;
            if (std::cin.fail() || spellNum < 1 || spellNum > static_cast<int>(spells.size()))
            {
                Invalidinput();
                std::cout << "Invalid spell selection.\n";
                continue;
            }

            Spell spellToEdit = spells[spellNum - 1];
            int editChoice = -1;

            do
            {
                std::cout << "\n=== Edit Spell: " << spellToEdit.getSpellName() << " ===\n";
                std::cout << "1. Name\n";
                std::cout << "2. Type\n";
                std::cout << "3. Effect\n";
                std::cout << "4. Level\n";
                std::cout << "5. Cast Time\n";
                std::cout << "6. Range\n";
                std::cout << "7. Components\n";
                std::cout << "8. Duration\n";
                std::cout << "9. Saving Throw\n";
                std::cout << "10. Description\n";
                std::cout << "11. View Spell Details\n";
                std::cout << "0. Save and Back\n";
                std::cout << "Choice: ";
                std::cin >> editChoice;

                if (std::cin.fail())
                {
                    Invalidinput();
                    continue;
                }

                switch (editChoice)
                {
                    case 1:
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        spellToEdit.setSpellName(getValidNameInput("spell name"));
                        break;
                    }
                    case 2:
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        spellToEdit.setSpellType(getValidStringInput("spell type"));
                        break;
                    }
                    case 3:
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        spellToEdit.setSpellEffect(getValidStringInput("spell effect"));
                        break;
                    }
                    case 4:
                    {
                        spellToEdit.setSpellLevel(getValidIntegerInput("spell level"));
                        break;
                    }
                    case 5:
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        spellToEdit.setSpellTime(getValidStringInput("cast time"));
                        break;
                    }
                    case 6:
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        spellToEdit.setSpellRange(getValidStringInput("range"));
                        break;
                    }
                    case 7:
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        spellToEdit.setSpellComponents(getValidStringInput("components"));
                        break;
                    }
                    case 8:
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        spellToEdit.setSpellDuration(getValidStringInput("duration"));
                        break;
                    }
                    case 9:
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        spellToEdit.setSpellSavingThrow(getValidStringInput("saving throw"));
                        break;
                    }
                    case 10:
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        spellToEdit.setSpellDescription(getValidStringInput("description"));
                        break;
                    }
                    case 11:
                    {
                        spellToEdit.DisplaySpellProperties();
                        break;
                    }
                    case 0:
                    {
                        if (global.updateSpell(static_cast<size_t>(spellNum - 1), spellToEdit))
                        {
                            saveGlobalSpellbook(global);
                            std::cout << "Spell updated.\n";
                        }
                        break;
                    }
                    default:
                    {
                        std::cout << "Invalid choice.\n";
                        break;
                    }
                }
            } while (editChoice != 0);
        }
        else if (choice != 0)
        {
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

void CharacterManager::editCharacter() {
    // Check for characters
    if (characters.empty()) {
        std::cout << "No characters to edit.\n";
        return;
    }

    int index;
    // Displays characters by name by using a for loop to iterate through the vector
    for (int i = 0; i < static_cast<int>(characters.size()); i++)
    {
        std::cout << i + 1 << ". " << characters[i].getName() << std::endl;
    }
    
    std::cout << "Enter character index: ";
    std::cin >> index;

    if (index < 1 || index > static_cast<int>(characters.size())) {
        std::cout << "Invalid index.\n";
        return;
    }

    // Assigns the character object chose to reference c to apply edits
    Character& c = characters[index - 1];

    int choice;

    // Display edit menu
    do {
        std::cout << "\n1.Character details \n2.Character health \n3.Inventory \n4.Ability scores \n5.Spells \n6.Features and skills \n0.Back \nChoice: ";
        std::cin >> choice;

        if (choice == 1) // Character details
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
                    std::string new_name = getValidNameInput("Name");
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
        else if (choice == 2) // Health
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

        else if (choice == 3) // Inventory
        {
            manageInventory(c);
        }
        else if (choice == 4) // Stats
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
        else if (choice == 5) // Spells and hsort/long rest
        {
        int spellChoice;

            do {
                std::cout << "\n=== Character Spells ===\n";
                std::cout << "1. View Global Spells\n";
                std::cout << "2. Add Existing Spell to Character\n";
                std::cout << "3. View Character Spellbook\n";
                std::cout << "4. Cast Spell\n";
                std::cout << "5. Edit Spell Slots\n";
                std::cout << "6. Long Rest\n";
                std::cout << "7. Short Rest\n";
                std::cout << "0. Back\n";
                std::cin >> spellChoice;

                if (spellChoice == 1)
                {
                    Spellbook global = loadGlobalSpellbook();
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
                else if (spellChoice == 2)
                {
                    Spellbook global = loadGlobalSpellbook();

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
                    std::cout << "Select spell number (Cantrips are Level 0): ";
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
                else if (spellChoice == 3)
                {
                    c.showSpells();
                }
                else if (spellChoice == 4)
                {
                    // Casting uses the character's own known spells, not the global spell list.
                    auto knownSpells = c.getSpellbook().getAllSpells();

                    if (knownSpells.empty())
                    {
                        std::cout << "Character has no spells in their spellbook.\n";
                        continue;
                    }

                    c.getSpellbook().displaySpellsWithIndex();
                    std::cout << "Select spell number (Cantrips are Level 0): ";

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
                else if (spellChoice == 5)
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
                else if (spellChoice == 6)
                {
                    c.getSpellSlots().resetSlots();
                    c.setCurrentHP(c.getMaxHP());
                    c.recoverHitDice();
                    std::cout << "Long rest complete. HP, spell slots, and hit dice restored.\n";
                    std::cout << "Hit dice: " << c.getHitDiceNum() << "/" << c.getLevel() << c.getHitDice() << "\n";
                }
                else if (spellChoice == 7)
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
        else if (choice == 6) // Feats and abilites
        {
            manageFeatures(c);
        }
        else // Exit edit menu
        {
            std::cout << "Exiting edit menu " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    } while (choice != 0);
}

// Utility methods for getting valid inputs and re-usable error-checking methods
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

std::string CharacterManager::getValidNameInput(const std::string& value_to_get)
{
    std::string new_input;
    while (true)
    {
        std::cout << "Enter new " << value_to_get << std::endl;
        std::getline(std::cin, new_input);
        if (isValidName(new_input))
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
        if (!std::isprint(static_cast<unsigned char>(c))) return false;
        if (std::isalpha(static_cast<unsigned char>(c))) hasLetter = true;
    }
    return hasLetter;
}

bool CharacterManager::isValidName(const std::string &input)
{
    if (input.empty()) return false;
    for (char c : input)
    {
        if (!std::isprint(static_cast<unsigned char>(c))) return false;
    }
    // Reject strings that are only whitespace
    for (char c : input)
    {
        if (!std::isspace(static_cast<unsigned char>(c))) return true;
    }
    return false;
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
// Save/Load functions

void CharacterManager::saveCharacter(const Character& c) const {
    namespace fs = std::filesystem;
    fs::path dir = fs::path("data") / "characters" / c.getName();
    fs::create_directories(dir);
    c.saveToDirectory(dir.string());
    std::cout << c.getName() << " saved.\n";
}

void CharacterManager::saveAll() const {
    if (characters.empty()) {
        std::cout << "No characters to save.\n";
        return;
    }
    for (const auto& c : characters)
        saveCharacter(c);
}

void CharacterManager::loadAll() {
    namespace fs = std::filesystem;
    fs::path base = fs::path("data") / "characters";

    if (!fs::exists(base) || !fs::is_directory(base)) {
        std::cout << "No saved characters found.\n";
        return;
    }

    characters.clear();
    int loaded = 0;
    for (const auto& entry : fs::directory_iterator(base)) {
        if (entry.is_directory() && fs::exists(entry.path() / "character.txt")) {
            characters.push_back(Character::loadFromDirectory(entry.path().string()));
            loaded++;
        }
    }

    if (loaded == 0)
        std::cout << "No saved characters found.\n";
    else
        std::cout << "Loaded " << loaded << " character(s).\n";
}

std::vector<std::string> CharacterManager::listCharacterNames() const {
    namespace fs = std::filesystem;
    std::vector<std::string> names;
    fs::path base = fs::path("data") / "characters";

    if (!fs::exists(base) || !fs::is_directory(base))
        return names;

    for (const auto& entry : fs::directory_iterator(base)) {
        if (entry.is_directory())
            names.push_back(entry.path().filename().string());
    }
    return names;
}

// Inventory
void CharacterManager::manageInventory(Character& c) {
    int choice;

    do {
        // Inventory menu
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
        else if (choice == 2) // Create new item
        {
            std::cout << "Item type:\n1. Weapon\n2. Armor\n3. Gear\nChoice: ";
            int typeChoice;
            std::cin >> typeChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::string iName, iDesc, iRarity;
            float iWeight;
            int iQty, iValue;
            bool iAttune;

            iName = getValidNameInput("name");
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
        else if (choice == 3) // Remove item by index 
        {
            int index;
            std::cout << "Index to remove: ";
            std::cin >> index;
            c.removeItem(index);
        }
        else if (choice == 5) // Equip armor or shield
        {
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
        else if (choice == 6) // Unequip Armor or shield 
        {
            std::cout << "1. Unequip armor\n2. Unequip shield\nChoice: ";
            int uChoice;
            std::cin >> uChoice;
            if (uChoice == 1) { c.unequipArmor();  std::cout << "Armor unequipped.\n"; }
            if (uChoice == 2) { c.unequipShield(); std::cout << "Shield unequipped.\n"; }
        }
        else if (choice == 4) // Manage currency
        {
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

// Methods for managing features
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
        std::cout << "8. Edit saving throw proficiency\n";
        std::cout << "9. Add language\n";
        std::cout << "10. Remove language\n";
        std::cout << "11. Toggle inspiration\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) // View feats
        {
            c.showFeatures();
        }
        else if (choice == 2) // Add feat
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
        else if (choice == 3) // Remove feat
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
        else if (choice == 4) // Add racial feat/trait
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
        else if (choice == 5) // Remove racial feat/trait
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
        else if (choice == 6) // View skills
        {
            std::cout << "\n=== Skills ===\n";
            c.getFeatures().displaySkills(c.getStrength(), c.getDexterity(), c.getConstitution(),
                                          c.getIntelligence(), c.getWisdom(), c.getCharisma(),
                                          c.getProficiency());
        }
        else if (choice == 7) // Edit skill proficiencies
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

        else if (choice == 8) // Edit saving throw proficiencys
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
        else if (choice == 9) // Add language
        {
            std::string lang;
            std::cout << "Language name: ";
            std::getline(std::cin, lang);
            if (!lang.empty())
            {
                c.getFeatures().addLanguage(lang);
                std::cout << "Language added.\n";
            }
        }
        else if (choice == 10) // Remove language
        {
            std::cout << "\n=== Languages ===\n";
            c.getFeatures().displayLanguages();
            std::cout << "Index to remove: ";
            int index = 0;
            std::cin >> index;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (c.getFeatures().removeLanguage(index))
                std::cout << "Language removed.\n";
            else
                std::cout << "Invalid index.\n";
        }
        else if (choice == 11) // Toggle inspiration
        {
            c.toggleInspiration();
            std::cout << "Inspiration: " << (c.getInspiration() ? "Yes" : "No") << "\n";
        }
    } while (choice != 0);
}
