#include "Utils.h"
bool Utils::totalOrdering(Tile x, Tile y) {
    bool precedence;
    if (x == 'F') {
        precedence = true;
    } else if (x == 'R' && y != 'F') {
        precedence = true;
    } else if (x == 'Y' && y != 'F' && y != 'R') {
        precedence = true;
    } else if (x == 'B' && y != 'F' && y != 'R' && y != 'Y') {
        precedence = true;
    } else if (x == 'L' && y != 'F' && y != 'R' && y != 'Y' && y != 'B') {
        precedence = true;
    } else precedence = x == 'U' && y != 'F' && y != 'R' && y != 'Y' && y != 'B' && y != 'L';

    return precedence;
}