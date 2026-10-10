# Hangman (C++)

A console implementation of the classic Hangman game, written in C++17 as a university project.

```
Category: Cars | Difficulty: Hard

  +---+
  |   |
  O   |
  |   |
      |
      |
=========

Word:               T _ _ _ t _
Wrong guesses left: 2
Guessed letters:    z t
Enter a letter:
```

## Features

- Three difficulty levels: Easy, Medium and Hard (10, 6 and 3 wrong guesses allowed)
- Five word categories: Cars, Fruits, Animals, Countries, Cities
- ASCII gallows that fills in with each wrong guess
- Case-insensitive guesses; repeating a letter is not penalized
- Input validation for menu choices and guesses

## Build and run

Requires a C++17 compiler and CMake 3.16 or newer.

```bash
git clone https://github.com/tavim26/hangman-cpp.git
cd hangman-cpp
cmake -S . -B build
cmake --build build
./build/hangman
```

## Project structure

```
include/        headers
src/
├── main.cpp    main menu loop
├── game.cpp    HangmanGame class: game state and rules, no input/output
├── words.cpp   word categories and random word selection
└── console.cpp menus, input handling and ASCII drawing
```

The game logic is kept separate from the console interface, so new categories or difficulty levels can be added in one place without touching the rest of the code.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
