#include "Factory.h"

Factory::Factory(int size) :
        size(size) {
    tiles = make_unique<Tile[]>(size);
    for (int i = 0; i != size; ++i) {
        tiles[i] = BLANK_SPACE;
    }
}

Factory::Factory(int size, string tiles) :
        size(size) {
    this->tiles = make_unique<Tile[]>(size);

    for (int i = 0; i != size; ++i) {
        if (size < tiles.length()) {
            this->tiles[i] = tiles[i];
            ++i;
        } else {
            tiles[i] = BLANK_SPACE;
        }
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
}

Tile Factory::getTile(const int index) {
    return tiles[index];
}

int Factory::getTilesOfSameColour(const Tile tile) {
    int tileCount = 0;
    for (int i = 0; i != size; ++i) {
        if (tiles[i] == tile) {
            ++tileCount;
        }
    }
    return tileCount;
}

void Factory::addTile(const Tile tile) {
    int i = 0;
    while (i != size && tiles[i] != BLANK_SPACE) {
        if (tiles[i] == BLANK_SPACE) {
            tiles[i] = tile;
        }
        ++i;
    }
}

string Factory::toString() {
    string out = "";
    for (int i = 0; i != size; i++) {
        out += tiles[i];
    }
    return out;
}

