#include "Player.h"

Player::Player(string name, int score) : name(std::move(name)),
                                         score(score),
                                         isTurn(false) { board = make_shared<Board>(); }

Player::Player(string name, int score, const string &storageInput, const string &mosaicInput,
               const string &brokenInput, bool isTurn) : name(std::move(name)),
                                                         score(score),
                                                         isTurn(isTurn) { board = make_shared<Board>(storageInput, mosaicInput, brokenInput); }

Player::Player(const Player &other) : name(other.name),
                                      score(other.score),
                                      isTurn(false) {}

Player::~Player() = default;

string Player::getName()
{
    return name;
}

int Player::getScore() const
{
    return score;
}

void Player::setScore(int score)
{
    this->score = score;
    if (this->score < 0)
    {
        this->score = 0;
    }
}

void Player::setPlayerTurn(bool value)
{
    this->isTurn = value;
}

bool Player::isPlayersTurn() const
{
    return isTurn;
}

string Player::getStrings(const string &data)
{
    string s;

    if (data == "storage")
    {
        s = board->getStorage()->toString();
    }
    else if (data == "mosaic")
    {
        s = board->getMosaic()->toString();
    }
    else if (data == "broken")
    {
        s = board->getBroken()->toString();
    }
    else
    {
        s = board->toString();
    }

    return s;
}

const shared_ptr<Board> &Player::getBoard() const
{
    return board;
}
