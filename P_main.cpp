
#include <iostream>
#include <string>
#include <memory>

#include "H_stats.h"
#include "H_Character.h"
#include "H_equipment.h"
#include "H_equipment_tracker.h"
#include "H_spells.h"

using namespace std;


int main()
{
    map<string, unique_ptr<Character>> Characters;
    map<string, unique_ptr<equipment>> Equipment_item;

    while (true)
    {
        int choice;

        bool Character_exists;
        string current_char_id;
        

        cout << "1. Create Character\n";
        cout << "2. Create item\n";
        cout << "3. Exit\n";
        cin >> choice;

        if (choice == 1)
        {
            string char_id;
            cout << "Enter character name: ";
            cin >> char_id;

            Characters.emplace(char_id, std::make_unique<Character>());

            auto& character = Characters[char_id];

            character->setCharacterComponents();

            Player_stats stat_1;
            Equipment_tracker track_1;

            character->setStatObj(stat_1);
            character->setEquipmentTrackObj(track_1);

            Character_exists = true;

            character->getStatObj()->setAllScores();

            character->getDetails();
            character->getStatObj()->displayAbilityScores();

            current_char_id = char_id;





        }


        else if (choice == 2)
        {
            if (Character_exists == true)
            {
                cout << "item is able to be created!\n"; 
                
                

                
            }

            else
            {
                cout << "item cannot be created, no character exists!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

               
            }

        }

        else if (choice == 3)
        {
            break;
        }

        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    /*
    cout << "OUTPUT TEST START" << endl;

    // Test for stats input and display functions 
    Player_stats stat_1; // Test custom constructs using 5e standard array for testing  

    //Create equipment tracker object for testing functions
    Equipment_tracker track_1;

    //Create character object to test functions
    Character char_1;

    char_1.setEquipmentTrackObj(track_1);

    equipment weapon_1; // Create equipment object for testing functions

    equipment weapon_2; // 

    Spell spell_1; // Create spell object for testing functions
    char_1.setStatObj(stat_1);

    char_1.getStatObj()->setAllScores();
    char_1.setCharacterComponents();



    // Test getters and setters for equipment objects
    weapon_1.setEquipmentName("Great axe");
    weapon_1.setEquipmentUse("2d6 + 4 slash damage");
    weapon_1.setEquipmentName("Greatsword");
    weapon_2.setEquipmentName("fist");
    weapon_2.setEquipmentUse("punch");






    // Test getters and setters for spell objects
    spell_1.setSpellName("Fireball!");
    spell_1.setSpellType("Evocation");
    spell_1.setSpellEffect("I Dont care how big the room is, I said cast fireball!");




    // Test Functions for adding and removing item objects assigned to a character
    char_1.getEquipmentTrackerObj()->addItem(&weapon_1);
    char_1.getEquipmentTrackerObj()->addItem(&weapon_2);


    char_1.getEquipmentTrackerObj()->removeItem(2); // Currently uses item index to remove, will be improved later to remove by element




    // Display all details and check for changes 
    char_1.getDetails();
    char_1.getStatObj()->displayAbilityScores(); // Display all stats via the character objects


    spell_1.DisplaySpellProperties(); // Display spell details


    char_1.getEquipmentTrackerObj()->DisplayItems();

    cout << "COMPILER CHECK" << endl;
    cout << "OUTPUT TEST FINISH" << endl;












    */
   
    cin.get();
}
