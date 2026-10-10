#ifndef WORDS_H
#define WORDS_H

#include <string>
#include <vector>

// A themed list of words the secret word is picked from.
struct Category
{
    std::string name;
    std::vector<std::string> words;
};

// All available categories, in the order they are shown in the menu.
const std::vector<Category>& getCategories();

// Returns a random word from the given category.
std::string pickRandomWord(const Category& category);

#endif // WORDS_H