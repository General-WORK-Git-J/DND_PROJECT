#include "H_DiceRoller.h"
#include <chrono>
#include <iostream>
#include <limits>
#include <numeric>
#include <thread>

namespace {
// Restrict the interactive roller to the standard dice used in this project.
bool isSupportedDie(int sides)
{
    return sides == 4 || sides == 6 || sides == 8 || sides == 10 ||
           sides == 12 || sides == 20 || sides == 100;
}

// Small timed animation used only by the interactive menu flow.
void showRollAnimation()
{
    std::cout << "Rolling";
    for (int i = 0; i < 6; i++)
    {
        std::cout << "#" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }
    std::cout << "\n";
}
}

DiceRoller::DiceRoller()
    // Seed from the current time so each run produces different rolls.
    : rng(static_cast<std::mt19937::result_type>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()))
{
}

int DiceRoller::rollDie(int sides)
{
    // Produce one random result in the inclusive range [1, sides].
    std::uniform_int_distribution<int> distribution(1, sides);
    return distribution(rng);
}

std::vector<int> DiceRoller::rollDice(int count, int sides)
{
    std::vector<int> rolls;
    // Roll the same die multiple times and keep each individual result.
    for (int i = 0; i < count; i++)
    {
        rolls.push_back(rollDie(sides));
    }
    return rolls;
}

int DiceRoller::totalRoll(const std::vector<int>& rolls) const
{
    // Sum all individual dice into the final combined total.
    return std::accumulate(rolls.begin(), rolls.end(), 0);
}

D20RollResult DiceRoller::rollD20(D20Mode mode)
{
    D20RollResult result{};
    result.firstRoll = rollDie(20);
    result.secondRoll = rollDie(20);

    // Advantage keeps the higher roll, disadvantage keeps the lower roll.
    if (mode == D20Mode::Advantage)
    {
        result.chosenRoll = std::max(result.firstRoll, result.secondRoll);
    }
    else if (mode == D20Mode::Disadvantage)
    {
        result.chosenRoll = std::min(result.firstRoll, result.secondRoll);
    }
    else
    {
        result.chosenRoll = result.firstRoll;
    }

    return result;
}

void DiceRoller::promptAndRoll()
{
    int sides = 0;
    std::cout << "\n=== Dice Roller ===\n";
    std::cout << "Choose a die (4, 6, 8, 10, 12, 20, 100): ";
    std::cin >> sides;

    if (std::cin.fail() || !isSupportedDie(sides))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid die choice.\n";
        return;
    }

    if (sides == 20)
    {
        // d20 rolls get a separate prompt for advantage/disadvantage handling.
        int modeChoice = 0;
        std::cout << "1. Normal\n";
        std::cout << "2. Advantage\n";
        std::cout << "3. Disadvantage\n";
        std::cout << "Choice: ";
        std::cin >> modeChoice;

        if (std::cin.fail() || modeChoice < 1 || modeChoice > 3)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid roll mode.\n";
            return;
        }

        D20Mode mode = D20Mode::Normal;
        if (modeChoice == 2)
        {
            mode = D20Mode::Advantage;
        }
        else if (modeChoice == 3)
        {
            mode = D20Mode::Disadvantage;
        }

        showRollAnimation();
        D20RollResult result = rollD20(mode);

        if (mode == D20Mode::Normal)
        {
            std::cout << "Result: " << result.chosenRoll << "\n";
        }
        else
        {
            // Show both d20 rolls so the player can see what advantage/disadvantage did.
            std::cout << "Rolls: " << result.firstRoll << ", " << result.secondRoll << "\n";
            std::cout << "Chosen result: " << result.chosenRoll << "\n";
        }
        return;
    }

    if (sides == 100)
    {
        // d100 is always rolled once, so no quantity prompt is needed.
        showRollAnimation();
        std::cout << "Result: " << rollDie(100) << "\n";
        return;
    }

    // All other supported dice ask how many copies of that die to roll.
    int count = 0;
    std::cout << "How many d" << sides << " would you like to roll? ";
    std::cin >> count;

    if (std::cin.fail() || count < 1)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid number of dice.\n";
        return;
    }

    showRollAnimation();
    std::vector<int> rolls = rollDice(count, sides);
    std::cout << "Rolls: ";
    for (size_t i = 0; i < rolls.size(); i++)
    {
        std::cout << rolls[i];
        if (i + 1 < rolls.size())
        {
            std::cout << ", ";
        }
    }
    std::cout << "\nTotal: " << totalRoll(rolls) << "\n";
}
