#include "H_stats.h"


//Constructor definitions
Player_stats::Player_stats()
{
     Strength = 0;
    Dexterity = 0;
    Constitution = 0;
    Inteligence = 0;
    Wisdom = 0;
    Charisma = 0;
}

Player_stats::Player_stats(int s, int d, int c, int i, int w, int ch, int in, int p)
{
    Strength = s;
    Dexterity = d;
    Constitution = c;
    Inteligence = i;
    Wisdom = w;
    Charisma = ch;
    Initiative = in;
    Proficiency = p;
}

//Setter definitions
void Player_stats::setAbility(int AS, int Ability)
{
    if(AS <= 20 && AS > 0)
    {
        switch (Ability)
        {
        case 1:
            Strength = AS;
            break;

        case 2:
            Dexterity = AS;
            break;

        case 3:
            Constitution = AS;
            break;

        case 4:
            Inteligence = AS;
            break;

        case 5:
            Wisdom = AS;
            break;

        case 6:
            Charisma = AS;
            break;

        default:
            cout << "Not an ability";
        }
    }
    else 
    {
    cout << "Ability score must be between 1 and 20" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Player_stats::setProficiency(int p)
{
    Proficiency = p;
}

void Player_stats::setInitiative(int in)
{
    Initiative = in;
}

void Player_stats::setAllScores()
{
    
    for (int i = 0; i < 6; i++)
    {
        int new_AS;
        cout << "What is your " << Ability_scores[i] << endl;
        cin >> new_AS;
        if (new_AS <= 20 && new_AS > 0)
        {
        setAbility(new_AS, i + 1);
        }
        else 
        {
            cout << "Not a suitable ability score. enter values again: " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            i--;
        }
    }

    int init;
    int prof;

    cout << "What is your initiative: " << endl;
    cin >> init;
    setInitiative(init);

    bool prof_not_set = true;
    while(prof_not_set == true)
    {
    cout << "What is your proficiency: " << endl;
    cin >> prof;
   

    
        if (prof >= 2)
        {
        setProficiency(prof); 
        prof_not_set = false;
        }
        else if (prof < 2)
        {
            cout << "Proficiency is minimum +2, and cannot be set lower! " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else 
        {
            cout << "Not a suitable value, please re-enter values: " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

}

//Getter definitions
int Player_stats::getAbility(int Ability)
{
    switch (Ability)
    {
    case 1:
        return Strength;
        break;

    case 2:
        return Dexterity;
        break;

    case 3:
        return Constitution;
        break;

    case 4:
        return Inteligence;
        break;

    case 5:
        return Wisdom;
        break;

    case 6:
        return Charisma ;
        break;

    default:
        return 0;
    }
}

int Player_stats::getAbilityModifier(int a)
{
    int Ab_mod;
    int Ab_check = getAbility(a);
    Ab_mod = (Ab_check - 10)/2; 
    return Ab_mod;



}

int Player_stats::getProficiency()
{
    return Proficiency;
}

int Player_stats::getInitiative()
{
    return Initiative;
}

//Display definitions
void Player_stats::displayAbilityScores()
{
    for (int i = 1; i <=6; i++ )
    {
        
        cout << Ability_scores[i - 1] << getAbility(i) << "(" << getAbilityModifier(i) << ")" << endl;
    }

    cout << "Initiative: " << getInitiative() <<  endl;
    cout << "Proficiency: " << getProficiency() << endl;
}

