#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

// A difficulty level: how many wrong guesses the player is allowed.
struct Difficulty
{
    std::string name;
    int maxWrongGuesses;
};

// All available difficulty levels, in the order they are shown in the menu.
const std::vector<Difficulty>& getDifficulties();

// The state and rules of a single round of Hangman.
// This class does no input/output, so it is independent of the console.
class HangmanGame
{
public:
    enum class GuessResult { Correct, Wrong, AlreadyGuessed };

    HangmanGame(std::string secretWord, int maxWrongGuesses);

    // Letters are case-insensitive. Repeating a letter costs nothing.
    GuessResult guess(char letter);

    // The secret word with unguessed letters replaced by '_'.
    std::string maskedWord() const;

    const std::string& secretWord() const;
    const std::vector<char>& guessedLetters() const;
    int wrongGuesses() const;
    int maxWrongGuesses() const;
    int remainingWrongGuesses() const;

    bool isWon() const;
    bool isLost() const;
    bool isOver() const;

private:
    bool hasBeenGuessed(char letter) const;

    std::string secretWord_;
    int maxWrongGuesses_;
    int wrongGuesses_ = 0;
    std::vector<char> guessedLetters_;
};

#endif // GAME_H