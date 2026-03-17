
#include <iostream>
#include <string>
#include <memory>

#include "H_stats.h"
#include "H_Character.h"
#include "H_equipment.h"

#include "H_spells.h"

using namespace std;





int main()
{
    map<string, unique_ptr<Character>> Characters;
    

    while (true)
    {
        int choice;

        bool Character_exists;
        string current_char_id;
        

        cout << "1. Create Character\n";
        cout << "2. Exit\n";
        cin >> choice;

        if (choice == 1)
        {
            string char_id;
            cout << "Enter character name: ";
            cin >> char_id;

            Characters.emplace(char_id, std::make_unique<Character>());

            auto& character = Characters[char_id];

            character->setCharacterComponents(char_id);

            Player_stats stat_1;
           

            character->setStatObj(stat_1);
           

            Character_exists = true;

            character->getStatObj()->setAllScores();

            character->getDetails();
            character->getStatObj()->displayAbilityScores();

            while (Character_exists == true)
            {
                int choice;
                cout << "what would you like to do: " << endl;
                cout << "1. Create new item\n";
                cout << "2. View Current items\n";
                cout << "3. Exit\n";

                cin >> choice;

                if (choice == 1)
                {

                
                string new_id;
                cout << "enter new item name: ";
                cin >> new_id;
                character->addItem_to_Map(new_id);
                

                }
                else if (choice == 2)
                {
                character->display_items_in_map();
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




        }


        else if (choice == 2)
        {
            break;
        }

        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

   
    cin.get();
}
