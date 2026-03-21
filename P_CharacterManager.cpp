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

    cout << "\nEnter name: ";
    cin >> name;

    cout << "Enter race: ";
    cin >> race;

    cout << "Enter class: ";
    cin >> characterClass;

    cout << "Enter background: ";
    cin >> background;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter alignment: ";
    getline(cin, alignment);

    cout << "Enter level: ";
    cin >> lvl;

    cout << "Enter age: ";
    cin >> age;

    cout << "Enter weight: ";
    cin >> weight;

    cout << "Enter Temporary health (if applicable, otherwise enter 0): ";
    cin >> t_hp;

    cout << "Enter Max Health: ";
    cin >> m_hp;
    c_hp = m_hp;

    cout << "Enter hit dice: ";
    cin >> h_dice;


    

    for (int i = 0; i < 6; i++)
    {
        int new_score;
        cout << "Enter " << Ability_scores[i];
        cin >> new_score;
        if (new_score >= 1 && new_score <= 20)
        {
        new_AS[i] = new_score;
        }
        else
        {
           cout << "Ability score must be between 1 and 20, please re-enter! " << endl;
           cin.clear();
           cin.ignore(numeric_limits<streamsize>::max(), '\n') ;
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
    cout << "Enter initiative: " ;
    cin >> init;
        if (init > 0 || init < 0){ initiative_set = true;}

        else 
        {
            cout << "Invalid initiative value, please re-enter! " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while ( proficiency_set == false)
    {
        
    cout << "Enter proficiency: ";
    cin >> prof;
    if (prof >=3)
    {proficiency_set = true;}

    else 
    {
        cout << "Proficiency must be minimum +3, please enter valid value! " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    }



    characters.emplace_back(name, race, characterClass, background, alignment, lvl, age, weight, c_hp, m_hp, t_hp, h_dice, str, dex, con, intl, wis, cha, init, prof);

    cout << "Character created!\n";
}

void CharacterManager::viewCharacters() const {
    if (characters.empty()) {
        cout << "No characters available.\n";
        return;
    }

    for (size_t i = 0; i < characters.size(); i++) {
        cout << "\nIndex: " << i + 1 << endl;
        characters[i].display();
    }
}

void CharacterManager::editCharacter() {
    if (characters.empty()) {
        cout << "No characters to edit.\n";
        return;
    }

    int index;
    cout << "Enter character index: ";
    cin >> index;

    if (index - 1 < 0 || index - 1 >= characters.size()) {
        cout << "Invalid index.\n";
        return;
    }

    Character& c = characters[index - 1];

    int choice;
    do {
        cout << "\n1.Name 2.Inventory 3.Ability scores 0.Back\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            string val;
            cout << "New name: ";
            cin >> val;
            c.setName(val);
        }

        else if (choice == 2) {
            manageInventory(c);
        }
        else if (choice == 3) {
            cout << "What stat would you like to change? "  << endl;
            for (int i = 0; i < 6; i++)
            {
                cout << i + 1 << ". " << Ability_scores[i] << endl;
            }
            int val;
            int abil;
            cin >> abil;
            cout << "New " << Ability_scores[abil - 1]<< endl;
            cin >> val;
            c.setStats(val, abil);
        }
        else 
        {
            cout << "Exiting edit menu " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while (choice != 0);
}

void CharacterManager::saveToFile(const string& filename) const {
    ofstream file(filename);

    if (!file) {
        cout << "Error saving file\n";
        return;
    }

    file << characters.size() << endl;

    for (const auto& c : characters) {
        c.save(file);
    }

    cout << "Saved successfully.\n";
}

void CharacterManager::loadFromFile(const string& filename) {
    ifstream file(filename);

    if (!file) {
        cout << "No save file found.\n";
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

        getline(file, name);
        getline(file, race);
        getline(file, characterClass);
        getline(file, background);
        getline(file, alignment);
        
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

            getline(file, itemName);
            getline(file, itemType);
            file >> itemValue;
            file.ignore();

            c.addItem(Item(itemName, itemType, itemValue));
        }

        characters.push_back(c);
    }

    cout << "Loaded successfully.\n";
}

// inventory
void CharacterManager::manageInventory(Character& c) {
    int choice;

    do {
        cout << "\n=== Inventory ===\n";
        cout << "1. View\n";
        cout << "2. Add Item\n";
        cout << "3. Remove Item\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            c.showInventory();
        }
        else if (choice == 2) {
            string name, type;
            int value;

            cout << "Item name: ";
            cin >> name;
            cout << "Type: ";
            cin >> type;
            cout << "Value: ";
            cin >> value;

            c.addItem(Item(name, type, value));
        }
        else if (choice == 3) {
            int index;
            cout << "Index to remove: ";
            cin >> index;
            c.removeItem(index);
        }

    } while (choice != 0);
}