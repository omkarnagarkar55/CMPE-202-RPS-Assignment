#include "../include/SmartStrategy.h"
#include "../include/ChoiceUtils.h"

SmartStrategy::SmartStrategy(FrequencyMap* frequencyMap): frequencyMap(frequencyMap){}

Choice SmartStrategy::makeChoice() {
    Choice choice = frequencyMap->predictNextMove();
    //return winningChoiceAgainst(choice);

    switch (choice) {
    case ROCK:
        return PAPER;
    case PAPER:
        return SCISSORS;
    case SCISSORS:
        return ROCK;
    default:
        return ROCK; // Default to ROCK
    }

}