
#include <iostream>
#include <fstream>
#include "H_CharacterManager.h"

using namespace std;

int main() {
    CharacterManager manager;
    int choice;
    
    do {
        cout << "\n=== DnD Manager ===\n";
        cout << "1. Create\n";
        cout << "2. View\n";
        cout << "3. Edit\n";
        cout << "4. Save\n";
        cout << "5. Load\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.createCharacter(); break;
            case 2: manager.viewCharacters(); break;
            case 3: manager.editCharacter(); break;
            case 4: manager.saveToFile("characters.txt"); break;
            case 5: manager.loadFromFile("characters.txt"); break;
        }

    } while (choice != 0);

    return 0;
}