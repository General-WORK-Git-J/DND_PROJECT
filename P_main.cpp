

#include <iostream>
#include <string>

#include "H_stats.h"
#include "H_Character.h"
#include "H_equipment.h"
#include "H_spells.h"

using namespace std;


int main()
{

cout << "OUTPUT TEST START" << endl;

// Test for stats input and display functions 
Player_stats stat_1(15,14,13,12,10,8,5,8); // Test custom constructs using 5e standard array for testing  
Character char_1("Paul","Warlock","Human",15,0,1, stat_1); // assign stat object to character object to test functions
equipment weapon_1; // Create equipment object for testing functions
Spell spell_1;


// Test setters and getters for character details
char_1.setCharName("Thrikna");
char_1.setCharClass("Fighter");
char_1.setRace("Orc");
char_1.setAge(20);
char_1.setWeight(80);
char_1.setLevel(5);

// Test getters and setters for stat details using character object
char_1.getStatObj().setInitiative(2);
char_1.getStatObj().setProficiency(3);
char_1.getStatObj().setAbility(18, 1); // Check for proper changing
char_1.getStatObj().setAbility(26, 2); // Check for improper changing 

// Test getters and setters for equipment objects
weapon_1.setEquipmentName("Greatsword");
weapon_1.setEquipmentUse("2d6 + 4 slash damage");

// Test getters and setters for spell objects
spell_1.setSpellName("Fireball!");
spell_1.setSpellType("Evocation");
spell_1.setSpellEffect("I Dont care how big the room is, I said cast fireball!");


// Display all details and check for changes 
char_1.getDetails();
char_1.getStatObj().displayAbilityScores(); // Display all stats via the character objects

weapon_1.displayEquipmentDetails(); // Display equipment details

spell_1.DisplaySpellProperties(); // Display spell details

cout << "COMPILER CHECK" << endl;
cout << "OUTPUT TEST FINISH" << endl;














    cin.get();
}
