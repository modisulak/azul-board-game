#ifndef APT_A2_MOSAIC_H
#define APT_A2_MOSAIC_H

#include "Grid.h"

#define DEFAULT_MOSAIC     "byrul"

#define INCREMENT 1

#define DECREMENT -1

class Mosaic : public Grid {
public:
    /**
     * Default constructor
     */
    Mosaic();

    /**
     * Construct 2D array for mosaic from input string
     * @param input
     */
    explicit Mosaic(const std::basic_string<char> &input);

    /**
     * Default de-constructor
     */
    ~Mosaic() override;

    /**
     * Check whether someone has ended the game by completing any row
     * @return true if a row is completed
     */
    bool isAnyRowComplete() const;

    /**
     * @param row index to check if row is complete or not
     * @return true for a completed row
     */
    bool isRowComplete(int row) const;

    /**
     * @param row index to check if column is complete or not
     * @return true for a completed column
     */
    bool isColumnComplete(int col) const;

    /**
     * @return Check how many tiles have completed all 5
     */
    int numberOfTilesCompleted();

    /**
     *
     * @param row
     * @param col
     * @return total points scored
     */
    int getPoints(int row, int col);

private:
    /**
     * Shift the mosaic string along by 1 element
     * @param mosaicRow
     */
    void shiftMosaic(string &mosaicRow);

    /**
     * Recursive function to tally points
     * @param row
     * @param col
     * @return points scored for tile placement
     * @param rowOffset offset to increment / decrement the tile to be checked
     * @param colOffset offset to increment / decrement the tile to be checked
     * @return point increase
     */
    int getPoints(int row, int col, int rowOffset, int colOffset);
};


#endif //APT_A2_MOSAIC_H
