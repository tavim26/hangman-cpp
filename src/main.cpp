#include <iostream>
#include "hangman.h"

using namespace std;

int main() {
    int difficulty;
    int category;
    int option;

    while (true) 
    {
        showMenu();
        cin >> option;

        switch (option) 
        {
            case 1:
                
                cout<<endl;
                showDifficulty();
                cin >> difficulty;
                cout<<endl;

                if (difficulty < 1 || difficulty > 3)
                {
                    cout << "Invalid difficulty level! Please choose again." << endl;
                    continue; 
                }

                cout<<endl;
                showCategories();
                cin >> category;
                cout<<endl;

                if (category < 1 || category > 5)
                 {
                    cout << "Invalid category! Please choose again." << endl;
                    continue; 
                }

                gameLogic(difficulty, category);
                break; 

            case 2:

                showInstructions();
                cout<<endl;
                break; 

            case 3:

                cout << "Goodbye!" << endl;
                exit(0); 

            default:
            
                cout << "Invalid option! Please choose 1, 2, or 3." << endl;
                break; 
        }
    }

    return 0;
}
