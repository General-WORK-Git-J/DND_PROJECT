#include "H_spells.h"

Spell::Spell()
{
    Spell_Name = "";
    Spell_Type = "";
    Spell_Effect = "";

}

Spell::Spell(string s_n, string s_t, string s_e)
{
    Spell_Name = s_n;
    Spell_Type = s_t;
    Spell_Effect = s_e;
}

void Spell::setSpellName(string s_n)
{
    Spell_Name = s_n;
}

void Spell::setSpellType(string s_t)
{
    Spell_Type = s_t;
}

void Spell::setSpellEffect(string s_e)
{
    Spell_Effect = s_e;
}

string Spell::getSpellName()
{
    return Spell_Name;
}

string Spell::getSpellType()
{
    return Spell_Type;
}

string Spell::getSpellEffect()
{
    return Spell_Effect;
}

void Spell::DisplaySpellProperties()
{
    cout << "Spell Name: " << getSpellName() << endl;
    cout << "Spell Type: " << getSpellType() << endl;
    cout << "Spell Effect: " << getSpellEffect() << endl;
}
