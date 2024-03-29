#include <iostream>
#include <memory>
#include <cctype> // For std::toupper
#include "include/GameEngine.h"
#include "include/HumanPlayer.h"
#include "include/RandomStrategy.h"
#include "include/SmartStrategy.h"
#include "include/Strategy.h"
#include "include/Player.h"
#include "include/FrequencyMap.h"
#include "include/FileHandler.h"

// Function to convert character input to Choice enum
Choice charToChoice(char c) {
    switch (std::toupper(c)) {
        case 'R':
            return ROCK;
        case 'P':
            return PAPER;
        case 'S':
            return SCISSORS;
        default:
            return ROCK; // Default choice
    }
}

int main() {
    std::cout << "Welcome to Rock-Paper-Scissors game!" << std::endl;
    std::cout << "Choose a strategy for the computer player:" << std::endl;
    std::cout << "1. Random strategy" << std::endl;
    std::cout << "2. Smart strategy" << std::endl;
    std::cout << "Enter your choice (1 or 2): ";
    
    int choice;
    std::cin >> choice;
    
    std::unique_ptr<Strategy> strategy;
    FileHandler fileHandler;
    FrequencyMap frequencyMap;
    
    if (choice == 1) {
        strategy = std::make_unique<RandomStrategy>();
    } else if (choice == 2) {
        fileHandler.readFrequenciesFromFile("frequencies.txt",frequencyMap.frequencyMap);
        strategy = std::make_unique<SmartStrategy>(&frequencyMap);
    } else {
        std::cerr << "Invalid choice. Exiting the game." << std::endl;
        return 1;
    }

    Player* computerPlayer = new ComputerPlayer(std::move(strategy));
    
    // Create human player object
    HumanPlayer humanPlayer;
    
    // Create the game engine and start the game
    GameEngine gameEngine(&humanPlayer, dynamic_cast<ComputerPlayer*>(computerPlayer));
    gameEngine.startGame();
    
    // Play the game
    char userInput;
    while (true) {
        //userInput = humanPlayer.makeChoice();
        std::cout << "Press R for Rock, P for Paper, S for Scissors, or Q to quit: ";
        std::cin >> userInput;
        userInput = std::toupper(userInput); // Convert input to uppercase
        
        if (userInput == 'Q') {
            std::cout << "Exiting the game." << std::endl;
            fileHandler.writeFrequenciesToFile("frequencies.txt",frequencyMap.frequencyMap);
            break;
        } else if (userInput == 'R' || userInput == 'P' || userInput == 'S') {
            // Convert user input to Choice enum and play a round
            Choice userChoice = charToChoice(userInput);
            gameEngine.playRound(userChoice);
        } else {
            std::cerr << "Invalid input. Please try again." << std::endl;
        }

        frequencyMap.updateFrequencyMap(toupper(userInput));
    }
    
    // End the game
    gameEngine.endGame();
    
    // Clean up dynamically allocated memory
    delete computerPlayer;
    
    return 0;
}
