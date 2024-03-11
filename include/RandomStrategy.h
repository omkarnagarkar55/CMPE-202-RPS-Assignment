#ifndef RANDOMSTRATEGY_H
#define RANDOMSTRATEGY_H

#include "ComputerPlayer.h"

class RandomStrategy : public ComputerPlayer {
public:
    RandomStrategy();
    Choice makeChoice() override;
};

#endif // RANDOMSTRATEGY_H