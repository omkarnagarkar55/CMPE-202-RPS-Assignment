#ifndef FREQUENCYMAP_H
#define FREQUENCYMAP_H

#include <unordered_map>
#include "Choice.h"

class FrequencyMap {
private:
    const int N = 5; // Lookback window for patterns
    std::string sequence;  // Stores the last N-1 moves
    std::unordered_map<std::string, std::unordered_map<char, int>> frequencyMap; // Frequency of patterns

public:
    void updateFrequencyMap(char move);
    Choice predictNextMove();
};

#endif // FREQUENCYMAP_H
