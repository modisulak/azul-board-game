#include "Factory.h"

Factory::Factory() {
    tiles = new Tile[MAX_FACTORY_TILES];

    for (int i = 0; i < MAX_FACTORY_TILES; ++i) {
        tiles[i] = EMPTY;
    }
}

Factory::Factory(const Factory &other) {
    tiles = new Tile[MAX_FACTORY_TILES];

    for (int i = 0; i < MAX_FACTORY_TILES; ++i) {
        tiles[i] = other.tiles[i];
    }
}

Factory::~Factory() {
    delete[] tiles;
}

Tile Factory::getTile(const int index) {
    return tiles[index];
}

int Factory::getTilesOfSameColour(const Tile tile) {
    int tileCount = 0;
    for (int i = 0; i < MAX_FACTORY_TILES; ++i) {
        if (tiles[i] == tile) {
            ++tileCount;
        }
    }
    return tileCount;
}

void Factory::addTile(const Tile tile) {
    int i = 0;
    while (i != MAX_FACTORY_TILES && tiles[i] == EMPTY) {
        ++i;
    }
    if (tiles[i] == EMPTY) {
        tiles[i] = tile;
    }
}
