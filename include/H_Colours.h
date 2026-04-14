#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <iostream>

#define  BLACK                  0
#define  BLUE                   1
#define  GREEN                  2
#define  AQUA                   3
#define  RED                    4
#define  PURPLE                 5
#define  YELLOW                 6
#define  WHITE                  7
#define  GRAY                   8
#define  LIGHT_BLUE             9
#define  LIGHT_GREEN            10    
#define  LIGHT_AQUA             11
#define  LIGHT_RED              12
#define  LIGHT_PURPLE           13
#define  LIGHT_YELLOW           14
#define  BRIGHT_WHITE           15


class Colour_manager
{
    private:

    HANDLE console_colour = GetStdHandle(STD_OUTPUT_HANDLE);
    


    public:

    // Setters

    void setColour(int colour_code);

    // Getters
    HANDLE getHandle();
    //Display
    void DisplayColourcodes();

    //Utilities

    void ChangeColour();

    

};