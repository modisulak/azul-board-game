#include "Broken.h"

Broken::Broken() = default;

Broken::Broken(std::basic_string<char> input) {
    for (int i = 0; i != input.size(); ++i) {
        add(input[i]);
    }
}

Broken::~Broken() = default;

std::vector<Tile> Broken::getTiles() const {
    return tiles;
}

int Broken::size() const {
    return tiles.size();
}


bool Broken::add(const Tile tile) {
    bool added = false;
    if (tiles.size() < MAX_BROKEN_TILES) {
        tiles.push_back(tile);
        added = true;
    }
    return added;
}

Tile Broken::at(int index) {
    return tiles.at(index);
}

string Broken::toString() const {
    string toString;
    int i = 0;
    while (i != tiles.size()) {
        toString += tiles.at(i);
        toString += " ";
        ++i;
    }
    return toString;
}

void Broken::clear() {
    tiles.clear();
}
