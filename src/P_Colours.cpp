#include "H_Colours.h"
#include <limits>

HANDLE Colour_manager::getHandle()
{
    return console_colour;
}


void Colour_manager::DisplayColourcodes()
{
    std::cout << "===Colours==="    << std::endl;
    std::cout << "Black: 0"         << std::endl;
    std::cout << "Blue: 1"          << std::endl;
    std::cout << "Green: 2"         << std::endl;
    std::cout << "Aqua: 3"          << std::endl;
    std::cout << "Red: 4"           << std::endl;
    std::cout << "Purple: 5"        << std::endl;
    std::cout << "Yellow: 6"        << std::endl;
    std::cout << "White: 7"         << std::endl;
    std::cout << "Grey: 8"          << std::endl;
    std::cout << "Light Blue: 9"    << std::endl;
    std::cout << "Light Green: 10"  << std::endl;
    std::cout << "Light Aqua: 11"   << std::endl;
    std::cout << "Light Red: 12"    << std::endl;
    std::cout << "Light Purple: 13" << std::endl;
    std::cout << "Light Yellow: 14" << std::endl;
    std::cout << "Bright White: 15" << std::endl;

}

void Colour_manager::setColour(int colour_code)
{
    SetConsoleTextAttribute(console_colour, colour_code);
}

void Colour_manager::ChangeColour()
{
    DisplayColourcodes();
    std::cout << "What Colour would you like?: " << std::endl;
    int choice;
    if (!(std::cin >> choice))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Colour unchanged." << std::endl;
        return;
    }
    if (choice < 0 || choice > 15)
    {
        std::cout << "Invalid colour code. Please enter a value between 0 and 15." << std::endl;
        return;
    }
    setColour(choice);
}