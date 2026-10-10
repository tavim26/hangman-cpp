#include "words.h"

#include <random>

const std::vector<Category>& getCategories()
{
    static const std::vector<Category> categories = {
        {"Cars",      {"Toyota", "Ford", "BMW", "Honda", "Tesla"}},
        {"Fruits",    {"Apple", "Banana", "Cherry", "Grape", "Orange"}},
        {"Animals",   {"Dog", "Cat", "Elephant", "Tiger", "Lion"}},
        {"Countries", {"USA", "Canada", "Germany", "France", "Italy"}},
        {"Cities",    {"NewYork", "Paris", "Tokyo", "London", "Berlin"}},
    };
    return categories;
}

std::string pickRandomWord(const Category& category)
{
    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<std::size_t> distribution(0, category.words.size() - 1);

    return category.words[distribution(generator)];
}