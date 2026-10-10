#include "game.h"

#include <algorithm>
#include <cctype>
#include <utility>

namespace
{
    char toLower(char c)
    {
        return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
}

const std::vector<Difficulty>& getDifficulties()
{
    static const std::vector<Difficulty> difficulties = {
        {"Easy",   10},
        {"Medium",  6},
        {"Hard",    3},
    };
    return difficulties;
}

HangmanGame::HangmanGame(std::string secretWord, int maxWrongGuesses)
    : secretWord_(std::move(secretWord)), maxWrongGuesses_(maxWrongGuesses)
{
}

HangmanGame::GuessResult HangmanGame::guess(char letter)
{
    letter = toLower(letter);

    if (hasBeenGuessed(letter))
    {
        return GuessResult::AlreadyGuessed;
    }
    guessedLetters_.push_back(letter);

    bool inWord = std::any_of(secretWord_.begin(), secretWord_.end(),
                              [letter](char c) { return toLower(c) == letter; });
    if (inWord)
    {
        return GuessResult::Correct;
    }

    ++wrongGuesses_;
    return GuessResult::Wrong;
}

std::string HangmanGame::maskedWord() const
{
    std::string masked;
    for (char c : secretWord_)
    {
        masked += hasBeenGuessed(toLower(c)) ? c : '_';
    }
    return masked;
}

const std::string& HangmanGame::secretWord() const
{
    return secretWord_;
}

const std::vector<char>& HangmanGame::guessedLetters() const
{
    return guessedLetters_;
}

int HangmanGame::wrongGuesses() const
{
    return wrongGuesses_;
}

int HangmanGame::maxWrongGuesses() const
{
    return maxWrongGuesses_;
}

int HangmanGame::remainingWrongGuesses() const
{
    return maxWrongGuesses_ - wrongGuesses_;
}

bool HangmanGame::isWon() const
{
    return maskedWord() == secretWord_;
}

bool HangmanGame::isLost() const
{
    return wrongGuesses_ >= maxWrongGuesses_;
}

bool HangmanGame::isOver() const
{
    return isWon() || isLost();
}

bool HangmanGame::hasBeenGuessed(char letter) const
{
    return std::find(guessedLetters_.begin(), guessedLetters_.end(), letter) != guessedLetters_.end();
}