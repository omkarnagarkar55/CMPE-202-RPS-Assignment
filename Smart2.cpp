#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream> // For file handling
#include <sstream> // For string stream
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

enum Choice
{
    ROCK,
    PAPER,
    SCISSORS
};

string choiceToString(Choice c)
{
    switch (c)
    {
    case ROCK:
        return "Rock";
    case PAPER:
        return "Paper";
    case SCISSORS:
        return "Scissors";
    default:
        return "Unknown";
    }
}

Choice charToChoice(char c)
{
    switch (c)
    {
    case 'R':
        return ROCK;
    case 'P':
        return PAPER;
    case 'S':
        return SCISSORS;
    default:
        return ROCK; // Safe default
    }
}

Choice winningChoiceAgainst(Choice c)
{
    switch (c)
    {
    case ROCK:
        return PAPER;
    case PAPER:
        return SCISSORS;
    case SCISSORS:
        return ROCK;
    default:
        return ROCK; // Safe default
    }
}

const int N = 5; // Lookback window for patterns
string sequence;  // Stores the last N-1 moves
unordered_map<string, unordered_map<char, int>> frequencyMap; // Frequency of patterns

// Predicts the next move based on the pattern
Choice predictNextMove()
{
    if (sequence.length() < N - 1)
    {
        // Not enough data for prediction
        return static_cast<Choice>(rand() % 3);
    }

    string recentPattern = sequence.substr(sequence.length() - (N - 1));
    if (frequencyMap.find(recentPattern) == frequencyMap.end())
    {
        // Pattern not found
        return static_cast<Choice>(rand() % 3);
    }

    char mostLikelyMove;
    int maxFrequency = -1;
    for (auto &moveFreq : frequencyMap[recentPattern])
    {
        if (moveFreq.second > maxFrequency)
        {
            maxFrequency = moveFreq.second;
            mostLikelyMove = moveFreq.first;
        }
    }

    return charToChoice(mostLikelyMove);
}

// Updates the frequency map with the latest move
void updateFrequencyMap(char move)
{
    if (sequence.length() == N - 1)
    {
        frequencyMap[sequence][move]++;
    }
    sequence += move;
    if (sequence.length() > N - 1)
    {
        sequence.erase(sequence.begin());
    }
}

// Determine the winner of each round
int determineWinner(Choice userChoice, Choice computerChoice)
{
    if (userChoice == computerChoice)
    {
        return 0; // Draw
    }
    else if ((userChoice == ROCK && computerChoice == SCISSORS) ||
             (userChoice == PAPER && computerChoice == ROCK) ||
             (userChoice == SCISSORS && computerChoice == PAPER))
    {
        return 1; // User wins
    }
    else
    {
        return -1; // Computer wins
    }
}

// Write frequencies to a file
void writeFrequenciesToFile(const string &filename)
{
    ofstream file(filename);
    if (file.is_open())
    {
        for (const auto &entry : frequencyMap)
        {
            file << entry.first << ": ";
            for (const auto &moveFreq : entry.second)
            {
                file << moveFreq.first << ":" << moveFreq.second << ",";
            }
            file << endl;
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open file: " << filename << endl;
    }
}

// Read frequencies from a file
void readFrequenciesFromFile(const string &filename)
{
    frequencyMap.clear(); // Clear the existing frequency map

    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            istringstream iss(line); // String stream to parse each line
            string pattern;
            getline(iss, pattern, ':');

            unordered_map<char, int> moves;
            string moveFreqPair;
            while (getline(iss, moveFreqPair, ','))
            {
                char move;
                int freq;
                stringstream ss(moveFreqPair);
                ss >> move;
                ss.ignore();
                ss >> freq;
                moves[move] = freq;
            }
            frequencyMap[pattern] = moves;
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open file: " << filename << endl;
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr))); // Seed for random number generation

    // Read frequencies from file at the start of each game
    readFrequenciesFromFile("frequencies.txt");

    cout << "Rock, Paper, Scissors Game against the Computer!\n";
    cout << "Enter R for Rock, P for Paper, S for Scissors, Q to quit:\n";

    char userMove;
    while (true)
    {
        cout << "> ";
        cin >> userMove;
        if (toupper(userMove) == 'Q')
        {
            // Write frequencies to file at the end of each game
            writeFrequenciesToFile("frequencies.txt");
            break; // Quit the game
        }

        Choice userChoice = charToChoice(toupper(userMove));
        Choice predictedMove = predictNextMove();
        Choice computerChoice = winningChoiceAgainst(predictedMove); // Computer plays to win against the predicted move

        cout << "You chose " << choiceToString(userChoice) << ".\n";
        cout << "Computer chose " << choiceToString(computerChoice) << ".\n";

        // Update pattern recognition
        updateFrequencyMap(toupper(userMove));

        // Determine the winner and display the result
        int winner = determineWinner(userChoice, computerChoice);
        if (winner == 0)
        {
            cout << "It's a draw!\n";
        }
        else if (winner == 1)
        {
            cout << "You win!\n";
        }
        else
        {
            cout << "Computer wins!\n";
        }
    }

    return 0;
}
