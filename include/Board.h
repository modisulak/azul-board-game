#ifndef APT_A2_BOARD_H
#define APT_A2_BOARD_H

#include "LinkedList.h"
#include "Utils.h"

#define MAX_BOARD_ROWS     5
#define MAX_BOARD_COLS     5
#define DEFAULT_MOSAIC     "byrul"

class Board {
public:
    /**
     * Default constructor, builds a new "blank" storage
     */
    Board();

    /**
     * Build's a previous storage when loading from a saved game file
     * @param storageInput 
     * @param mosaicInput
     * @param brokenInput
     */
    Board(string storageInput, string mosaicInput, string brokenInput);

    ~Board();

    shared_ptr<std::vector<Tile>> getBroken() const;

    /**
     * Return a string displaying the storage 2D array
     */
    string storageToString() const;

    /**
     * Return a string displaying the mosaic 2D array
     */
    string mosaicToString() const;

    /**
     * Return a string displaying the broken tiles
     */
    string brokenToString() const;

    /**
     * Return a string displaying the whole board
     */
    string toString() const;

    /**
     * Add tiles from factory to "storage"
     * @param tile
     * @param numberOfTiles
     * @param row
     */
    bool addToStorage(const Tile tile, const unsigned int numberOfTiles, const unsigned int row);

    /**
     * Move tiles to mosaic
     * Returns the number of points earned within a round
     */
    int addToMosaic();

    /**
     * Add a tile to the broken list
     * @param tile
     */
    void addToBroken(const Tile tile);

    /**
     * Check whether someone has ended the game by completing a row
     */
    bool isGameFinished() const;

private:
    // 2D array for the tile storage
    Tile **storage;
    // 2D array for the tile mosaic
    Tile **mosaic;
    // Vector containing the broken tiles
    shared_ptr<std::vector<Tile>> broken;

    /** 
     * Create an empty new storage array
     * Create an empty new mosaic array
     */
    void newBoard();

    /**
     * Load a storage file into a storage array
     * @param boardInput
     * @param mosaicInput
     */
    void newBoard(string&& boardInput, string&& mosaicInput);

    /** 
     * Load the saved broken array in from a file
     * * @param brokenInput
     */
    void newBroken(string brokenInput);

    /** 
     * Return the number of points lost from broken tiles
     */
    int lostPoints() const;

    /**
     * Shift the mosaic string along by 1 element
     * @param mosaicRow
     */
    void shiftMosaic(string &mosaicRow);
};

#endif //APT_A2_BOARD_H