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

Factory::~Factory() = default;

int Factory::getSize() const {
    return size;
}

Tile Factory::getTile(const int index) {
    Tile tile = BLANK_SPACE;
    if (index < size) {
        tile = tiles[index];
    }
    return tile;
}

int Factory::getTilesOfSameColour(const Tile tile) {
    int tileCount = 0;
    for (int i = 0; i != size; ++i) {
        if (tiles[i] == tile) {
            ++tileCount;
            removeTile(i);
        }
    }
    return tileCount;
}

void Factory::addTile(const Tile tile) {
    int i = 0;
    while (i != size && tiles[i] != BLANK_SPACE) {
        ++i;
    }
    if (i != size && tiles[i] == BLANK_SPACE) {
        tiles[i] = tile;
    }
}

void Factory::removeTile(int index) {
    tiles[index] = BLANK_SPACE;
}

void Factory::removeTile(Tile tile) {
    int i = 0;
    while (i != size && tiles[i] != tile) {
        ++i;
    }
    if(i != size)
    tiles[i] = BLANK_SPACE;
}

string Factory::toString() {
    string out;
    for (int i = 0; i != size; i++) {
        out += tiles[i];
    }
    return out;
}

bool Factory::isEmpty() {
    int i = 0;
    while (i < size && tiles[i] == BLANK_SPACE) {
        ++i;
    }
    return i < size && tiles[i] == BLANK_SPACE;
}

bool Factory::contains(Tile tile) {
    int i = 0;
    bool contains = false;
    while (!contains && i != size) {
        contains = tiles[i] == tile;
        ++i;
    }
    return contains;
}

