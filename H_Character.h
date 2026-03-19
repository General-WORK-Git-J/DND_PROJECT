#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <fstream>
#include <limits>
#include <cmath>

#include "H_Inventory.h"

class Character {
private:

    // Character details
    std::string name;
    std::string race;
    std::string characterClass;
    std::string background;
    std::string alignment;
    int level;
    int age;
    int weight;

    // Stats
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
    int Initiative;
    int proficiency;


    Inventory inventory;

public:
    Character(std::string n, std::string r, std::string c, std::string b, std::string a, int lvl, int age, int weight, int str, int dex, int con, int intl, int wis, int cha, int init, int prof);

    // Display functions
    void display() const;

    // Getters
    std::string getName() const;
    std::string getRace() const;
    std::string getClass() const;
    std::string getBackground() const;
    std::string getAlignment() const;
    int getLevel() const;
    int getAge() const;
    int getWeight();
    int getStrength() const;
    int getDexterity() const;
    int getConstitution() const;
    int getIntelligence() const;
    int getWisdom() const;
    int getCharisma() const;
    int getInitiative() const;
    int getProficiency() const;

    int getAbilityModifier(int& ability_score);

    // Setters
    void setName(const std::string& n);
    void setRace(const std::string& r);
    void setClass(const std::string& c);
    void setBackground(const std::string& b);
    void setAlignment(const std::string& a);
    void setLevel(int lvl);
    void setAge(int age);
    void setWeight(int weight);
    void setStrength(int str);
    void setDexterity(int dex);
    void setConstitution(int con);
    void setIntelligence(int intl);
    void setWisdom(int wis);
    void setCharisma(int cha);
    void setInitiative(int init);
    void setProficiency(int prof);

    void setStats(int new_AS, int ability_to_change);

    // Inventory
    void addItem(const Item& item);
    void removeItem(int index);
    void showInventory() const;
    void clearInventory();

    // File functions
    void save(std::ofstream& file) const;
};

#endif