#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#define TILE_COMPLETE_POINTS 10

#define COL_COMPLETE_POINTS 7

#define ROW_COMPLETE_POINTS 2

#include <random>

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
    GameManager(const string &filename);

    ~GameManager();

    /**
     * Manages the playing of the game
     */
    void playGame();

    /**
     * Manages the playing of a round
     */
    void playRound();

    /**
     * Gets the input of the tiles chosen and places them onto the board
     * Factory number, colour, storage row     
     */
    bool playTurn(std::vector<string> &inputs, int playerIndex);

    /**
     * Gives a selection of information to help a user interact with the game
     */
    // TODO
    void help();

    /**
     * Saves the current state of the game
     */
    void saveGame(const string &fileName);

private:
    // engine to randomly swap / assign tiles
    std::default_random_engine engine;

    // Seed number
    int seed;

    // 2D array to store factories factories
    unique_ptr<unique_ptr<Factory>[]> factories;

    // Discard factory
    unique_ptr<Factory> discard;

    // 2 Players
    unique_ptr<unique_ptr<Player>[]> players;

    // Linkedlist representing the bag
    unique_ptr<LinkedList> bag;

    // Linked list representing the box lid
    unique_ptr<LinkedList> boxLid;

    /**
     * Populates a new bag
     */
    void populateBag();

    /**
     * Populates factories
     */
    void populateFactories();

    void setFirstTurn();

    bool isRoundEnd() const;

    string promptPlayer(int index);

    void getPlayerInput(string &input, std::vector<string> &inputs) const;

    bool isANumber(const string &input);

    bool validateInputs(std::vector<string> &inputs, int &factoryNumber);

    void TransferLidToBag();

    bool addTiles(const string& destination, int playerIndex, Tile tile, int noOfTiles);

    void removePlayedTiles(int playerIndex, int factoryNumber, bool isDiscard, Tile tile) const;

    void tileMosaic(shared_ptr<Board> &p1Board, shared_ptr<Board> &p2Board) const;

    void prepareNextRound(const shared_ptr<Board> &p1Board, const shared_ptr<Board> &p2Board);

    void addEndOfGamePoints(const shared_ptr<Board> &p1Board, const shared_ptr<Board> &p2Board);
};

#endif // GAME_MANAGER_H