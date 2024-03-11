#ifndef PLAYER_H
#define PLAYER_H

#include "Choice.h"

class Player {
public:
    virtual Choice makeChoice() = 0;
};

#endif // PLAYER_H
