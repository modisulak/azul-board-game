#include "Utils.h"

bool Utils::totalOrdering(Tile x, Tile y) {
    std::vector<Tile> tiles = {FIRST_PLAYER_TILE, 'R', 'Y', 'B', 'L', 'U', BLANK_SPACE};

    unsigned int xPos = 0;
    while (xPos != tiles.size() && x != tiles[xPos]) {
        ++xPos;
    }
    unsigned int yPos = 0;
    while (yPos != tiles.size() && y != tiles[yPos]) {
        ++yPos;
    }

    return xPos < yPos;
}