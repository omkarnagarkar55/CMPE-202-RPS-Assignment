#include "../include/SmartStrategy.h"
#include "../include/FrequencyMap.h"

Choice SmartStrategy::makeChoice() {
    FrequencyMap map;
    Choice choice = map.predictNextMove();
    //return Choice::ROCK;
    return choice;
}