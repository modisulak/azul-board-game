#ifndef APT_A2_FACTORY_H
#define APT_A2_FACTORY_H

#include "Types.h"

class Factory {
public:

    /**
     * Default constructor for 5 factories
     */
    Factory();

    /**
     * Constructor for discard pile
     */
    Factory(bool isDiscard);

    // Factory(const Factory &other);

    ~Factory();

    /**
     * Get Tile at Index.
     */
    Tile getTile(int index);

    /**
     * Get number of tiles of the same colour
     */
    int getTilesOfSameColour(Tile tile);

    /**
     * Add a tile to the factory
     */
    void addTile(Tile tile);

    /**
     * Return the contents of the factory as a string 
     */
    string toString();

private:

    Tile *tiles;
    bool isDiscard;

};


#endif //APT_A2_FACTORY_H