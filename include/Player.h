#ifndef APT_A2_PLAYER_H
#define APT_A2_PLAYER_H

#include "Types.h"

class Player {
public:
    Player(string name, int score);

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
     * Get the status of the players turn
     */
    bool isPlayersTurn();

private:
    string name;
    int score;
    bool isTurn;

};

#endif //APT_A2_PLAYER_H