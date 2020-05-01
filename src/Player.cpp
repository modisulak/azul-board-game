#include "Player.h"

Player::Player(string name, int score) :
        name(name),
        score(score),
        isTurn(false)
        {board = new Board();}

Player::Player(string name, int score, string storageInput, string mosaicInput, string brokenInput) :
        name(name),
        score(score),
        isTurn(false)
        { board = new Board(storageInput, mosaicInput, brokenInput); }

Player::Player(const Player &other) :
        name(other.name),
        score(other.score),
        isTurn(false) {}

Player::~Player() {}

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


