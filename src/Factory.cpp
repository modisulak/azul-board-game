#include "Factory.h"

Factory::Factory(int size) {
    tiles = make_unique<std::vector<Tile>>(size);
    for (int i = 0; i != size; ++i) {
        tiles->at(i) = BLANK_SPACE;
    }
}

Factory::Factory(int size, string tiles) {
    this->tiles = make_unique<std::vector<Tile>>(size);

    for (int i = 0; i != size; ++i) {
        if (i < tiles.length()) {
            this->tiles->at(i) = tiles[i];
        } else {
            this->tiles->at(i) = BLANK_SPACE;
        }
    }
    sortTiles();
}

Factory::~Factory() = default;

int Factory::getSize() const {
    return tiles->size();
}

Tile Factory::getTile(const int index) {
    Tile tile = BLANK_SPACE;
    if (index < tiles->size()) {
        tile = tiles->at(index);
    }
    return tile;
}

int Factory::getTilesOfSameColour(const Tile tile) {
    int tileCount = 0;
    for (int i = 0; i != tiles->size(); ++i) {
        if (tiles->at(i) == tile) {
            ++tileCount;
        }
    }
    return tileCount;
}

void Factory::addTile(const Tile tile) {
    int i = 0;
    while (i != tiles->size() && tiles->at(i) != BLANK_SPACE) {
        ++i;
    }
    if (i != tiles->size() && tiles->at(i) == BLANK_SPACE) {
        tiles->at(i) = tile;
    }
    sortTiles();
}

void Factory::removeTile(int index) {
    tiles->at(index) = BLANK_SPACE;
}

void Factory::sortTiles() const {
    std::sort(tiles->begin(), tiles->end(), &Utils::totalOrdering);
}

void Factory::removeTile(Tile tile) {
    int i = 0;
    while (i != tiles->size() && tiles->at(i) != tile) {
        ++i;
    }
    if (i != tiles->size()) {
        tiles->at(i) = BLANK_SPACE;
    }
}

string Factory::toString() {
    string out;
    for (int i = 0; i != tiles->size(); ++i) {
        out += tiles->at(i);
    }
    return out;
}

bool Factory::isEmpty() {
    int i = 0;
    while (i != tiles->size() && tiles->at(i) == BLANK_SPACE) {
        ++i;
    }
    return i == tiles->size();
}

bool Factory::contains(Tile tile) {
    int i = 0;
    bool contains = false;
    while (!contains && i != tiles->size()) {
        contains = tiles->at(i) == tile;
        ++i;
    }
    return contains;
}



