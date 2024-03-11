#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Player.h"
#include "ComputerPlayer.h"
#include <iostream>

class GameEngine {
private:
    Player* humanPlayer;
    ComputerPlayer* computerPlayer;

public:
    GameEngine(Player* human, ComputerPlayer* computer);

    void startGame();
    void playRound(Choice userChoice);
    void endGame();
    void promptPlayerChoice();
    Choice getComputerChoice();
    int determineWinner(Choice userChoice, Choice computerChoice);
    static std::string choiceToString(Choice c);
    static Choice charToChoice(char c);
};

#endif // GAMEENGINE_H
