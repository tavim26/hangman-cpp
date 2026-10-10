#include "console.h"

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
    // Gallows drawings, from an empty gallows to the complete figure.
    const std::vector<std::string> gallowsStages = {
        "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n",
    };

    // Reads a whole line. If the input is closed (e.g. Ctrl+D), the program
    // ends instead of looping forever.
    std::string readLine()
    {
        std::string line;
        if (!std::getline(std::cin, line))
        {
            std::cout << "\nGoodbye!\n";
            std::exit(0);
        }
        return line;
    }

    // Keeps asking until the user enters a whole number in [min, max].
    int readNumber(int min, int max)
    {
        while (true)
        {
            std::istringstream input(readLine());
            int value;
            char extra;

            if (input >> value && !(input >> extra) && value >= min && value <= max)
            {
                return value;
            }
            std::cout << "Please enter a number between " << min << " and " << max << ": ";
        }
    }

    // Keeps asking until the user enters exactly one letter.
    char readLetter()
    {
        while (true)
        {
            std::string line = readLine();

            if (line.length() == 1 && std::isalpha(static_cast<unsigned char>(line[0])))
            {
                return line[0];
            }
            std::cout << "Please enter a single letter: ";
        }
    }

    // Picks the drawing that matches how close the player is to losing,
    // so the figure is complete exactly on the last allowed mistake.
    const std::string& gallowsFor(const HangmanGame& game)
    {
        int lastStage = static_cast<int>(gallowsStages.size()) - 1;
        int stage = (game.wrongGuesses() * lastStage + game.maxWrongGuesses() - 1) / game.maxWrongGuesses();
        return gallowsStages[stage];
    }

    std::string spaced(const std::string& text)
    {
        std::string result;
        for (char c : text)
        {
            if (!result.empty())
            {
                result += ' ';
            }
            result += c;
        }
        return result;
    }

    void showGameState(const HangmanGame& game)
    {
        std::cout << '\n' << gallowsFor(game) << '\n';
        std::cout << "Word:               " << spaced(game.maskedWord()) << '\n';
        std::cout << "Wrong guesses left: " << game.remainingWrongGuesses() << '\n';
        std::cout << "Guessed letters:    " << spaced(std::string(game.guessedLetters().begin(),
                                                                  game.guessedLetters().end())) << '\n';
    }
}

MenuOption askMenuOption()
{
    std::cout << "=== HANGMAN ===\n";
    std::cout << "1 - Play\n";
    std::cout << "2 - Instructions\n";
    std::cout << "3 - Exit\n";
    std::cout << "Choose your option: ";

    return static_cast<MenuOption>(readNumber(1, 3));
}

const Difficulty& askDifficulty()
{
    const auto& difficulties = getDifficulties();

    std::cout << "\nChoose a difficulty level:\n";
    for (std::size_t i = 0; i < difficulties.size(); ++i)
    {
        std::cout << i + 1 << " - " << difficulties[i].name << '\n';
    }
    std::cout << "Your choice: ";

    return difficulties[readNumber(1, static_cast<int>(difficulties.size())) - 1];
}

const Category& askCategory()
{
    const auto& categories = getCategories();

    std::cout << "\nChoose a category:\n";
    for (std::size_t i = 0; i < categories.size(); ++i)
    {
        std::cout << i + 1 << " - " << categories[i].name << '\n';
    }
    std::cout << "Your choice: ";

    return categories[readNumber(1, static_cast<int>(categories.size())) - 1];
}

void showInstructions()
{
    std::cout << "\nHOW TO PLAY\n";
    std::cout << "Guess the secret word one letter at a time, before the hangman is complete.\n";
    std::cout << "Guesses are not case-sensitive, and repeating a letter costs nothing.\n";

    std::cout << "\nDifficulty levels (wrong guesses allowed):\n";
    for (const auto& difficulty : getDifficulties())
    {
        std::cout << "  " << difficulty.name << ": " << difficulty.maxWrongGuesses << '\n';
    }

    std::cout << "\nCategories:\n";
    for (const auto& category : getCategories())
    {
        std::cout << "  " << category.name << '\n';
    }
    std::cout << "\nHave fun!\n\n";
}

void playRound(const Difficulty& difficulty, const Category& category)
{
    HangmanGame game(pickRandomWord(category), difficulty.maxWrongGuesses);

    std::cout << "\nCategory: " << category.name << " | Difficulty: " << difficulty.name << '\n';

    while (!game.isOver())
    {
        showGameState(game);
        std::cout << "Enter a letter: ";

        char letter = readLetter();

        switch (game.guess(letter))
        {
            case HangmanGame::GuessResult::Correct:
                std::cout << "Good guess!\n";
                break;
            case HangmanGame::GuessResult::Wrong:
                std::cout << "Wrong guess!\n";
                break;
            case HangmanGame::GuessResult::AlreadyGuessed:
                std::cout << "You already tried '" << letter << "'. Try another letter.\n";
                break;
        }
    }

    showGameState(game);

    if (game.isWon())
    {
        std::cout << "\nCongratulations! You guessed the word: " << game.secretWord() << "\n\n";
    }
    else
    {
        std::cout << "\nYou lost! The word was: " << game.secretWord() << "\nBetter luck next time!\n\n";
    }
}