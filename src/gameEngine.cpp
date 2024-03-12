#include "../include/GameEngine.h"
#include <iostream>

GameEngine::GameEngine(Player* human, ComputerPlayer* computer) : humanPlayer(human), computerPlayer(computer) {
}

void GameEngine::startGame() {
    std::cout << "Rock, Paper, Scissors Game against the Computer!\n";
}

void GameEngine::playRound(Choice userChoice) {
    std::cout << "Playing a round..." << std::endl;
    Choice computerChoice = getComputerChoice();
    std::cout << "User chose: " << choiceToString(userChoice) << std::endl;
    std::cout << "Computer chose: " << choiceToString(computerChoice) << std::endl;
    
    // Determine the winner
    int winner = determineWinner(userChoice, computerChoice);
    
    // Display the result
    if (winner == 0) {
        std::cout << "It's a draw!\n";
    } else if (winner == 1) {
        std::cout << "You win!\n";
    } else {
        std::cout << "Computer wins!\n";
    }
}

void GameEngine::endGame() {
    std::cout << "Game ended!" << std::endl;
    // Display final scores and any cleanup
}

void GameEngine::promptPlayerChoice() {
    std::cout << "Enter R for Rock, P for Paper, S for Scissors: ";
    char userMove;
    std::cin >> userMove;
    Choice userChoice = charToChoice(userMove);
    playRound(userChoice);
}

Choice GameEngine::getComputerChoice() {
    return computerPlayer->makeMove();
}

int GameEngine::determineWinner(Choice userChoice, Choice computerChoice) {
    if (userChoice == computerChoice) {
        return 0; // Draw
    } else if ((userChoice == ROCK && computerChoice == SCISSORS) ||
               (userChoice == PAPER && computerChoice == ROCK) ||
               (userChoice == SCISSORS && computerChoice == PAPER)) {
        return 1; // User wins
    } else {
        return -1; // Computer wins
    }
}

std::string GameEngine::choiceToString(Choice c) {
    switch (c) {
        case ROCK:
            return "Rock";
        case PAPER:
            return "Paper";
        case SCISSORS:
            return "Scissors";
        default:
            return "Unknown";
    }
}

Choice GameEngine::charToChoice(char c) {
    switch (c) {
        case 'R':
            return ROCK;
        case 'P':
            return PAPER;
        case 'S':
            return SCISSORS;
        default:
            return ROCK; // Safe default
    }
}
