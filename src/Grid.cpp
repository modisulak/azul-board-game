#include "Grid.h"

Grid::Grid()= default;

Grid::Grid(const std::basic_string<char>& input) {
    int count = 0;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        for (int col = 0; col != MAX_BOARD_COLS; ++col) {
            tiles[row][col] = input[count];
            ++count;
        }
    }
}

Grid::~Grid() = default;

Tile Grid::getTile(const unsigned int row, const unsigned int col) const {
    return tiles[row][col];
}

void Grid::setTile( const unsigned int row, const unsigned int col, Tile tile) {
    Grid::tiles[row][col] = tile;
}

string Grid::toString(){
    string toString;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        for (int col = 0; col != MAX_BOARD_COLS; ++col) {
            toString += tiles[row][col];
        }
    }
    return toString;
}
