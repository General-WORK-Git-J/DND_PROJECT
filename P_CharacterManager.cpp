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
                    string new_name;
                    bool name_set = false;

                    while (name_set == false)
                    {
                        std::cout << "Enter new name: " << endl;
                        std::getline(std::cin,new_name);
                        if (isValidString(new_name))
                        {
                            std::cout << "New Name Set! " << endl;
                            c.setName(new_name);
                            name_set = true;
                        }
                        else 
                        {
                            Invalidinput();
                        }
                    }
                    break;
                }

            case 2: //Race
                {
                    string new_race;
                    bool race_set = false;
                    while (race_set == false)
                    {
                        std::cout << "Enter new race: " << endl;
                        std::getline(std::cin,new_race);
                        if (isValidString(new_race))
                        {
                            std::cout << "New Race Set! " << endl;
                            c.setRace(new_race);
                            race_set = true;
                        }
                        else 
                        {
                            Invalidinput();
                        } 
                    }
                    break;
                }
                  
            case 3: //Class
                {
                    std::string new_class;
                    bool class_set = false;
                    while(class_set == false)
                    {
                        std::cout << "Enter new Class" << endl;
                        std::getline(std::cin,new_class);
                        if (isValidString(new_class))
                        {
                            c.setClass(new_class);
                            class_set = true;
                        }
                        else
                        {
                            Invalidinput();
                        }
                    }
                    break;
                }
            
            case 4: //Background
                {
                    std::string new_background;
                    bool background_set = false;
                    while (background_set == false)
                    {
                        std::cout << "Enter new Background" << endl;
                        std::getline(std::cin, new_background);
                        if (isValidString(new_background))
                        {
                            c.setBackground(new_background);
                            background_set = true;
                        }
                        else
                        {
                            Invalidinput();
                        }
                    }
                    break;

                    
                }
            case 5: //Alignment
                {
                    std::string new_alignment;
                    bool alignment_set = false;
                    while (alignment_set == false)
                    {
                        std::cout << "Enter new Alignment" << endl;
                        std::getline(std::cin,new_alignment);
                        if (isValidString(new_alignment))
                        {
                            c.setAlignment(new_alignment);
                            alignment_set = true;
                        }
                        else 
                        {
                            Invalidinput();
                        }
                    }
                    break;
                }
            case 6: //Age
                {
                    int new_age;
                    bool age_set = false;
                    while (age_set == false)
                    {
                        std::cout << "Enter new age" << endl;
                        std::cin >> new_age;
                        if (new_age >= 0)
                        {
                            c.setAge(new_age);
                            age_set = true;
                        }
                        else
                        {
                            Invalidinput();
                            cout << "Age must be greater than/equal to 0" << endl;
                        }
                    }
                    break;
                }

                case 7: //Weight
                {
                    int new_weight;
                    bool weight_set = false;
                    while (weight_set == false)
                    {
                        std::cout << "Enter new weight" << endl;
                        std::cin >> new_weight;
                        if (new_weight > 0)
                        {
                            c.setWeight(new_weight);
                            weight_set = true;
                        }
                        else 
                        {
                            Invalidinput();
                            cout << "Weight must be greater than 0" << endl;
                        }
                    }
                    break;

                }

                case 8: //Level
                {
                    int new_level;
                    bool level_set = false;
                    while (level_set == false)
                    {
                        std::cout << "Enter new Level" << endl;
                        std::cin >> new_level;
                        if (new_level >=1 && new_level <= 20)
                        {
                            c.setLevel(new_level);
                            level_set = true;
                        }
                        else 
                        {
                            Invalidinput();
                            std::cout << "Level must be between 1 and 20! " << endl; 
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
                    int new_max_health;
                    bool max_health_set = false;
                    while (max_health_set == false)
                    {
                        cout << "Enter new Max health" << endl;
                        cin >> new_max_health;
                        if ( new_max_health > 1)
                        {
                            c.setMaxHP(new_max_health);
                            cout << "Max health set" << endl;
                            max_health_set = true;
                        }
                        else 
                        {
                            Invalidinput();
                            cout << "Max health must be an integer greater than 1" << endl;
                        }

                    }
                }
                case 2: //Current Health
                {
                    int new_current_health;
                    bool current_health_set = false;
                    while (current_health_set == false)
                    {
                        cout << "Enter new current health " << endl;
                        cin >> new_current_health;
                        if (new_current_health > 1 && new_current_health < c.getMaxHP())
                        {
                            c.setCurrentHP(new_current_health);
                            cout << "Current health set" << endl;
                            current_health_set = true;
                        }
                        else if (new_current_health > c.getMaxHP())
                        {
                            Invalidinput();
                            cout << "Current health cannot exceed Max health" << endl;
                            
                        }
                        else 
                        {
                            Invalidinput();
                            std::cout << "Current health must be an integer greater than 1 and cannot exceed max health" << endl;
                        }
                        
                    }
                }
                case 3: //Temporary Health
                case 4: //Hit Dice
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

void CharacterManager::Invalidinput()
{
    std::cout << "Not a valid Input!" << endl;
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