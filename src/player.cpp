// Player.cpp
#include "Player.h"
#include <iostream>
#include <limits>
#include <cctype> // For toupper
#include "Strategy.h" // Ensure this is included after defining Strategy interface

// Helper function to convert user input into a Choice
Choice charToChoice(char input) {
    switch (input) {
        case 'R': return Choice::ROCK;
        case 'P': return Choice::PAPER;
        case 'S': return Choice::SCISSORS;
        default: return Choice::ROCK;
    }
}
