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
    int Spell_Level;
    string Spell_Time;
    string Spell_Range;
    string Spell_Components;
    string Spell_Duration;
    string Spell_Saving_Throw;
    string Spell_Description;


    public: 

    //Constructors
    Spell();
    Spell(string s_n, string s_t, string s_e, int s_l, string s_ti, string s_r, string s_c, string s_d, string s_s, string s_de);

    //Setters
    void setSpellName(string s_n);
    void setSpellType(string s_t);
    void setSpellEffect(string s_e);
    void setSpellLevel(int s_l);
    void setSpellTime(string s_t);
    void setSpellRange(string s_r);
    void setSpellComponents(string s_c);
    void setSpellDuration(string s_d);
    void setSpellSavingThrow(string s_s);
    void setSpellDescription(string s_d);

    //Getters
    string getSpellName();
    string getSpellType();
    string getSpellEffect();
    int getSpellLevel();
    string getSpellTime();
    string getSpellRange();
    string getSpellComponents();
    string getSpellDuration();
    string getSpellSavingThrow();
    string getSpellDescription();

    //Display Spell Properties
    void DisplaySpellProperties();
    

};

#endif