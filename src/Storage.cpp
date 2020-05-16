#include "Storage.h"

Storage::Storage() {
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        clearRow(row);
    }
}

Storage::Storage(const std::basic_string<char> &input) : Grid(input) {}

Storage::~Storage() = default;

void Storage::clearRow(int row){
    int minStorageCol = MAX_BOARD_COLS - row - 1;
    for (int col = 0; col != MAX_BOARD_COLS; ++col) {
        if (col >= minStorageCol) {
            tiles[row][col] = EMPTY;
        } else {
            tiles[row][col] = BLANK_SPACE;
        }
    }
}

string Storage::toString() {
    string toString = Grid::toString();

    for (int i = 0; i != toString.size(); ++i) {
        if(i+1 % MAX_BOARD_COLS && i != toString.size()){
            toString.replace(i, 1, "\n");
        }
    }
    toString.erase(std::remove(toString.begin(), toString.end(), ' '), toString.end());
    return toString;
}
