#include "Player.h"
Player::Player(string name, int score) :
        name(std::move(name)),
        score(score),
        isTurn(false)
        {board = make_unique<Board>();}

Player::Player(string name, int score, const string& storageInput, const string& mosaicInput, const string& brokenInput, bool isTurn) :
        name(std::move(name)),
        score(score),
        isTurn(isTurn)
        { board = make_unique<Board>(storageInput, mosaicInput, brokenInput); }

Player::Player(const Player &other) :
        name(other.name),
        score(other.score),
        isTurn(false) {}

Player::~Player() = default;

string Player::getName() {
    return name;
}

int Player::getScore() const {
    return score;
}

void Player::setScore(int score) {
    this->score = score;
}

void Player::setPlayerTurn(bool value) {
    this->isTurn = value;
}

bool Player::isPlayersTurn() const {
    return isTurn;
}

string Player::getStrings(const string& data) {
    string s;

    if (data == "storage") {s = board->storageToString();}
    else if (data == "mosaic") {s = board->mosaicToString();}
    else if (data == "broken") {s = board->brokenToString();}
    else {s = board->toString();}

    return s;
}


