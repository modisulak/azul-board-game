#include "../include/Board.h"

Board::Board() {
    storage = make_unique<Storage>();
    mosaic = make_unique<Mosaic>();
    broken = make_shared<Broken>();
}

Board::Board(const string &storageInput, const string &mosaicInput, const string &brokenInput) {
    storage = make_unique<Storage>(storageInput);
    mosaic = make_unique<Mosaic>(mosaicInput);
    broken = make_shared<Broken>(brokenInput);
}

Board::~Board() = default;

const unique_ptr<Storage> &Board::getStorage() const {
    return storage;
}

const unique_ptr<Mosaic> &Board::getMosaic() const {
    return mosaic;
}

const shared_ptr<Broken> &Board::getBroken() const {
    return broken;
}

string Board::toString() const {
    string boardToString;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        boardToString += std::to_string(row + 1);
        boardToString += ": ";
        for (int col = 0; col != MAX_BOARD_COLS; ++col) {
            boardToString += storage->getTile(row, col);
            boardToString += " ";
        }
        boardToString += "||";
        for (int col = 0; col != MAX_BOARD_COLS; ++col) {
            boardToString += " ";
            boardToString += mosaic->getTile(row, col);
        }
        boardToString += "\n";
    }
    boardToString += "Broken: ";
    boardToString += broken->toString();
    return boardToString;
}

bool Board::validateMove(const Tile tile, const unsigned int row) const {
    bool success = false;

    // Ensure the mosaic doesn't already contain tile colour
    int col = 0;
    while (col != MAX_BOARD_COLS && mosaic->getTile(row, col) != tile) {
        ++col;
    }
    if (col == MAX_BOARD_COLS) {
        int colMin = MAX_BOARD_COLS - (row + 1);

        // Ensure storage row isn't full of tiles
        bool spaceAvailable = storage->getTile(row, colMin) == EMPTY;

        if (spaceAvailable) {
            Tile firstTile = storage->getTile(row, col - 1);
            // Ensure row will accept tile colour
            success = firstTile == tile || firstTile == EMPTY;
        }
    }
    return success;
}

bool Board::addToStorage(const Tile tile, const unsigned int row) {
    bool success = false;
    int col = MAX_BOARD_COLS - 1;
    int colMin = MAX_BOARD_COLS - (row + 1);

    while (col >= colMin && storage->getTile(row, col) != EMPTY) {
        --col;
    }
    if (col >= colMin) {
        storage->setTile(row, col, tile);
        success = true;
    }

    return success;
}

int Board::addToMosaic() {
    int points = 0;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        int colMin = MAX_BOARD_COLS - (row + 1);
        // Ensure storage row is full of tiles
        if (storage->getTile(row, colMin) != EMPTY) {
            Tile tile = storage->getTile(row, colMin);
            Tile location = std::tolower(tile);
            int col = 0;
            // Find location in mosaic for current storage row's colour
            while (col != MAX_BOARD_COLS && mosaic->getTile(row, col) != location) {
                ++col;
            }
            // Update mosaic
            mosaic->setTile(row, col, tile);

            points += mosaic->getPoints(row, col);

            // Reset completed storage row
            storage->clearRow(row);
        }
    }
    // remove lost points for broken tiles
    points -= lostPoints();
    return points;
}

int Board::lostPoints() const {
    int lostPoints = 0;
    for (int i = 0; i != broken->size(); ++i) {
        if (i < 2) { lostPoints += 1; }
        else if (i < 5) { lostPoints += 2; }
        else { lostPoints += 3; }
    }
    return lostPoints;
}


