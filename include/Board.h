#ifndef APT_A2_BOARD_H
#define APT_A2_BOARD_H

#include "LinkedList.h"
#include "Utils.h"
#include "Types.h"
#include "Storage.h"
#include "Mosaic.h"
#include "Broken.h"

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
    Board(const string& storageInput, const string& mosaicInput, const string& brokenInput);

    ~Board();

    const unique_ptr<Storage> & getStorage() const;

    const unique_ptr<Mosaic> & getMosaic() const;

    /**
     * Return a string displaying the whole board
     */
    string toString() const;

    /**
     * Validate the entered move is allowed
     * @param tile
     * @param row
     * @return
     */
    bool validateMove(const Tile tile, const unsigned int row) const;


    // TODO add contract
    /**
     * Add tile from factory to "storage"
     * @param tile
     * @param row
     */
    bool addToStorage(const Tile tile, const unsigned int row);

    /**
     * Move tiles to mosaic
     * Returns the number of points earned within a round
     */
    int addToMosaic();

    const shared_ptr<Broken> &getBroken() const;

private:
    // 2D array Class Storage for the tile storage
    unique_ptr<Storage> storage;
    // 2D array Class Mosaic for the tile mosaic
    unique_ptr<Mosaic> mosaic;
    // Vector pointer containing the broken tiles
    shared_ptr<Broken> broken;

    /** 
     * Return the number of points lost from broken tiles
     */
    int lostPoints() const;
};

#endif //APT_A2_BOARD_H