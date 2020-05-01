#ifndef APT_A2_BOARD_H
#define APT_A2_BOARD_H

#include "LinkedList.h"

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

    /**
     * Getters for each of the member variables
     */
    Tile **getStorage() const;

    Tile **getMosaic() const;

    LinkedList *getBroken() const;

    /**
     * Return a string displaying the storage 2D array
     */
    string storageToString();

    /**
     * Return a string displaying the mosaic 2D array
     */
    string mosaicToString();

    /**
     * Return a string displaying the broken tiles
     */
    string brokenToString();

    /**
     * Return a string displaying the whole board
     */
    string boardToString();

    /**
     * Add tiles from factory to "storage"
     * @param tile
     * @param numberOfTiles
     * @param row
     */
    void addToStorage(Tile tile, int numberOfTiles, int row);

    /**
     * Move tiles to mosaic
     * Returns points earned within round
     */
    int addToMosaic();

    /**
     * Check whether someone has ended the game by completing a row
     */
    bool isGameFinished();

private:
    // 2D array for the tile storage
    Tile **storage;
    // 2D array for the tile mosaic
    Tile **mosaic;
    // Linked List containing the broken tiles
    LinkedList *broken;

    /** 
     * Create an empty new storage array
     * * Create an empty new mosaic array
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
    int lostPoints();

    /**
     * Shift the mosaic string along by 1 element
     * @param mosaicRow
     */
    void shiftMosaic(string &mosaicRow);
};

#endif //APT_A2_BOARD_H