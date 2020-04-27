#include "../include/Board.h"

Board::Board() {
    storage = new Tile *[MAX_BOARD_ROWS];
    mosaic = new Tile *[MAX_BOARD_ROWS];
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        storage[row] = new Tile[MAX_BOARD_COLS];
        mosaic[row] = new Tile[MAX_BOARD_COLS];
    }
    newBoard();
    newBroken();
}

Board::Board(string storageInput, string mosaicInput, string brokenInput) {
    storage = new Tile *[MAX_BOARD_ROWS];
    mosaic = new Tile *[MAX_BOARD_ROWS];
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        storage[row] = new Tile[MAX_BOARD_COLS];
        mosaic[row] = new Tile[MAX_BOARD_COLS];
    }
    newBoard(storageInput, mosaicInput);
    newBroken(brokenInput);
}

Board::~Board() {
    for (int row = 0; row < MAX_BOARD_ROWS; ++row) {
        delete[] storage[row];
        delete[] mosaic[row];
    }
    delete storage;
    delete mosaic;
    delete broken;
}

string Board::storageToString() {
    string storageToString;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        for (int col = 0; col != MAX_BOARD_COLS; ++col) {
            storageToString += storage[row][col];
        }
    }
    return storageToString;
}

string Board::mosaicToString() {
    string mosaicToString;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        for (int col = 0; col != MAX_BOARD_COLS; ++col) {
            mosaicToString += storage[row][col];
        }
    }
    return mosaicToString;
}

string Board::brokenToString() {
    string brokenToString;
    int count = 0;
    while (broken->get(count) != EMPTY) {
        brokenToString += broken->get(count);
        ++count;
    }
    return brokenToString;
}

//TODO this needs to take into account partially filled rows
//void Board::addToStorage(Tile tile, int numberOfTiles, int row) {
//    int brokenTiles = numberOfTiles - (row + 1);
//    if (brokenTiles != 0) {
//        for (int i = 0; i != brokenTiles; i++) {
//            broken->addBack(tile);
//            --numberOfTiles;
//        }
//    }
//    for (int col = MAX_BOARD_COLS; col >= row + MAX_BOARD_COLS; --col) {
//        storage[row][col] = tile;
//    }
//}

int Board::addToMosaic() {
    int points = 0;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        int col = 0;
        int count = 0;
        while (col != MAX_BOARD_COLS) {
            if (storage[row][col] != EMPTY) {
                ++count;
            }
            ++col;
        }
        if (count == row + 1) {
            Tile tile = storage[row][col];
            Tile location = std::tolower(tile);
            col = 0;
            while (col != MAX_BOARD_COLS && mosaic[row][col] != location) {
                ++col;
            }
            if (mosaic[row][col] == location) {
                mosaic[row][col] = tile;
                //TODO Tally up points based on surrounding tiles
            }
        }
    }
    return points;
}

bool Board::isGameFinished() {
    bool finished = false;
    int row = 0;
    while (row != MAX_BOARD_ROWS && !finished) {
        int col = 0;
        Tile tile = mosaic[row][col];
        while (tile != std::tolower(tile) && col != MAX_BOARD_COLS) {
            ++col;
        }
        if (col == MAX_BOARD_COLS) {
            finished = true;
        }
        ++row;
    }
    return finished;
}

void Board::newBoard() {
    string defaultMosaic = DEFAULT_MOSAIC;
    int row = 0;
    while (row != MAX_BOARD_ROWS) {
        for (int col = 0; col != MAX_BOARD_COLS; ++col) {
            this->storage[row][col] = defaultMosaic[col];
        }
        shiftMosaic(defaultMosaic);
        ++row;
    }
}

void Board::shiftMosaic(string &mosaicRow) {
    if (!mosaicRow.empty()) {
        char temp = mosaicRow[mosaicRow.size() - 1];
        for (int i = mosaicRow.size() - 1; i != 0; --i) {
            mosaicRow[i] = mosaicRow[i - 1];
        }
        mosaicRow[0] = temp;
    }
}

void Board::newBoard(string boardInput, string mosaicInput) {
    int count = 0;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        for (int col = 0; col != MAX_BOARD_COLS; ++col) {
            storage[row][col] = boardInput[count];
            mosaic[row][col] = mosaicInput[count];
            ++count;
        }
    }
}

void Board::newBroken() {
    broken->clear();
    for (int i = 0; i != MAX_BOARD_BROKEN; i++) {
        broken->addBack(EMPTY);
    }
}

void Board::newBroken(string brokenInput) {
    for (int i = 0; i != MAX_BOARD_BROKEN; ++i) {
        if (i < brokenInput.size()) {
            broken->addBack(brokenInput[i]);
        } else {
            broken->addBack(EMPTY);
        }
    }
}

void Board::addToBroken(Tile brokenTile) {
    broken->addBack(brokenTile);
}

int Board::lostPoints() {
    int lostPoints = 0;
    int count = 0;
    while (broken->get(count) != EMPTY) {
        if (count < 2) { lostPoints -= 1; }
        else if (count < 5) { lostPoints -= 2; }
        else { lostPoints -= 3; }
        ++count;
    }
    return lostPoints;
}




