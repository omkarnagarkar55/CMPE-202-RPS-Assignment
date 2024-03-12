#include <iostream>
#include <vector>
#include <random>
#include <memory> // For std::unique_ptr

// Enum for possible moves
enum class Move { ROCK, PAPER, SCISSORS };

// Strategy Interface
class Strategy {
public:
    virtual Move makeMove() = 0;
    virtual ~Strategy() {}
};

// Random Strategy
class RandomStrategy : public Strategy {
public:
    Move makeMove() override {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 2);
        return static_cast<Move>(dis(gen));
    }
};

// Smart Strategy (Simplified)
class SmartStrategy : public Strategy {
    // Example: Always choose paper for simplicity
public:
    Move makeMove() override {
        return Move::PAPER; // Simplified strategy for demonstration
    }
};

// Player Interface
class Player {
public:
    virtual Move getMove() = 0;
    virtual ~Player() {}
};

// Human Player
class HumanPlayer : public Player {
public:
    Move getMove() override {
        char choice;
        std::cout << "Choose (R)ock, (P)aper, or (S)cissors: ";
        std::cin >> choice;

        switch (choice) {
            case 'R':
            case 'r':
                return Move::ROCK;
            case 'P':
            case 'p':
                return Move::PAPER;
            case 'S':
            case 's':
                return Move::SCISSORS;
            default:
                std::cout << "Invalid choice. Defaulting to Rock.\n";
                return Move::ROCK;
        }
    }
};

// Computer Player
class ComputerPlayer : public Player {
    std::unique_ptr<Strategy> strategy;

public:
    ComputerPlayer(std::unique_ptr<Strategy> strategy) : strategy(std::move(strategy)) {}

    Move getMove() override {
        return strategy->makeMove();
    }
};

// Game Class
class Game {
    HumanPlayer human;
    ComputerPlayer computer;
    int scoreHuman = 0;
    int scoreComputer = 0;

    void determineWinner(Move humanMove, Move computerMove) {
        if (humanMove == computerMove) {
            std::cout << "It's a draw.\n";
        } else if ((humanMove == Move::ROCK && computerMove == Move::SCISSORS) ||
                   (humanMove == Move::PAPER && computerMove == Move::ROCK) ||
                   (humanMove == Move::SCISSORS && computerMove == Move::PAPER)) {
            std::cout << "Human wins this round.\n";
            scoreHuman++;
        } else {
            std::cout << "Computer wins this round.\n";
            scoreComputer++;
        }
    }

public:
    Game(std::unique_ptr<Strategy> strat) : computer(std::move(strat)) {}

    void play() {
        for (int round = 1; round <= 20; ++round) {
            std::cout << "\nRound " << round << std::endl;
            Move humanMove = human.getMove();
            Move computerMove = computer.getMove();
            determineWinner(humanMove, computerMove);
        }

        std::cout << "\nFinal Score:\nHuman: " << scoreHuman << "\nComputer: " << scoreComputer << std::endl;
    }
};

int main() {
    std::cout << "Choose strategy for computer:\n1. Random\n2. Smart\nEnter choice: ";
    int choice;
    std::cin >> choice;

    std::unique_ptr<Strategy> strategy;
    if (choice == 1) {
        strategy = std::make_unique<RandomStrategy>();
    } else {
        strategy = std::make_unique<SmartStrategy>();
    }

    Game game(std::move(strategy));
    game.play();

    return 0;
}
