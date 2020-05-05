#include "../include/GameManager.h"

GameManager::GameManager(string p1, string p2, int seed) : 
    seed(seed)
{   
    string pl [MAX_PLAYER_INSTANCES] = {p1, p2};
    players = new Player *[MAX_PLAYER_INSTANCES];
    for (int i = 0; i != MAX_PLAYER_INSTANCES; i++) {
        players[i] = new Player(pl[i], 0);
    }

    discard = new Factory(true);
    bag = new std::vector<Tile>();
    boxLid = new LinkedList();

    factories = new Factory *[MAX_FACTORY_INSTANCES];
    for (int i = 0; i != MAX_FACTORY_INSTANCES; i++) {
        factories[i] = new Factory();
    }

    populateBag();

}

/*
GameManager::GameManager(string fileName) : 
    // TODO - Load information from save file 
    { 
        player1 = new Player(name, score, storageInput, mosaicInput, brokenInput);
        player2 = new Player(name, score, storageInput, mosaicInput, brokenInput);
    }
*/

GameManager::~GameManager() { 
    // TODO
}

void GameManager::playRound() {
    populateFactories();
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
    // score = player1->getScore()
    // TODO
    return score;
}

void GameManager::help() {
    // TODO
}

void GameManager::populateBag() {
    int i = 0;
    while (i < MAX_TOTAL_TILES) {
        if (i < MAX_AMOUNT_COLOUR) { bag->push_back('R'); }
        else if (i < 2* MAX_AMOUNT_COLOUR) { bag->push_back('Y'); }
        else if (i < 3* MAX_AMOUNT_COLOUR) { bag->push_back('B'); }
        else if (i < 4* MAX_AMOUNT_COLOUR) { bag->push_back('L'); }
        else { bag->push_back('U'); }
    }

    // TODO - Shuffle elements with use of a seed to ensure the 
    // randomness is the same every time
    for (int i = 0; i < bag->size() - 1; i++) {
      int j = i + rand() % (bag->size() - i);
      std::swap(bag[i], bag[j]);
   }
}


void GameManager::populateFactories() {
    for (int fNo = 0; fNo < MAX_FACTORY_INSTANCES; fNo++) {
        for (int noTiles = 0; noTiles < MAX_FACTORY_TILES; noTiles++) {
            factories[fNo][noTiles] = bag->back();
            bag->pop_back();
        }
    }

    discard[0] = 'F';
}

void GameManager::saveGame(string fileName) {
    string path = "../save_files/" + fileName;

    std::ofstream outfile;
    outfile.open(path);

    outfile << seed << endl;
    outfile << players[0]->isPlayersTurn();

    for (int i = 0; i != MAX_PLAYER_INSTANCES; i++) {
        outfile << players[i]->getName() << endl;
        outfile << players[i]->getScore() << endl;
    }

    outfile << discard->toString() << endl;

    for (int i = 0; i != MAX_FACTORY_INSTANCES; i++) {
        outfile << factories[i]->toString() << endl;
    }

    for (int i = 0; i != MAX_PLAYER_INSTANCES; i++) {
        outfile << players[i]->getStrings("storage") << endl;
        outfile << players[i]->getStrings("broken") << endl;
        outfile << players[i]->getStrings("mosaic") << endl;
    }

    outfile << boxLid->toString() << endl;
    outfile << bagToString();

    outfile.close();
}

string GameManager::bagToString() {
    return std::string(bag->data(), bag->size());
}