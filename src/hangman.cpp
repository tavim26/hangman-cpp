#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <cctype>
#include <cstdlib>
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
    cout << "Your choice: ";
}

void showCategories()
{
    cout << "Now, choose a category\n";
    cout << "1 - Cars\n";
    cout << "2 - Fruits\n";
    cout << "3 - Animals\n";
    cout << "4 - Countries\n";
    cout << "5 - Cities\n";
    cout << "Your choice: ";
}

void showInstructions()
{
    cout << "Instructions for the Hangman Game:\n";
    cout << "The objective of the game is to guess the secret word, one letter at a time,\n";
    cout << "before making too many wrong guesses.\n";
    cout << "Guesses are not case-sensitive, and repeating a letter costs nothing.\n";
    cout << "\nDifficulty Levels (wrong guesses allowed):\n";
    cout << "1. Easy: 10\n";
    cout << "2. Medium: 6\n";
    cout << "3. Hard: 3\n";
    cout << "After you choose the difficulty level, you may choose a category:\n";
    cout << "(cars, fruits, animals, countries, cities)\n";
    cout << "Have fun!\n";
}

// Reads a whole line from the keyboard. If the input stream is closed
// (e.g. Ctrl+D), the program ends instead of looping forever.
static string readLine()
{
    string line;
    if (!getline(cin, line))
    {
        cout << endl << "Goodbye!" << endl;
        exit(0);
    }
    return line;
}

int readNumber(int min, int max)
{
    while (true)
    {
        istringstream input(readLine());
        int value;
        char extra;

        if (input >> value && !(input >> extra) && value >= min && value <= max)
        {
            return value;
        }
        cout << "Please enter a number between " << min << " and " << max << ": ";
    }
}

char readLetter()
{
    while (true)
    {
        string line = readLine();

        if (line.length() == 1 && isalpha(static_cast<unsigned char>(line[0])))
        {
            return static_cast<char>(tolower(static_cast<unsigned char>(line[0])));
        }
        cout << "Please enter a single letter: ";
    }
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
    if (words.empty())
    {
        return "";
    }

    static mt19937 generator(random_device{}());
    uniform_int_distribution<size_t> distribution(0, words.size() - 1);

    return words[distribution(generator)];
}

void gameLogic(int difficulty, int category)
{
    int triesLeft;

    switch (difficulty) {
        case 1: triesLeft = 10; break;
        case 2: triesLeft = 6; break;
        case 3: triesLeft = 3; break;
        default: triesLeft = 10; break;
    }

    string word = selectRandomWord(getWordsByCategory(category));
    string templateWord(word.length(), '#');
    vector<char> guessedLetters;

    while (triesLeft > 0) {
        cout << endl;
        cout << "Your word, so far: " << templateWord << endl;
        cout << "Wrong guesses left: " << triesLeft << endl;
        cout << "Guessed letters: ";
        for (char ch : guessedLetters)
        {
            cout << ch << ' ';
        }
        cout << "\nEnter a letter: ";

        char guess = readLetter();

        if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end())
        {
            cout << "You already tried '" << guess << "'. Try another letter." << endl;
            continue;
        }
        guessedLetters.push_back(guess);

        bool found = false;
        for (size_t i = 0; i < word.length(); ++i)
        {
            if (tolower(static_cast<unsigned char>(word[i])) == guess)
            {
                templateWord[i] = word[i];
                found = true;
            }
        }

        if (found)
        {
            cout << "Good guess!" << endl;
        }
        else
        {
            --triesLeft;
            cout << "Wrong guess!" << endl;
        }

        if (templateWord == word)
        {
            cout << endl << "Congratulations! You've won the game!" << endl;
            cout << "The word was: " << word << endl << endl;
            return;
        }
    }

    cout << endl << "You lost! The correct word was: " << word << endl << "Better luck next time!" << endl << endl;
}