#include "H_spells.h"

//-----------------------------------------------------//
// Constructors

Spell::Spell()
{
    Spell_Name = "";
    Spell_Type = "";
    Spell_Effect = "";
    Spell_Level = 0;
    Spell_Time = "";
    Spell_Range = "";
    Spell_Components = "";
    Spell_Duration = "";
    Spell_Saving_Throw = "";
    Spell_Description = "";
}

Spell::Spell(string s_n, string s_t, string s_e, int s_l, string s_ti, string s_r, string s_c, string s_d, string s_s, string s_de)
{
    Spell_Name = s_n;
    Spell_Type = s_t;
    Spell_Effect = s_e;
    Spell_Level = s_l;
    Spell_Time = s_ti;
    Spell_Range = s_r;
    Spell_Components = s_c;
    Spell_Duration = s_d;
    Spell_Saving_Throw = s_s;
    Spell_Description = s_de;
}
//-----------------------------------------------------//
// Setters

void Spell::setSpellName(string s_n){Spell_Name = s_n;}
void Spell::setSpellType(string s_t){Spell_Type = s_t;}
void Spell::setSpellEffect(string s_e){Spell_Effect = s_e;}
void Spell::setSpellLevel(int s_l){Spell_Level = s_l;}
void Spell::setSpellTime(string s_ti){Spell_Time = s_ti;}
void Spell::setSpellRange(string s_r){Spell_Range = s_r;}
void Spell::setSpellComponents(string s_c){Spell_Components = s_c;}
void Spell::setSpellDuration(string s_d){Spell_Duration = s_d;}
void Spell::setSpellSavingThrow(string s_s){Spell_Saving_Throw = s_s;}
void Spell::setSpellDescription(string s_de){Spell_Description = s_de;}

//-----------------------------------------------------//
// Getters

string Spell::getSpellName(){return Spell_Name;}
string Spell::getSpellType(){return Spell_Type;}
string Spell::getSpellEffect(){return Spell_Effect;}
string Spell::getSpellTime(){return Spell_Time;}
string Spell::getSpellRange(){return Spell_Range;}
string Spell::getSpellComponents(){return Spell_Components;}
string Spell::getSpellDuration(){return Spell_Duration;}
string Spell::getSpellSavingThrow(){return Spell_Saving_Throw;}
string Spell::getSpellDescription(){return Spell_Description;}
int Spell::getSpellLevel(){return (Spell_Level);}

//-----------------------------------------------------//
// Display 

void Spell::DisplaySpellProperties()
{
    cout << "Spell Name: " << getSpellName() << endl;
    cout << "Spell Type: " << getSpellType() << endl;
    cout << "Spell Effect: " << getSpellEffect() << endl;
    cout << "Spell Level: " << getSpellLevel() << endl;
    cout << "Spell Time: " << getSpellTime() << endl;
    cout << "Spell Range: " << getSpellRange() << endl;
    cout << "Spell Components: " << getSpellComponents() << endl;
    cout << "Spell Duration: " << getSpellDuration() << endl;
    cout << "Spell Saving Throw: " << getSpellSavingThrow() << endl;
    cout << "Spell Description: " << getSpellDescription() << endl;
}
