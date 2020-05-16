#ifndef APT_A2_STORAGE_H
#define APT_A2_STORAGE_H


#include "Grid.h"

class Storage : public Grid{
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
    string toString() override;

    /**
     * Clears a row of the 2D storage array
     * @param row to clear
     */
    void clearRow(int row);

};

#endif //APT_A2_STORAGE_H
