#include "Mosaic.h"

Mosaic::Mosaic() {
    string defaultMosaic = DEFAULT_MOSAIC;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        for (int col = 0; col != MAX_BOARD_COLS; ++col) {
            tiles[row][col] = defaultMosaic[col];
        }
        shiftMosaic(defaultMosaic);
    }
};

Mosaic::Mosaic(const std::basic_string<char> &input) : Grid(input) {}

Mosaic::~Mosaic() = default;

void Mosaic::shiftMosaic(string &mosaicRow) {
    if (!mosaicRow.empty()) {
        char temp = mosaicRow.at(mosaicRow.size() - 1);
        for (unsigned int i = mosaicRow.size() - 1; i != 0; --i) {
            mosaicRow.at(i) = mosaicRow.at(i - 1);
        }
        mosaicRow.at(0) = temp;
    }
}

int Mosaic::getPoints(int row, int col) {
    // Start on 1 point for placing a tile
    int points = 1;

    //Check tiles in all 4 directions
    points += getPoints(row + INCREMENT, col, INCREMENT, 0);
    points += getPoints(row + DECREMENT, col, DECREMENT, 0);
    points += getPoints(row, col + INCREMENT, 0, INCREMENT);
    points += getPoints(row, col + DECREMENT, 0, DECREMENT);
    return points;
}

int Mosaic::getPoints(int row, int col, int rowOffset, int colOffset) {
    int points = 0;
    if (row == MAX_BOARD_ROWS || row < 0 || col == MAX_BOARD_COLS || col < 0) {
        points = 0;
    } else if (tiles[row][col] == toupper(tiles[row][col])) {
        points += 1 + getPoints(row + rowOffset, col + colOffset, rowOffset, colOffset);
    }

    return points;
}

bool Mosaic::isAnyRowComplete() const {
    bool complete = false;
    int row = 0;
    while (row != MAX_BOARD_ROWS && !complete) {
        complete = isRowComplete(row);
        ++row;
    }
    return complete;
}

bool Mosaic::isRowComplete(int row) const {
    bool complete = false;
    int col = 0;
    // Check each column of row to ensure it is not Uppercase
    while (col != MAX_BOARD_COLS && isupper(tiles[row][col])) {
        ++col;
    }
    // If every column was uppercase, set finished to true
    if (col == MAX_BOARD_COLS) {
        complete = true;
    }
    return complete;
}

bool Mosaic::isColumnComplete(int col) const {
    bool complete = false;
    int row = 0;
    // Check each row of column to ensure it is Uppercase
    while (row != MAX_BOARD_ROWS && isupper(tiles[row][col])) {
        ++row;
    }
    // If every row was uppercase, set finished to true
    if (row == MAX_BOARD_ROWS) {
        complete = true;
    }
    return complete;
}

int Mosaic::numberOfTilesCompleted() {
    std::array<Tile, 5> array = {'R', 'Y', 'B', 'L', 'U'};
    int completed = 0;

    for (int tile = 0; tile != array.size(); ++tile) {
        int count = 0;
        int row = 0;
        // Check if completed in each row, if count isn't == row continue to the next Tile
        while (row != MAX_BOARD_ROWS && row == count) {
            Tile *position = std::find(std::begin(tiles[row]), std::end(tiles[tiles[row].size()]),
                                       array[tile]);
            if (position != std::end(tiles[row])) {
                ++count;
            }
            ++row;
        }
        completed += count == MAX_BOARD_ROWS;
    }

    return completed;
}
