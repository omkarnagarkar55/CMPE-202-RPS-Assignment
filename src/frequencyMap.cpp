#include "../include/FrequencyMap.h"
#include <cstdlib>
#include <string>

void FrequencyMap::updateFrequencyMap(char move) {
    if (sequence.length() == N - 1) {
        frequencyMap[sequence][move]++;
    }
    sequence += move;
    if (sequence.length() > N - 1) {
        sequence.erase(sequence.begin());
    }
}

Choice FrequencyMap::predictNextMove() {
    if (sequence.length() < N - 1) {
        // Not enough data for prediction
        return static_cast<Choice>(rand() % 3);
    }

    string recentPattern = sequence.substr(sequence.length() - (N - 1));
    if (frequencyMap.find(recentPattern) == frequencyMap.end()) {
        // Pattern not found
        return static_cast<Choice>(rand() % 3);
    }

    char mostLikelyMove;
    int maxFrequency = -1;
    for (auto &moveFreq : frequencyMap[recentPattern]) {
        if (moveFreq.second > maxFrequency) {
            maxFrequency = moveFreq.second;
            mostLikelyMove = moveFreq.first;
        }
    }

    return charToChoice(mostLikelyMove);
}
