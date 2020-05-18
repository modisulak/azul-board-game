#ifndef APT_A2_GRID_H
#define APT_A2_GRID_H

#include "Types.h"

class Grid
{
public:
    /**
     * Default Constructor
     */
    Grid();

    /**
     * Construct 2D array from input string
     * @param input
     */
    explicit Grid(const std::basic_string<char> &input);

    /**
     * Default de-constructor
     */
    virtual ~Grid();

    /**
     * @param row
     * @param col
     * @return Tile at specific co-ordinates
     */
    Tile getTile(unsigned int row, unsigned int col) const;

    /**
     * @param row
     * @param col
     * @param tile to set at specific co-ordinates
     */
    void setTile(unsigned int row, unsigned int col, Tile tile);

    /**
     * @return String representation of 2D array
     */
    virtual string toString();

protected:
    /**
     * 5 x 5 2D array of tiles
     */
    std::array<std::array<Tile, MAX_BOARD_ROWS>, MAX_BOARD_COLS> tiles{};
};

#endif //APT_A2_GRID_H
