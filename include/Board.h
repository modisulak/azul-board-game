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

    /**
     * @return pointer to storage
     */
    const unique_ptr<Storage> & getStorage() const;

    /**
     * @return pointer to mosaic
     */
    const unique_ptr<Mosaic> & getMosaic() const;
    /**
     * @return pointer to broken
     */
    const shared_ptr<Broken> &getBroken() const;

    /**
     * @return a string displaying the whole board
     */
    string toString() const;

    /**
     * @param tile to check if is valid
     * @param row to check if tile can be placed there
     * @return if move is valid or not
     */
    bool validateMove(const Tile tile, const unsigned int row) const;


private:
    // 2D array Class Storage for the tile storage
    unique_ptr<Storage> storage;
    // 2D array Class Mosaic for the tile mosaic
    unique_ptr<Mosaic> mosaic;
    // Vector pointer containing the broken tiles
    shared_ptr<Broken> broken;

};

#endif //APT_A2_BOARD_H