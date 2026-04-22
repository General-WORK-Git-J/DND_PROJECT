
#include <iostream>
#include <fstream>
#include <limits>
#include "H_CharacterManager.h"
#include "H_CharacterFeatures.h"
#include "H_SpellBook.h"
#include "H_Colours.h"

int main() {
    CharacterManager manager;
    Colour_manager col_manager;

    // Get console handle and set text colour. Colour codes are in H_Colours.h (e.g. red = 4)
    //HANDLE console_color;
    //console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(console_color, 4);


    int choice;
    Spellbook globalSpellbook;
    globalSpellbook.loadSpellbook("data/SpellBook.txt");
    
    do {
        std::cout << "\n=== DnD Manager ===\n";
        std::cout << "1. Create\n";
        std::cout << "2. View\n";
        std::cout << "3. Edit\n";
        std::cout << "4. Save\n";
        std::cout << "5. Load\n";
        std::cout << "6. Colour\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: manager.createCharacter(); break;
            case 2: manager.viewCharacters(); break;
            case 3: manager.editCharacter(); break;
            case 4: manager.saveToFile("data/characters.txt"); break;
            case 5: manager.loadFromFile("data/characters.txt"); break;
            case 6: col_manager.ChangeColour(); break;
        }

    } while (choice != 0);
    col_manager.setColour(WHITE);
    return 0;
}