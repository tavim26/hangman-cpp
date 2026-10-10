#include <iostream>
#include "hangman.h"

using namespace std;

int main()
{
    while (true)
    {
        showMenu();
        int option = readNumber(1, 3);

        switch (option)
        {
            case 1:
            {
                cout << endl;
                showDifficulty();
                int difficulty = readNumber(1, 3);

                cout << endl;
                showCategories();
                int category = readNumber(1, 5);

                gameLogic(difficulty, category);
                break;
            }

            case 2:
                cout << endl;
                showInstructions();
                cout << endl;
                break;

            case 3:
                cout << "Goodbye!" << endl;
                return 0;
        }
    }
}