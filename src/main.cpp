#include <iostream>

#include "console.h"

int main()
{
    while (true)
    {
        switch (askMenuOption())
        {
            case MenuOption::Play:
            {
                const Difficulty& difficulty = askDifficulty();
                const Category& category = askCategory();
                playRound(difficulty, category);
                break;
            }

            case MenuOption::Instructions:
                showInstructions();
                break;

            case MenuOption::Exit:
                std::cout << "Goodbye!\n";
                return 0;
        }
    }
}