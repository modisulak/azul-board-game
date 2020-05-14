#ifndef APT_A2_FACTORY_H
#define APT_A2_FACTORY_H

#include "../include/Types.h"
#include "../include/Utils.h"

class Factory {
public:

    /**
     * Default constructor for 5 factories
     * @param size
     */
    explicit Factory(int size);

    /**
     * Constructor for pile loaded from file
     * @param size
     * @param tiles
     */
    Factory(int size, string tiles);

    ~Factory();

    /**
     * Get Tile at Index.
     * @param index
     * @return
     */
    Tile getTile(int index);

    /**
     * Get number of tiles of the same colour
     * @param tile
     * @return
     */
    int getTilesOfSameColour(Tile tile);

    /**
     * Add a tile to the factory
     * @param tile
     */
    void addTile(Tile tile);

    /**
     * Remove a tile from the factory by index
     * @param index
     */
    void removeTile(int index);

    /**
     * Remove a tile from the factory by tile
     * @param tile
     */
    void removeTile(Tile tile);

    /**
     * Return the contents of the factory as a string
     * @return
     */
    string toString();

    /**
     * Check if the factory is empty
     * @return
     */
    bool isEmpty();

    /**
     * Returns the size of the factory
     * @return
     */
    int getSize() const;

    /**
     * Checks if the factory contains a specific tile
     * @param tile
     * @return
     */
    bool contains(Tile tile);

    /**
     * Sorts the tiles in a Total order of => F R Y B L U
     */
    void sortTiles() const;

private:
    /**
     * Collection of tiles in the factory
     */
    unique_ptr<std::vector<Tile>> tiles;
};


#endif //APT_A2_FACTORY_H