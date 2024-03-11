#ifndef SMARTSTRATEGY_H
#define SMARTSTRATEGY_H

#include "ComputerPlayer.h"

class SmartStrategy : public ComputerPlayer {
public:
    Choice makeChoice() override;
};

#endif // SMARTSTRATEGY_H
