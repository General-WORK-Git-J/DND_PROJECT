#include "H_CharacterManager.h"
#include <iostream>
#include <fstream>

using namespace std;

void CharacterManager::createCharacter() {
    string name, race, characterClass;
    int str, dex, con, intl, wis, cha, init, prof;

    int new_AS[6];

    cout << "\nEnter name: ";
    cin >> name;

    cout << "Enter race: ";
    cin >> race;

    cout << "Enter class: ";
    cin >> characterClass;

    for (int i = 0; i < 6; i++)
    {
        int new_score;
        cout << "Enter " << Ability_scores[i];
        cin >> new_score;

        new_AS[i] = new_score;
    }

    str = new_AS[0];
    dex = new_AS[1];
    con = new_AS[2];
    intl = new_AS[3];
    wis = new_AS[4];
    cha = new_AS[5];

    cout << "Enter initiative: " ;
    cin >> init;
    cout << endl;

    cout << "Enter proficiency: ";
    cin >> prof;
    cout << endl;



    characters.emplace_back(name, race, characterClass, str, dex, con, intl, wis, cha, init, prof);

    cout << "Character created!\n";
}

void CharacterManager::viewCharacters() const {
    if (characters.empty()) {
        cout << "No characters available.\n";
        return;
    }

    for (size_t i = 0; i < characters.size(); i++) {
        cout << "\nIndex: " << i << endl;
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
        cout << "\n1.Name 2.Inventory 3.Ability scores 4.Spells 0.Back\nChoice: ";
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
        else if (choice == 4){
        int spellChoice;

            do {
                cout << "\n=== Spells ===\n";
                cout << "1. View Spells\n";
                cout << "2. Create New Spell\n";
                cout << "3. Add Existing Spell to Character\n";
                cout << "0. Back\n";
                cin >> spellChoice;

                if (spellChoice == 1)
                {
                    c.showSpells();
                }
                else if (spellChoice == 2)
                {
                    string name, type, effect, time, range, comp, duration, save, desc;
                    int level;

                    cout << "Spell name: "; cin >> name; //Name of spell
                    cout << "Type: "; cin >> type; //Abjuration, Conjuration, Divination, Enchantment, Evocation, Illusion, Necromancy, Transmutation
                    cout << "Effect: "; cin >> effect; //Damage, Healing, Utility, Control, Summoning, Buff, Debuff
                    cout << "Level: "; cin >> level; //Spell level (0 for cantrips)
                    cout << "Cast time: "; cin >> time; //Action, Bonus Action, Reaction, etc.
                    cout << "Range: "; cin >> range; //Touch, Self, 30 ft, 60 ft, etc.
                    cout << "Components: "; cin >> comp; //V, S, M (with optional material description)
                    cout << "Duration: "; cin >> duration; //Instantaneous, Concentration (up to 1 minute), etc.
                    cout << "Saving throw: "; cin >> save; //None, Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma
                    cout << "Description: "; cin >> desc; //Detailed spell description

                    Spell s(name, type, effect, level, time, range, comp, duration, save, desc);
                    // Save to Spellbook
                    Spellbook global;
                    global.loadSpellbook("SpellBook.txt");

                    global.addSpell(s);
                    global.saveSpellbook("SpellBook.txt");

                    cout << "Spell added to global spellbook!\n";
                }
                else if (spellChoice == 3)
                {
                    Spellbook global;
                    global.loadSpellbook("SpellBook.txt");

                    cout << "\n=== Global Spell List ===\n";
                    global.displayAllSpells();

                    string spellName;
                    cout << "Enter spell name to add: ";
                    cin >> spellName;

                    // Find spell
                    auto spells = global.getSpellsByLevel(0);

                    bool found = false;

                    for (const auto& s : spells)
                    {
                        if (s.getSpellName() == spellName)
                        {
                            c.getSpellbook().addSpell(s);
                            cout << "Spell added to character!\n";
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "Spell not found.\n";
                    }
                }
            } while (spellChoice != 0);
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
        string name, race, characterClass;
        int str, dex, con, intl, wis, cha, init, prof;

        getline(file, name);
        getline(file, race);
        getline(file, characterClass);

        file >> str >> dex >> con >> intl >> wis >> cha >> init >> prof;
        file.ignore();

        Character c(name, race, characterClass, str, dex, con, intl, wis, cha, init, prof );
    

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

        // --- SPELLBOOK ---
        string marker;
        getline(file, marker);

        if (marker == "SPELLBOOK")
        {
            ofstream temp("temp_spell.txt");

            string line;
            while (getline(file, line) && line != "SPELLSLOTS")
            {
                temp << line << endl;
            }

            temp.close();
            c.getSpellbook().loadSpellbook("temp_spell.txt");
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