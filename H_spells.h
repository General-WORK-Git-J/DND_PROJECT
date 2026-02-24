#ifndef _SPELLS_
#define _SPELLS_


#include <string>
#include <iostream>

using namespace std;

class Spell
{

    private:

    //Member variables 
    string Spell_Name;
    string Spell_Type;
    string Spell_Effect;


    public: 

    //Constructors
    Spell();
    Spell(string s_n, string s_t, string s_e);

    //Setters
    void setSpellName(string s_n);
    void setSpellType(string s_t);
    void setSpellEffect(string s_e);

    //Getters
    string getSpellName();
    string getSpellType();
    string getSpellEffect();

    //Display Spell Properties
    void DisplaySpellProperties();
    

};

#endif