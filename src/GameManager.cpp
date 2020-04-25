#include "../include/GameManager.h"

GameManager::GameManager() { }

GameManager::~GameManager() { }

bool GameManager::loadGame(string fileName) {
    bool loadSuccess = false;
    // TODO - Open file and send relevant information to different 
    // constructors to resume game
    return loadSuccess;
}

void GameManager::newGame() {
    // TODO - create a new game
}

void GameManager::playRound() {
    /**
     * while (factories are not empty) {
     * playTurn(player)
     * }
     */
}

void GameManager::playTurn(int factoryNo, Tile colour, int storageRow) {
    // TODO
}

int GameManager::getScore() {
    int score = 0;
    // player->getScore()
    // TODO
    return score;
}

void GameManager::help() {
    // TODO
}

void GameManager::saveGame() {
    // TODO
}