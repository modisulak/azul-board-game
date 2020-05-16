#include "Storage.h"

Storage::Storage() {
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        clearRow(row);
    }
}

Storage::Storage(const std::basic_string<char> &input) : Grid(input) {}

Storage::~Storage() = default;

void Storage::clearRow(int row) {
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
    // Add new line at the end of each column
    int newLineIndex = MAX_BOARD_COLS;
    // Increment by columns + \n character = 6
    int increment = MAX_BOARD_COLS + 1;
    // Add new lines to all except last row
    int requiredLines = MAX_BOARD_ROWS -1;

    for (int i = 0; i != requiredLines; ++i) {
        toString.insert(newLineIndex, 1, '\n');
        newLineIndex+=increment;
    }

    toString.erase(std::remove(toString.begin(), toString.end(), ' '), toString.end());
    return toString;
}
