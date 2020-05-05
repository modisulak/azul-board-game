#include "Factory.h"

Factory::Factory() : 
    isDiscard(false)
{
    tiles = new Tile[MAX_FACTORY_TILES];
    for (int i = 0; i != MAX_FACTORY_TILES; ++i) {
        tiles[i] = BLANK_SPACE;
    }
}

Factory::Factory(bool isDiscard) : 
    isDiscard(isDiscard)
{
    tiles = new Tile[MAX_DISCARD_TILES];
    for (int i = 0; i != MAX_DISCARD_TILES; ++i) {
        tiles[i] = BLANK_SPACE;
    }
}

/*
Factory::Factory(const Factory &other) {
    tiles = new Tile[MAX_FACTORY_TILES];

    for (int i = 0; i != MAX_FACTORY_TILES; ++i) {
        tiles[i] = other.tiles[i];
    }
}*/

Factory::~Factory() {
    delete[] tiles;
}

Tile Factory::getTile(const int index) {
    return tiles[index];
}

int Factory::getTilesOfSameColour(const Tile tile) {
    int tileCount = 0;
    if (isDiscard) {
        for (int i = 0; i != MAX_DISCARD_TILES; ++i) {
            if (tiles[i] == tile) {
            ++tileCount;
            }
        }
    } else {
        for (int i = 0; i != MAX_FACTORY_TILES; ++i) {
            if (tiles[i] == tile) {
            ++tileCount;
            }
        }   
    }
    return tileCount;
}

void Factory::addTile(const Tile tile) {
    int i = 0;
    if (isDiscard) {
        while (i != MAX_DISCARD_TILES && tiles[i] != BLANK_SPACE) {
            if (tiles[i] == BLANK_SPACE) {
                tiles[i] = tile;
            }
            ++i;
        }
    } else {
        while (i != MAX_FACTORY_TILES && tiles[i] != BLANK_SPACE) {
            if (tiles[i] == BLANK_SPACE) {
                tiles[i] = tile;
            }
            ++i;
        }
    }
}

string Factory::toString() {
    string out = "";
    
    if (isDiscard) {
        for (int i = 0; i != MAX_DISCARD_TILES; i++) {
            out = out + tiles[i];
        }
    } else {
        for (int i = 0; i != MAX_FACTORY_TILES; i++) {
            out = out + tiles[i];
        }
    }

    return out;
}
