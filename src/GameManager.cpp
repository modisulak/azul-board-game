#include "../include/GameManager.h"

GameManager::GameManager(string p1, string p2, int seed) :
        seed(seed) {
    string pl[MAX_PLAYER_INSTANCES] = {move(p1), move(p2)};
    players = make_unique<unique_ptr<Player>[]>(MAX_PLAYER_INSTANCES);
    for (int i = 0; i != MAX_PLAYER_INSTANCES; ++i) {
        players[i] = make_unique<Player>(pl[i], 0);
    }

    discard = make_unique<Factory>(MAX_DISCARD_TILES);
    bag = new std::vector<Tile>();
    boxLid = new LinkedList();

    factories = make_unique<unique_ptr<Factory>[]>(MAX_FACTORY_INSTANCES);
    for (int i = 0; i != MAX_FACTORY_INSTANCES; ++i) {
        factories[i] = make_unique<Factory>(MAX_FACTORY_TILES);
    }

    populateBag();
}

GameManager::GameManager(const string& filename) {
    players = make_unique<unique_ptr<Player>[]>(MAX_PLAYER_INSTANCES);
    factories = make_unique<unique_ptr<Factory>[]>(MAX_FACTORY_INSTANCES);
    bag = new std::vector<Tile>();
    boxLid = new LinkedList();

    ifstream file;
    file.open(filename);
    if (file.is_open()) {
        string line;
        getline(file, line);
        seed = stoi(line);

        getline(file, line);
        bool p1Turn = false;
        if (line == "1") {
            p1Turn = true;
        }

        string player1Name;
        string player1ScoreAsString;
        getline(file, player1Name);
        getline(file, player1ScoreAsString);
        int player1Score = stoi(player1ScoreAsString);

        string player2Name;
        string player2ScoreAsString;
        getline(file, player2Name);
        getline(file, player2ScoreAsString);
        int player2Score = stoi(player2ScoreAsString);

        string discardAsString;
        getline(file, discardAsString);
        discard = make_unique<Factory>(MAX_DISCARD_TILES, discardAsString);

        for (int i = 0; i != MAX_FACTORY_INSTANCES; ++i) {
            string factoryAsString;
            getline(file, factoryAsString);
            factories[i] = make_unique<Factory>(MAX_FACTORY_TILES,
                                                factoryAsString);
        }

        string p1storageAsString;
        for (int i = 0; i != MAX_BOARD_ROWS; ++i) {
            getline(file, line);
            p1storageAsString += line;
        }

        string p1BrokenAsString;
        getline(file, p1BrokenAsString);

        string p1MosaicAsString;
        getline(file, p1MosaicAsString);

        string p2storageAsString;
        for (int i = 0; i != MAX_BOARD_ROWS; ++i) {
            getline(file, line);
            p2storageAsString += line;
        }

        string p2BrokenAsString;
        getline(file, p2BrokenAsString);

        string p2MosaicAsString;
        getline(file, p2MosaicAsString);

        players[0] = make_unique<Player>(player1Name, player1Score,
                                         p1storageAsString, p1MosaicAsString,
                                         p1BrokenAsString, p1Turn);
        players[1] = make_unique<Player>(player2Name, player2Score,
                                         p2storageAsString, p2MosaicAsString,
                                         p2BrokenAsString, !p1Turn);

        getline(file, line);
        for (char c : line) {
            boxLid->addBack(c);
        }

        getline(file, line);
        for (char c : line) {
            bag->push_back(c);
        }
        file.close();
    }
}

GameManager::~GameManager() = default;

void GameManager::playGame() {

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
    while (i != MAX_TOTAL_TILES) {
        if (i < MAX_AMOUNT_COLOUR) { bag->push_back('R'); }
        else if (i < 2 * MAX_AMOUNT_COLOUR) { bag->push_back('Y'); }
        else if (i < 3 * MAX_AMOUNT_COLOUR) { bag->push_back('B'); }
        else if (i < 4 * MAX_AMOUNT_COLOUR) { bag->push_back('L'); }
        else { bag->push_back('U'); }
        ++i;
    }

    // TODO - Shuffle elements with use of a seed to ensure the 
    // randomness is the same every time
    for (int i = 0; i != bag->size() - 1; i++) {
        int j = i + rand() % (bag->size() - i);
        std::swap(bag[i], bag[j]);
    }
}


void GameManager::populateFactories() {
    for (int fNo = 0; fNo != MAX_FACTORY_INSTANCES; ++fNo) {
        for (int noTiles = 0; noTiles != MAX_FACTORY_TILES; ++noTiles) {
            factories[fNo]->addTile(bag->back());
            bag->pop_back();
        }
    }
    discard->addTile(FIRST_PLAYER_TILE);
}

void GameManager::saveGame(const string &filename) {
    string path = "../save_files/" + filename;

    std::ofstream outfile;
    outfile.open(path);

    outfile << seed << endl;
    outfile << players[0]->isPlayersTurn();

    for (int i = 0; i != MAX_PLAYER_INSTANCES; ++i) {
        outfile << players[i]->getName() << endl;
        outfile << players[i]->getScore() << endl;
    }

    outfile << discard->toString() << endl;

    for (int i = 0; i != MAX_FACTORY_INSTANCES; ++i) {
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
    return string(bag->data(), bag->size());
}


