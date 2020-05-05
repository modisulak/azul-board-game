#include "Player.h"

Player::Player(string name, int score) :
        name(name),
        score(score),
        isTurn(false)
        {board = new Board();}

Player::Player(string name, int score, string storageInput, string mosaicInput, string brokenInput, bool isTurn) :
        name(name),
        score(score),
        isTurn(isTurn)
        { board = new Board(storageInput, mosaicInput, brokenInput); }

Player::Player(const Player &other) :
        name(other.name),
        score(other.score),
        isTurn(false) {}

Player::~Player() {
    delete board;
}

string Player::getName() {
    return name;
}

int Player::getScore() {
    return score;
}

void Player::setScore(int score) {
    this->score = score;
}

void Player::setPlayerTurn(bool value) {
    this->isTurn = value;
}

bool Player::isPlayersTurn() {
    return isTurn;
}

string Player::getStrings(string data) {
    string s;

    if (data == "storage") {s = board->storageToString();}
    else if (data == "mosaic") {s = board->mosaicToString();}
    else if (data == "broken") {s = board->brokenToString();}
    else {s = board->toString();}

    return s;
}


