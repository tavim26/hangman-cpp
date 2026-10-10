#ifndef CONSOLE_H
#define CONSOLE_H

#include "game.h"
#include "words.h"

// Everything that reads from the keyboard or prints to the screen.

enum class MenuOption { Play = 1, Instructions, Exit };

MenuOption askMenuOption();
const Difficulty& askDifficulty();
const Category& askCategory();

void showInstructions();

// Plays one full round, from the first guess to the win/lose message.
void playRound(const Difficulty& difficulty, const Category& category);

#endif // CONSOLE_H