#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "hangman.h"

using namespace std;


map<int, vector<string>> wordCategories = {
    {1, {"Toyota", "Ford", "BMW", "Honda", "Tesla"}},      // Cars
    {2, {"Apple", "Banana", "Cherry", "Grape", "Orange"}}, // Fruits
    {3, {"Dog", "Cat", "Elephant", "Tiger", "Lion"}},      // Animals
    {4, {"USA", "Canada", "Germany", "France", "Italy"}},  // Countries
    {5, {"NewYork", "Paris", "Tokyo", "London", "Berlin"}}  // Cities
};


void showMenu() 
{
    cout << "Welcome to the Hangman! " << endl;
    cout << "1 - Play!" << endl;
    cout << "2 - Instructions" << endl;
    cout << "3 - Exit" << endl;
    cout << "Choose your option: ";
}

void showDifficulty() 
{
    cout << "Firstly, choose a difficulty level\n";
    cout << "1 - Easy\n";
    cout << "2 - Medium\n";
    cout << "3 - Hard\n";
}

void showCategories()
 {
    cout << "Now, choose a category\n";
    cout << "1 - Cars\n";
    cout << "2 - Fruits\n";
    cout << "3 - Animals\n";
    cout << "4 - Countries\n";
    cout << "5 - Cities\n";
}

void showInstructions() 
{
    cout << "Instructions for the Hangman Game:\n";
    cout << "The objective of the game is to guess the secret word before making a limited number of mistakes.\n";
    cout << "Words may contain both uppercase and lowercase letters.\n";
    cout << "\nDifficulty Levels:\n";
    cout << "1. Easy: 10 attempts\n";
    cout << "2. Medium: 6 attempts\n";
    cout << "3. Hard: 3 attempts\n";
    cout << "After you choose the difficulty level, you may choose a category:\n";
    cout << "(cars, fruits, animals, countries, cities)\n";
    cout << "Have fun!\n";
}

vector<string> getWordsByCategory(int category) 
{
    if (wordCategories.find(category) != wordCategories.end()) 
    {
        return wordCategories[category];
    }
    return {};
}

string selectRandomWord(const vector<string> &words) 
{
    if (!words.empty()) 
    {
        srand(time(0)); 
        int index = rand() % words.size();

        return words[index];
    }
    return "";
}

void gameLogic(int difficulty, int category) 
{
    int nrOfTries;
    
    switch (difficulty) {
        case 1: nrOfTries = 10; break;
        case 2: nrOfTries = 6; break;
        case 3: nrOfTries = 3; break;
        default: nrOfTries = 10; break; 
    }

    char c;
    string word = selectRandomWord(getWordsByCategory(category));
    string templateWord(word.length(), '#');
    vector<char> introducedCharacters;

    while (nrOfTries > 0) {
        cout<<endl;
        cout << "Your word, so far: " << templateWord << endl;
        cout << "Number of tries left: " << nrOfTries << endl;
        cout << "Introduced characters: ";
        for (char ch : introducedCharacters) 
        {
            cout << ch << ' ';
        }
        cout << "\nEnter a character: ";
        
        cin >> c;
        introducedCharacters.push_back(c);

        if (word.find(c) != string::npos) 
        {
            for (size_t i = 0; i < word.length(); ++i) 
            {
                if (word[i] == c) 
                {
                    templateWord[i] = c;
                }
            }
        } 
        --nrOfTries;

        if (templateWord == word) 
        {
            cout <<endl<< "Congratulations! You've won the game!" << endl;
            cout<<"The word was: "<<word<<endl<<endl;
            return;
        }
    }


    cout <<endl<< "You lost! The correct word was: " << word << endl<< "Better luck next time!" << endl <<endl;
}
