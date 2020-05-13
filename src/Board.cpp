#include "../include/Board.h"

Board::Board() {
    storage = new Tile *[MAX_BOARD_ROWS];
    mosaic = new Tile *[MAX_BOARD_ROWS];
    broken = make_shared<std::vector<Tile>>();
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        storage[row] = new Tile[MAX_BOARD_COLS];
        mosaic[row] = new Tile[MAX_BOARD_COLS];
    }
    newBoard();
}

Board::Board(string storageInput, string mosaicInput, string brokenInput) {
    storage = new Tile *[MAX_BOARD_ROWS];
    mosaic = new Tile *[MAX_BOARD_ROWS];
    broken = make_shared<std::vector<Tile>>();
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        storage[row] = new Tile[MAX_BOARD_COLS];
        mosaic[row] = new Tile[MAX_BOARD_COLS];
    }
    // Move strings to avoid unnecessary copies
    newBoard(std::move(storageInput), std::move(mosaicInput));
    newBroken(std::move(brokenInput));
}

Board::~Board() {
    for (int row = 0; row < MAX_BOARD_ROWS; ++row) {
        delete[] storage[row];
        delete[] mosaic[row];
    }
    delete storage;
    delete mosaic;
}

Tile **Board::getStorage() const {
    return storage;
}

Tile **Board::getMosaic() const {
    return mosaic;
}

shared_ptr<std::vector<Tile>> Board::getBroken() const {
    return broken;
}

string Board::storageToString() {
    string storageToString;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        for (int col = 0; col != MAX_BOARD_COLS; ++col) {
            if (storage[row][col] != BLANK_SPACE) {
                storageToString += storage[row][col];
            }
        }
        if (row != MAX_BOARD_ROWS - 1) { storageToString += "\n"; }
    }
    return storageToString;
}

string Board::mosaicToString() {
    string mosaicToString;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        for (int col = 0; col != MAX_BOARD_COLS; ++col) {
            mosaicToString += mosaic[row][col];
        }
    }
    return mosaicToString;
}

string Board::brokenToString() {
    string brokenToString;
    int i = 0;
    while (i != broken->size()) {
        brokenToString += broken->at(i);
        brokenToString += " ";
        ++i;
    }
    return brokenToString;
}

string Board::toString() {
    string boardToString;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        boardToString += std::to_string(row + 1);
        boardToString += ": ";
        for (int col = 0; col != MAX_BOARD_COLS; ++col) {
            boardToString += storage[row][col];
            boardToString += " ";
        }
        boardToString += "||";
        for (int col = 0; col != MAX_BOARD_COLS; ++col) {
            boardToString += " ";
            boardToString += mosaic[row][col];
        }
        boardToString += "\n";
    }
    boardToString += "Broken: ";
    boardToString += brokenToString();
    return boardToString;
}

bool Board::addToStorage(Tile tile, int numberOfTiles, int row) {
    bool success = false;

    // Ensure the mosaic doesn't already contain tile colour
    int col = 0;
    while (col != MAX_BOARD_COLS && mosaic[row][col] != tile) {
        ++col;
    }

    if (col == MAX_BOARD_COLS) {
        int colMin = MAX_BOARD_COLS - (row + 1);
        // Ensure storage row isn't full of tiles
        if (storage[row][colMin] == EMPTY) {
            col = MAX_BOARD_COLS - 1;
            // Ensure storage row is of the same colour (or empty)
            if (storage[row][col] == tile || storage[row][col] == EMPTY) {
                while (col >= colMin && numberOfTiles != 0) {
                    if (storage[row][col] == EMPTY) {
                        storage[row][col] = tile;
                        --numberOfTiles;
                    }
                    --col;
                }
                // Add Any extra tiles to the broken section
                while (numberOfTiles != 0) {
                    addToBroken(tile);
                    --numberOfTiles;
                }
                success = true;
            }
        }
    }
    return success;
}

int Board::addToMosaic() {
    int points = 0;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        int colMin = MAX_BOARD_COLS - (row + 1);
        // Ensure storage row is full of tiles
        if (storage[row][colMin] != EMPTY) {
            Tile tile = storage[row][colMin];
            Tile location = std::tolower(tile);
            int col = 0;
            // Find location in mosiac for current storage row's colour
            while (col != MAX_BOARD_COLS && mosaic[row][col] != location) {
                ++col;
            }
            // Update mosaic
            mosaic[row][col] = tile;
            //TODO Tally up points based on surrounding tiles including lost points for broken tiles

            // Reset completed storage row
            for (int i = colMin; i != MAX_BOARD_COLS; ++i) {
                storage[row][i] = EMPTY;
            }
        }
    }
    return points;
}

void Board::addToBroken(Tile tile) {
    broken->push_back(tile);
    std::sort(broken->begin(), broken->end(), &Utils::totalOrdering);
}

bool Board::isGameFinished() {
    bool finished = false;
    int row = 0;
    while (row != MAX_BOARD_ROWS && !finished) {
        int col = 0;
        // Check each column of row to ensure it is not lowercase
        while (col != MAX_BOARD_COLS && !std::islower(mosaic[row][col])) {
            ++col;
        }
        // If every column was lowercase, set finished to true
        if (col == MAX_BOARD_COLS) {
            finished = true;
        }
        ++row;
    }
    return finished;
}

void Board::newBoard() {
    string defaultMosaic = DEFAULT_MOSAIC;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        int minStorageCol = MAX_BOARD_COLS - row - 1;
        for (int col = 0; col != MAX_BOARD_COLS; ++col) {
            if (col >= minStorageCol) {
                storage[row][col] = EMPTY;
            } else {
                storage[row][col] = BLANK_SPACE;
            }
            mosaic[row][col] = defaultMosaic[col];
        }
        shiftMosaic(defaultMosaic);
    }
}

void Board::shiftMosaic(string &mosaicRow) {
    if (!mosaicRow.empty()) {
        char temp = mosaicRow.at(mosaicRow.size() - 1);
        for (unsigned int i = mosaicRow.size() - 1; i != 0; --i) {
            mosaicRow.at(i) = mosaicRow.at(i - 1);
        }
        mosaicRow.at(0) = temp;
    }
}

void Board::newBoard(string &&storageInput, string &&mosaicInput) {
    int count = 0;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        for (int col = 0; col != MAX_BOARD_COLS; ++col) {
                storage[row][col] = storageInput[count];
                mosaic[row][col] = mosaicInput[count];
                ++count;
        }
    }
}

void Board::newBroken(string brokenInput) {
    for (int i = 0; i != brokenInput.size(); ++i) {
        addToBroken(brokenInput[i]);
    }
}

int Board::lostPoints() {
    int lostPoints = 0;
    int count = 0;
    while (broken->at(count) != BLANK_SPACE) {
        if (count < 2) { lostPoints -= 1; }
        else if (count < 5) { lostPoints -= 2; }
        else { lostPoints -= 3; }
        ++count;
    }
    return lostPoints;
}
