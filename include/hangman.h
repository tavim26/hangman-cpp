#ifndef HANGMAN_H
#define HANGMAN_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

void showMenu();
void showDifficulty();
void showCategories();
void showInstructions();
int readNumber(int min, int max);
char readLetter();
std::vector<std::string> getWordsByCategory(int category);
std::string selectRandomWord(const std::vector<std::string>& words);
void gameLogic(int difficulty, int category);

#endif // HANGMAN_H
