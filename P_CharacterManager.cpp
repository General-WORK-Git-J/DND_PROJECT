#include "H_CharacterManager.h"
#include <iostream>
#include <fstream>

using namespace std;

void CharacterManager::createCharacter() {
    string name, race, characterClass, background, alignment;
    int lvl, age, weight;
    int c_hp, m_hp, t_hp;
    string h_dice;
    int str, dex, con, intl, wis, cha, init, prof;

    int new_AS[6];

    std::cout << "\nEnter name: ";
    std::cin >> name;

    std::cout << "Enter race: ";
    std::cin >> race;

    std::cout << "Enter class: ";
    std::cin >> characterClass;

    std::cout << "Enter background: ";
    std::cin >> background;

    std::cin.clear();
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    std::cout << "Enter alignment: ";
    std::getline(cin, alignment);

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
            Invalidinput();
            std::cout << "Ability score must be between 1 and 20, please re-enter! " << endl;
           
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
        if (init > 0 || init < 0){ initiative_set = true;}

        else 
        {
            Invalidinput();
            std::cout << "Invalid initiative value, please re-enter! " << endl;
            
        }
    }

    while ( proficiency_set == false)
    {
        
    std::cout << "Enter proficiency: ";
    std::cin >> prof;
    if (prof >=3)
    {proficiency_set = true;}

    else 
    {
        Invalidinput();
        std::cout << "Proficiency must be minimum +3, please enter valid value! " << endl;
        
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
        std::cout << "\nIndex: " << i + 1 << endl;
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
        std::cout << "\n1.Character details 2.Character health 3.Inventory 4.Ability scores 0.Back\nChoice: ";
        std::cin >> choice;

        if (choice == 1) 
        {
            int char_edit_choice;
            std::cout << "What would you like to change? " << endl;
            for (int i = 0; i < size(EditCharDetailsArray); i++)
            {
                std::cout << i + 1 << "." << EditCharDetailsArray[i] << endl;
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
            std::cout << "What would you like to change? " << endl;
            for (int i = 0; i < size(EditHpArray); i++)
            {
                std::cout << i + 1 << "." << EditHpArray[i] << endl;
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
                    cout << "New temp health set" << endl;
                    break;
                }
                case 4: //Hit Dice
                {
                    std::string new_hit_dice = getValidHitDiceInput();
                    c.setHitDice(new_hit_dice);
                    std::cout << "New hit dice set" << endl;
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
            std::cout << "What stat would you like to change? "  << endl;
            for (int i = 0; i < 6; i++)
            {
                std::cout << i + 1 << ". " << Ability_scores[i] << endl;
            }
            int val;
            int abil;
            std::cin >> abil;
            std::cout << "New " << Ability_scores[abil - 1]<< endl;
            std::cin >> val;
            c.setStats(val, abil);
        }
        else 
        {
            std::cout << "Exiting edit menu " << endl;
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

    // Returns false if any character is a digit
    for (char c : input) 
    {
        if (std::isdigit(c)) return false;
    }
    return true;
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
        std::cout << "Enter new " << value_to_get << endl;
        std::cin >> new_input;
        if (new_input > 0)
        {
            return new_input;
        }
        else
        {
            Invalidinput();
            std::cout << value_to_get << " must be a positive integer greater than 0" << endl;
        }
    }
}

void CharacterManager::Invalidinput()
{
    std::cout << "Not a valid Input!" << std::endl;
    std::cin.clear();
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

}

void CharacterManager::saveToFile(const string& filename) const {
    ofstream file(filename);

    if (!file) {
        std::cout << "Error saving file\n";
        return;
    }

    file << characters.size() << endl;

    for (const auto& c : characters) {
        c.save(file);
    }

    std::cout << "Saved successfully.\n";
}

void CharacterManager::loadFromFile(const string& filename) {
    ifstream file(filename);

    if (!file) {
        std::cout << "No save file found.\n";
        return;
    }

    characters.clear();

    int count;
    file >> count;
    file.ignore();

    for (int i = 0; i < count; i++) {
        string name, race, characterClass, background, alignment;
        int lvl, age, weight;
        int c_hp, m_hp, t_hp;
        string h_dice;
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
        int itemCount;
        file >> itemCount;
        file.ignore();

        for (int j = 0; j < itemCount; j++) {
            std::string itemName, itemType;
            int itemValue;

            std::getline(file, itemName);
            std::getline(file, itemType);
            file >> itemValue;
            file.ignore();

            c.addItem(Item(itemName, itemType, itemValue));
        }

        characters.push_back(c);
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
        std::cout << "0. Back\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 1) {
            c.showInventory();
        }
        else if (choice == 2) {
            string name, type;
            int value;

            std::cout << "Item name: ";
            std::cin >> name;
            std::cout << "Type: ";
            std::cin >> type;
            std::cout << "Value: ";
            std::cin >> value;

            c.addItem(Item(name, type, value));
        }
        else if (choice == 3) {
            int index;
            std::cout << "Index to remove: ";
            std::cin >> index;
            c.removeItem(index);
        }

    } while (choice != 0);
}