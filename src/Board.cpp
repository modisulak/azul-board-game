#include "../include/Board.h"

Board::Board() {
    board = new Tile *[MAX_BOARD_ROWS];
    for (int row = 0; row < MAX_BOARD_ROWS; ++row) {
        board[row] = new Tile[MAX_BOARD_COLS];
    }
    newBoard();
    newBroken();
}

Board::Board(string boardInput, string brokenInput) {
    board = new Tile *[MAX_BOARD_ROWS];
    for (int row = 0; row < MAX_BOARD_ROWS; ++row) {
        board[row] = new Tile[MAX_BOARD_COLS];
    }
    newBoard(boardInput);
    newBroken(brokenInput);
}

Board::~Board() {
    for (int row = 0; row < MAX_BOARD_ROWS; ++row) {
        delete[] board[row];
    }
    delete board;
    delete broken;
}

string Board::getBoardAsString() {
    string boardAsString;
    for (int row = 0; row < MAX_BOARD_ROWS; ++row) {
        for (int col = 0; col < MAX_BOARD_COLS; ++col) {
            boardAsString += board[row][col];
        }
    }
    return boardAsString;
}

string Board::getBrokenAsString() {
    string brokenAsString;
    int count = 0;
    while (broken->get(count) != EMPTY) {
        brokenAsString += broken->get(count);
        count++;
    }
    return brokenAsString;
}

void Board::addToStorage(Tile tile, int numberOfTiles, int row) {
    int brokenTiles = numberOfTiles - (row + 1);
    if (brokenTiles != 0) {
        for (int i = 0; i < brokenTiles; i++) {
            broken->addBack(tile);
            --numberOfTiles;
        }
    }
    for (int col = MAX_STORAGE_COLS; col >= row + MAX_STORAGE_COLS; --col) {
        board[row][col] = tile;
    }
}

int Board::addToMosaic() {
    int points = 0;
    for (int row = 0; row < MAX_BOARD_ROWS; ++row) {
        int col = 0;
        int count = 0;
        while (board[row][col] != DIVIDER) {
            if (board[row][col] != EMPTY) {
                ++count;
            }
            ++col;
        }
        if (count == row + 1) {
            Tile tile = board[row][col];
            Tile location = std::tolower(tile);
            while (board[row][col] != location) {
                ++col;
            }
            board[row][col] = tile;
            //TODO Tally up points based on surrounding tiles
        }
    }
    return points;
}

bool Board::isGameFinished() {
    bool finished = false;
    int row = 0;
    while (row != MAX_BOARD_ROWS && !finished) {
        int col = MAX_BOARD_COLS - MAX_MOSAIC_COLS;
        while (board[row][col] != EMPTY) {
            ++col;
        }
        if (col == MAX_MOSAIC_COLS) {
            finished = true;
        }
        ++row;
    }
    return finished;
}

void Board::newBoard() {
    string fileName = "../include/blankBoard.h";
    ifstream file;
    file.open(fileName);

    if (file.is_open()) {
        int row = 0;
        while (!file.eof() && row != MAX_BOARD_ROWS) {
            string line;
            getline(file, line);
            for (int col = 0; col < MAX_BOARD_COLS; ++col) {
                this->board[row][col] = line[col];
            }
            ++row;
        }
    }
    file.close();
}

void Board::newBoard(string boardInput) {
    int count = 0;
    for (int row = 0; row < MAX_BOARD_ROWS; ++row) {
        for (int col = 0; col < MAX_BOARD_COLS; ++col) {
            this->board[row][col] = boardInput[count];
            ++count;
        }
    }
}

void Board::newBroken() {
    broken->clear();
    for (int i = 0; i < MAX_BOARD_BROKEN; i++) {
        broken->addBack(EMPTY);
    }
}

void Board::newBroken(string brokenInput) {
    for (int i = 0; i < MAX_BOARD_BROKEN; ++i) {
        broken->addBack(brokenInput[i]);
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
        count++;
    }
    return lostPoints;
}


