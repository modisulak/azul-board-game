#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#define TILE_COMPLETE_POINTS 10
#define COL_COMPLETE_POINTS 7
#define ROW_COMPLETE_POINTS 2
#define HELP_FILE "resources/help.txt"
#define RULES_FILE "resources/rules.txt"

#include <random>
#include <iomanip>

#include "Player.h"
#include "Factory.h"

class GameManager
{
public:
    /**
     * Creates a new game
     */
    // GameManager(string p1, string p2, int seed);

    // GameManager(string p1s, string p2, string p3, int seed);

    GameManager(string p1, string p2, string p3, string p4, int seed, int numofplayers);

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
    void info(string filename);

    /**
     * Saves the current state of the game
     */
    void saveGame(const string &fileName);

private:
    // engine to randomly swap / assign tiles
    std::default_random_engine engine;

    // Seed number
    int seed;

    int numOfPlayers;

    int maxNumOfFactories;

    // 2D array to store factories factories
    unique_ptr<unique_ptr<Factory>[]> factories;

    // Discard factory
    unique_ptr<Factory> discard;

    // 4 Players
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

    bool addTiles(const string &destination, int playerIndex, Tile tile, unsigned int noOfTiles);

    void removePlayedTiles(int playerIndex, int factoryNumber, bool isDiscard, Tile tile) const;

    void endOfRound(shared_ptr<Board> &p1Board, shared_ptr<Board> &p2Board,
                    shared_ptr<Board> &p3Board, shared_ptr<Board> &p4Board) const;

    void prepareNextRound(const shared_ptr<Board> &p1Board, const shared_ptr<Board> &p2Board,
                          const shared_ptr<Board> &p3Board, const shared_ptr<Board> &p4Board);

    void addEndOfGamePoints(const shared_ptr<Board> &p1Board, const shared_ptr<Board> &p2Board,
                            const shared_ptr<Board> &p3Board, const shared_ptr<Board> &p4Board);

    void getWinner(const shared_ptr<Board> &p1Board, const shared_ptr<Board> &p2Board,
                   const shared_ptr<Board> &p3Board, const shared_ptr<Board> &p4Board, string &winner) const;

    void waitForEnter() const;

    int tileMosaic(const shared_ptr<Board> &board, int row) const;

    bool processBroken(const shared_ptr<Board> &board) const;
};

#endif // GAME_MANAGER_H