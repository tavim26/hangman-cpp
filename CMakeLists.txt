cmake_minimum_required(VERSION 3.16)
project(Hangman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(hangman
    src/main.cpp
    src/hangman.cpp
)

target_include_directories(hangman PRIVATE include)

if(MSVC)
    target_compile_options(hangman PRIVATE /W4)
else()
    target_compile_options(hangman PRIVATE -Wall -Wextra -Wpedantic)
endif()