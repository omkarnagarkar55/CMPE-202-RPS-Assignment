#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
public:
    Choice makeChoice() override;
};

#endif // HUMANPLAYER_H