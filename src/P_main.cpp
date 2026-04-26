
#include <iostream>
#include <fstream>
#include <limits>
#include "H_CharacterManager.h"
#include "H_CharacterFeatures.h"
#include "H_DiceRoller.h"
#include "H_SpellBook.h"
#include "H_Colours.h"
#include "H_DndExceptions.h"

int main() {
  try {

    // Initialize character and colour manager objects
    CharacterManager manager;
    Colour_manager col_manager;
    // Dice roller is available from the main menu as a utility tool.
    DiceRoller diceRoller;

    int choice;

    do {

        // Main menu
        std::cout << "\n=== DnD Manager ===\n";
        std::cout << "1. Create Character\n";
        std::cout << "2. View Characters\n";
        std::cout << "3. Manage Global Spells\n";
        std::cout << "4. Change Text Colour\n";
        std::cout << "5. Roll Dice\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: manager.createCharacter(); break;
            case 2:
            {
                int characterMenuChoice = -1;
                do
                {
                    std::cout << "\n=== View Character ===\n";
                    std::cout << "1. Load Characters\n";
                    std::cout << "2. View Character Details\n";
                    std::cout << "3. Edit Character\n";
                    std::cout << "4. Save Characters\n";
                    std::cout << "0. Back\n";
                    std::cout << "Choice: ";

                    std::cin >> characterMenuChoice;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    switch (characterMenuChoice)
                    {
                        case 1:
                            manager.loadAll();
                            break;
                        case 2:
                            manager.viewCharacters();
                            break;
                        case 3:
                            manager.editCharacter();
                            break;
                        case 4:
                            manager.saveAll();
                            break;
                        case 0:
                            break;
                        default:
                            std::cout << "Invalid choice.\n";
                            break;
                    }
                } while (characterMenuChoice != 0);
                break;
            }
            case 3: manager.manageGlobalSpells(); break;
            case 4: col_manager.ChangeColour(); break;
            case 5: diceRoller.promptAndRoll(); break;
            case 0: break;
            default: std::cout << "Invalid choice.\n"; break;
        }

    } while (choice != 0);
    col_manager.setColour(WHITE); // Set terminal colour back to white before closing program
    return 0;

  } catch (const std::exception& e) {
    std::cerr << "\nFatal error: " << e.what() << "\n";
    return 1;
  } catch (...) {
    std::cerr << "\nUnknown fatal error.\n";
    return 1;
  }
}
