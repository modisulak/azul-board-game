#ifndef APT_A2_STORAGE_H
#define APT_A2_STORAGE_H

#include "Grid.h"

class Storage : public Grid
{
public:
    /**
     * Default Constructor
     */
    Storage();
    /**
     * Construct 2D storage array from input string
     * @param input
     */
    explicit Storage(const std::basic_string<char> &input);

    /**
     * Default de-constructor
     */
    ~Storage() override;

    /**
     * @return Overridden String representation of 2D array
     */

    /**
     * Clears a row of the 2D storage array
     * @param row to clear
     */
    void clearRow(int row);

    /**
     * @param row to check if it is complete
     * @return if the row is complete or not
     */
    bool isRowComplete(int row);

    /**
     * @param tile to add to storage
     * @param row  to add the tile in
     * @return if tile was added successfully depending on game rules
     */
    bool add(Tile tile, unsigned int row);
};

#endif //APT_A2_STORAGE_H
