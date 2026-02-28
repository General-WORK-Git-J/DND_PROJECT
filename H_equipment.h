
#ifndef _EQUIPMENT_
#define _EQUIPMENT_

#include "H_Character.h"


#include <iostream>
#include <string>
#include <vector>



using namespace std; 



class equipment : Character
{
    private:
    // Member variables
    string name;
    string use;



    public:

    //Constructors
    equipment();
    equipment(string n, string u);


    // Setters 
    void setEquipmentName(string n);
    void setEquipmentUse(string u);


    // Getters
    string getEquipmentName();
    string getEquipmentuse();


 

    // Display functions
    void displayEquipmentDetails();
};


#endif