#include "Player.h"

Player::Player (string name, int score) :
    name(name),
    score(score) {}

Player::Player(const Player &other) :
    name(other.name),
    score(other.score) {}

Player::~Player() {}    

string Player::getName() { 
    return name;
}

int Player::getScore() { 
    return score;
}

void  Player::setScore(int score) { 
    this->score = score; 
}


