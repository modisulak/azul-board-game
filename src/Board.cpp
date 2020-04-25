#include "../include/Board.h"

Board::Board() { 
    newBoard();
    newBroken();
}

Board::Board(string fileName) {
    newBoard(fileName);
    newBroken(fileName);
}

Board::~Board() {
    //TODO - delete 2D array of the board
    delete broken;
}

string Board::getBoardAsString() {
    string boardAsString = "";
    //TODO

    return boardAsString;
}

string Board::getBrokenAsString() {
    string brokenAsString = "";
    int count = 0;
    while(broken->get(count) != ' ') { 
       brokenAsString = brokenAsString + broken->get(count) + " ";
       count++;
    }
    return brokenAsString;
}



void Board::addToStorage(Tile colour, int numberOfTiles, int row) {
    int brokenTiles = numberOfTiles - row;
    if (brokenTiles != 0) {
        for (int i = 0; i < brokenTiles; i++) {
            broken->addBack(colour);
        }
    }
    // TODO - update board with tiles in storage spots
}

int Board::addToMosaic() {
    int points = 0;
    //TODO
    return points;
}

bool Board::isGameFinished() {
    bool finished = false;
    //TODO - loop through array and check if a row is complete
    return finished;
}

void Board::newBoard() {
    string fileName = "../include/blankBoard.h";
    //TODO - load board from file and add it to array
}

void Board::newBoard(string fileName) {
    //TODO - load board from save file and add it to array
}


void Board::newBroken() {
    broken->clear();
    for (int i = 0; i < MAX_BOARD_BROKEN; i++) {
        broken->addBack(' ');
    }
}

void Board::newBroken(string fileName) {
    //TODO - create a new broken list from a save file
}

void Board::addToBroken(Tile brokenTile) {
    broken->addBack(brokenTile);
}

int Board::lostPoints() {
    int lostPoints = 0;
    int count = 0;
    while(broken->get(count) != ' ') { 
       if (count < 2) {lostPoints = lostPoints - 1;}
       else if (count < 5) {lostPoints = lostPoints - 2;}
       else {lostPoints = lostPoints - 3;}
       count++;
    }
    return lostPoints;
}


