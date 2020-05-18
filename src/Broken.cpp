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

bool Broken::add(const Tile tile) {
    bool added = false;
    if (tiles.size() < MAX_BROKEN_TILES) {
        tiles.push_back(tile);
        added = true;
    }
    return added;
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

int Broken::lostPoints() const {
    int lostPoints = 0;
    for (int i = 0; i != tiles.size(); ++i) {
        if (i < 2) { lostPoints += 1; }
        else if (i < 5) { lostPoints += 2; }
        else { lostPoints += 3; }
    }
    return lostPoints;
}

void Broken::clear() {
    tiles.clear();
}
