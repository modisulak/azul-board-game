#ifndef APT_A2_PLAYER_H
#define APT_A2_PLAYER_H

#include "Types.h"
#include "Board.h"

class Player {
public:
    // New player constructor
    Player(string name, int score);

    // Load player constructor
    Player(string name, int score, string storageInput, string mosaicInput, string brokenInput);

    Player(const Player &other);

    ~Player();

    /**
    * Get the player name.
    */
    string getName();

    /**
     * Get the player score.
     */
    int getScore();

    /**
     * Set the player score.
     */
    void setScore(int score);
    
    /**
     * Set the players turn.
     */
    void setPlayerTurn(bool value);

    /**
     * Get the status of the players turn
     */
    bool isPlayersTurn();

private:
    string name;
    int score;
    bool isTurn;
    Board* board;

};

#endif //APT_A2_PLAYER_H