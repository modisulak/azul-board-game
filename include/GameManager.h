#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <Types.h>

#include "Types.h"
#include "Board.h"
#include "Player.h"
#include "Factory.h"

class GameManager {
public:
    /**
     * Creates a new game
     */
    GameManager(string p1, string p2, int seed);

    /**
     * Loads a game from a save file with given name
     */
    GameManager(string fileName);

    ~GameManager();

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

    /**
     * Saves the current state of the game
     */
    void saveGame(string fileName);

private:
    // Seed number
    int seed;

    // 2D array to store factories factories
    Factory **factories;

    // Discard factory
    Factory* discard;

    // 2 Players
    Player **players;

    // Vector representing the bag
    std::vector<Tile>* bag;

    // Linked list representing the box lid
    LinkedList *boxLid;

    /**
     * Populates a new bag
     */
    void populateBag();

    /**
     * Populates factories
     */
    void populateFactories();

    /**
     * Returns the bag as a string for saving
     */
    string bagToString();

};

#endif // GAME_MANAGER_H