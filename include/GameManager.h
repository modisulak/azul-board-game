#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Types.h"
#include "Board.h"
#include "Player.h"

class GameManager {
public:
    GameManager();

    ~GameManager();

    /**
     * Loads a game from the name of the save file given
     */
    bool loadGame(string fileName);

    /**
     * Begins a new game from scratch
     */
    void newGame();

    /**
     * Manages the playing of a round
     */
    void playRound();

    /**
     * Gets the input of the tiles chosen and places them onto the board
     * Factory number, colour, storage row     
     */
    void playTurn(int factoryNo, Tile colour, int storageRow);

    /**
     * Returns the player's score
     */
    int getScore();

    /**
     * Gives a selection of information to help a user interact with the game
     */
    void help();

private:


};

#endif // GAME_MANAGER_H