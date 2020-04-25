#ifndef APT_A2_FACTORY_H
#define APT_A2_FACTORY_H

#include "Types.h"

class Factory {
public:

    Factory();

    Factory(const Factory &other);

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

private:

    Tile *tiles;

};


#endif //APT_A2_FACTORY_H