#include "Factory.h"

Factory::Factory(unsigned int size) {
    tiles = make_unique<std::vector<Tile>>(size);
    for (unsigned int i = 0; i != size; ++i) {
        tiles->at(i) = BLANK_SPACE;
    }
}

Factory::Factory(unsigned int size, string tiles) {
    this->tiles = make_unique<std::vector<Tile>>(size);

    for (unsigned int i = 0; i != size; ++i) {
        if (i < tiles.length()) {
            this->tiles->at(i) = tiles[i];
        } else {
            this->tiles->at(i) = BLANK_SPACE;
        }
    }
    sortTiles();
}

Factory::~Factory() = default;

unsigned int Factory::getSize() const {
    return tiles->size();
}

Tile Factory::getTile(const unsigned int index) {
    Tile tile = BLANK_SPACE;
    if (index < tiles->size()) {
        tile = tiles->at(index);
    }
    return tile;
}

unsigned int Factory::getTilesOfSameColour(const Tile tile) const {
    int tileCount = 0;
    for (unsigned int i = 0; i != tiles->size(); ++i) {
        if (tiles->at(i) == tile) {
            ++tileCount;
        }
    }
    return tileCount;
}

void Factory::addTile(const Tile tile) {
    unsigned int i = 0;
    while (i != tiles->size() && tiles->at(i) != BLANK_SPACE) {
        ++i;
    }
    if (i != tiles->size() && tiles->at(i) == BLANK_SPACE) {
        tiles->at(i) = tile;
    }
    sortTiles();
}

void Factory::removeTile(const unsigned int index) {
    tiles->at(index) = BLANK_SPACE;
}

void Factory::sortTiles() const {
    std::sort(tiles->begin(), tiles->end(), &Utils::totalOrdering);
}

void Factory::removeTile(const Tile tile) {
    unsigned int i = 0;
    while (i != tiles->size() && tiles->at(i) != tile) {
        ++i;
    }
    if (i != tiles->size()) {
        tiles->at(i) = BLANK_SPACE;
    }
}

string Factory::toString() const {
    string out;
    for (unsigned int i = 0; i != tiles->size(); ++i) {
        out += tiles->at(i);
    }
    return out;
}

bool Factory::isEmpty() const {
    unsigned int i = 0;
    while (i != tiles->size() && tiles->at(i) == BLANK_SPACE) {
        ++i;
    }
    return i == tiles->size();
}

bool Factory::contains(const Tile tile) const {
    unsigned int i = 0;
    bool contains = false;
    while (!contains && i != tiles->size()) {
        contains = tiles->at(i) == tile;
        ++i;
    }
    return contains;
}



