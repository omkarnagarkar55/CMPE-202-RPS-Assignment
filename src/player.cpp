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
        default: return Choice::UNKNOWN;
    }
}

Choice HumanPlayer::makeChoice() {
    char input;
    std::cout << getName() << ", enter your choice (R for Rock, P for Paper, S for Scissors): ";
    std::cin >> input;
    // Clear the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Choice choice = charToChoice(toupper(input));
    while (choice == Choice::UNKNOWN) {
        std::cout << "Invalid choice. Please enter R, P, or S: ";
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        choice = charToChoice(toupper(input));
    }
    return choice;
}

ComputerPlayer::ComputerPlayer(std::unique_ptr<Strategy> strategy)
    : strategy(std::move(strategy)) {}

Choice ComputerPlayer::makeChoice() {
    return strategy->determineChoice();
}
