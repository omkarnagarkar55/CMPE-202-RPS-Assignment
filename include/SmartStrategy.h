#ifndef SMARTSTRATEGY_H
#define SMARTSTRATEGY_H

#include "Strategy.h"

class SmartStrategy : public Strategy {
public:
    Choice makeChoice() override;
};

#endif // SMARTSTRATEGY_H
