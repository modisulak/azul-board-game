#ifndef APT_A2_BOARD_H
#define APT_A2_BOARD_H

#include "LinkedList.h"

#define MAX_BOARD_ROWS     5
#define MAX_BOARD_COLS    11
#define MAX_BOARD_BROKEN   7
#define MAX_MOSAIC_COLS    5
#define MAX_STORAGE_COLS   5

class Board { 
public:
    /**
     * Default constructor, builds a new "blank" board
     */
    Board();

    /**
     * Build's a previous board when loading from a saved game file
     */
    Board(string boardInput, string brokenInput);
    
    ~Board();

    /**
     * Return a string displaying the board array
     */
    string getBoardAsString();

    /**
     * Return a string displaying the broken tiles
     * Tile colours separated by a space
     */
    string getBrokenAsString();

    /**
     * Add tiles from factory to "storage" (LHS of board)
     */
    void addToStorage(Tile colour, int numberOfTiles, int row);

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
    //2D array containing the board
    Tile** board;

    // Linked List containing the broken tiles
    LinkedList *broken = new LinkedList();

    /** 
     * Create an empty new board array
     */
    void newBoard();

    /** 
     * Load a board file into a board array
     */
    void newBoard(string boardInput);

    /** 
     * Initialise the "broken" array with empty spots (spaces)
     * Clears the linked list and then places 7 spaces in the list
     */
    void newBroken();

    /** 
     * Load the saved broken array in from a file
     */
    void newBroken(string brokenInput);

    /** 
     * Add to the broken section
     */
    void addToBroken(Tile brokenTile);

    /** 
     * Return the number of points lost from broken tiles
     */
    int lostPoints();

};

#endif //APT_A2_BOARD_H