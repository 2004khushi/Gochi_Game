#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Structure to hold player information
struct Player {
    string name;
    int totalScore; // Player's total score (accumulated across all rounds)
};

// Function to calculate and update the score for a player based on their performance in a round
void updateScore(Player &p, int prediction, int actualSirs) {
    int roundScore = 0;

    if (actualSirs == prediction) {
        roundScore = prediction * 10; // Exact match of prediction
    }
    else if (actualSirs < prediction) {
        roundScore = -(prediction * 10); // Player predicted more than actual
    }
    else {
        roundScore = prediction * 10 + (actualSirs - prediction); // Extra sirs made
    }

    p.totalScore += roundScore; // Add round score to total score
}

// Function to display the final results
void displayResults(const vector<Player>& players) {
    cout << "\nFinal Rankings (Descending Order of Scores):\n";
    int rank = 1;
    for (const auto& player : players) {
        cout << "Rank " << rank++ << ": " << player.name << " with total score: " << player.totalScore << endl;
    }
}

int main() {
    int numPlayers, numRounds;

    // Input number of players
    cout << "Enter the number of players: ";
    cin >> numPlayers;

    // Initialize the players
    vector<Player> players(numPlayers);

    // Input the player names
    for (int i = 0; i < numPlayers; i++) {
        cout << "Enter name for Player " << i + 1 << ": ";
        cin >> players[i].name;
        players[i].totalScore = 0; // Initialize total score to 0 for each player
    }

    // Input the number of rounds to be played
    cout << "Enter the number of rounds to play: ";
    cin >> numRounds;

    // Game phase: Input predicted and actual sirs for each round for each player
    for (int round = 1; round <= numRounds; round++) {
        cout << "\nRound " << round << ":\n";

        // Step 1: Ask all players for their predicted number of sirs for this round
        vector<int> predictions(numPlayers);
        for (int i = 0; i < numPlayers; i++) {
            cout << "Enter predicted number of sirs for " << players[i].name << ": ";
            cin >> predictions[i];
        }

        // Step 2: Ask each player for their actual number of sirs made in this round
        for (int i = 0; i < numPlayers; i++) {
            int actualSirs;
            cout << "Enter actual number of sirs made by " << players[i].name << ": ";
            cin >> actualSirs;
            updateScore(players[i], predictions[i], actualSirs); // Update player's score based on prediction and actual sirs
        }
    }

    // Sort players based on their total scores in descending order
    sort(players.begin(), players.end(), [](const Player &a, const Player &b) {
        return a.totalScore > b.totalScore; // Descending order of total scores
    });

    // Display the final rankings
    displayResults(players);

    return 0;
}
