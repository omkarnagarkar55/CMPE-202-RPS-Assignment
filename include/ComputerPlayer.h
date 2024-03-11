#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Player.h"

class ComputerPlayer : public Player {
public:
    virtual Choice makeChoice() = 0;
};

#endif // COMPUTERPLAYER_H
