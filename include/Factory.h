#ifndef APT_A2_FACTORY_H
#define APT_A2_FACTORY_H

#include "Utils.h"

class Factory {
public:

    /**
     * Default constructor for 5 factories
     * @param size
     */
    explicit Factory(unsigned int size);

    /**
     * Constructor for pile loaded from file
     * @param size
     * @param tiles
     */
    Factory(unsigned int size, string tiles);

    ~Factory();

    /**
     * Get Tile at Index.
     * @param index
     * @return
     */
    Tile getTile(const unsigned int index) ;

    /**
     * Get number of tiles of the same colour
     * @param tile
     * @return
     */
    int getTilesOfSameColour(const Tile tile) const;

    /**
     * Add a tile to the factory
     * @param tile
     */
    void addTile(const Tile tile);

    /**
     * Remove a tile from the factory by index
     * @param index
     */
    void removeTile(const unsigned int index);

    /**
     * Remove a tile from the factory by tile
     * @param tile
     */
    void removeTile(const Tile tile);

    /**
     * Return the contents of the factory as a string
     * @return
     */
    string toString() const;

    /**
     * Check if the factory is empty
     * @return
     */
    bool isEmpty() const;

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
    bool contains(const Tile tile) const;

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