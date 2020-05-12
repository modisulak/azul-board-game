#include "../include/GameManager.h"

GameManager::GameManager(string p1, string p2, int seed) :
        seed(seed) {
    engine.seed(seed);

    string pl[MAX_PLAYER_INSTANCES] = {move(p1), move(p2)};
    players = make_unique<unique_ptr<Player>[]>(MAX_PLAYER_INSTANCES);
    for (int i = 0; i != MAX_PLAYER_INSTANCES; ++i) {
        players[i] = make_unique<Player>(pl[i], 0);
    }

    setFirstTurn();

    discard = make_unique<Factory>(MAX_DISCARD_TILES);
    bag = new std::vector<Tile>();
    boxLid = new LinkedList();

    populateBag();

    factories = make_unique<unique_ptr<Factory>[]>(MAX_FACTORY_INSTANCES);
    for (int i = 0; i != MAX_FACTORY_INSTANCES; ++i) {
        factories[i] = make_unique<Factory>(MAX_FACTORY_TILES);
    }
    populateFactories();
}

GameManager::GameManager(const string &filename) {
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
        engine.seed(seed);

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
            factories[i] = make_unique<Factory>(MAX_FACTORY_TILES, factoryAsString);
        }

        string p1storageAsString;
        for (int i = 0; i != MAX_BOARD_ROWS; ++i) {
            int blankSpaces = MAX_BOARD_COLS - i - 1;
            for (int j = 0; j < blankSpaces; ++j) {
                p1storageAsString += BLANK_SPACE;
            }
            getline(file, line);
            p1storageAsString += line;
        }

        string p1BrokenAsString;
        getline(file, p1BrokenAsString);

        string p1MosaicAsString;
        getline(file, p1MosaicAsString);

        string p2storageAsString;
        for (int i = 0; i != MAX_BOARD_ROWS; ++i) {
            int blankSpaces = MAX_BOARD_COLS - i - 1;
            for (int j = 0; j < blankSpaces; ++j) {
                p2storageAsString += BLANK_SPACE;
            }
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

void GameManager::setFirstTurn() {
    int min = 0;
    int max = 1;

    std::uniform_int_distribution<int> uniform_dist(min, max);
    int index = uniform_dist(engine);

    players[index]->setPlayerTurn(true);
}

void GameManager::playGame() {
    shared_ptr<Board> p1Board = players[0]->getBoard();
    shared_ptr<Board> p2Board = players[1]->getBoard();

    cout << endl << "Let's Play!" << endl;

    while (!p1Board->isGameFinished() && !p2Board->isGameFinished()) {
        playRound();

        // Update mosaic and get score for newly placed tiles
        int p1Points = p1Board->addToMosaic();
        int p2Points = p2Board->addToMosaic();

        // Update players score
        players[0]->setScore(players[0]->getScore() + p1Points);
        players[1]->setScore(players[1]->getScore() + p2Points);

        // Update players turn
        if (p1Board->getBroken()->includes(FIRST_PLAYER_TILE)) {
            players[0]->setPlayerTurn(true);
            players[1]->setPlayerTurn(false);
        } else {
            players[0]->setPlayerTurn(false);
            players[1]->setPlayerTurn(true);
        }

        // Clear the broken tiles
        p1Board->getBroken()->clear();
        p2Board->getBroken()->clear();

        populateFactories();
    }
    //TODO announce the winner!
}

void GameManager::playRound() {
    bool roundEnd = false;

    cout << endl << "=== Start Round ===" << endl;

    while (!roundEnd) {
        int playerIndex;
        if (players[0]->isPlayersTurn()) {
            playerIndex = 0;
        } else {
            playerIndex = 1;
        }

        string input = promptPlayer(playerIndex);
        transform(input.begin(), input.end(), input.begin(), ::toupper);
        std::vector<string> inputs;
        getInputsVector(input, inputs);

        string message = "Invalid input, try again.";
        string command = inputs[0];
        if (command == TURN) {
            if (inputs.size() == TURN_ARGC) {
                bool success = playTurn(inputs, playerIndex);
                if (success) {
                    roundEnd = isRoundEnd();
                    for (int i = 0; i < MAX_PLAYER_INSTANCES; ++i) {
                        players[i]->setPlayerTurn(!players[i]->isPlayersTurn());
                    }
                    message = "Turn successful.";
                }
            }
        } else if (command == SAVE) {
            if (inputs.size() == SAVE_ARGC) {
                string filename = inputs[1];
                transform(filename.begin(), filename.end(), filename.begin(), ::tolower);
                saveGame(filename);
                message = "Game Saved.";
            }
        } else if (command == HELP) {
            help();
            message = "";
        }
        cout << message << endl;
    }
}

string GameManager::promptPlayer(int index) {

    cout << endl << "Turn for player " << players[index]->getName() << ":" << endl;

    cout << endl << "Factories: " << endl << "0: ";
    cout << discard->toString() << endl;

    for (int i = 0; i < MAX_FACTORY_INSTANCES; ++i) {
        cout << i + 1 << ": ";
        cout << factories[i]->toString() << endl;
    }

    cout << endl << "Mosaic for " << players[index]->getName() << ":" << endl;

    cout << players[index]->getBoard()->toString() << endl;

    cout << endl << INPUT_TAB;
    string line;
    while (line.empty()) {
        getline(cin, line);
    }
    return line;
}

void GameManager::getInputsVector(string &input, std::vector<string> &inputs) const {
    string delimiter = " ";
    int pos = 0;
    string token;
    while ((pos = input.find(delimiter)) != string::npos) {
        token = input.substr(0, pos);
        inputs.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    inputs.push_back(input);
}

bool GameManager::playTurn(std::vector<string> &inputs, int playerIndex) {
    bool success = false;
    if (validateInputs(inputs)) {
        int factoryNumber = std::stoi(inputs[1]);
        bool isDiscard = true;
        if (factoryNumber != 0) {
            factoryNumber -= 1;
            isDiscard = false;
        }
        Tile tile = inputs[2][0];


        if (tile != FIRST_PLAYER_TILE) {
            int noOfTiles = isDiscard ? discard->getTilesOfSameColour(tile)
                                      : factories[factoryNumber]->getTilesOfSameColour(tile);

            if (noOfTiles > 0) {
                if (isANumber(inputs[3])) {
                    int storageRow = std::stoi(inputs[3]) - 1;
                    success = players[playerIndex]->getBoard()->addToStorage(tile, noOfTiles, storageRow);
                } else if(inputs[3] == BROKEN){
                    for (int count = 0; count != noOfTiles; ++count) {
                        players[playerIndex]->getBoard()->addToBroken(tile);
                    }
                    success = true;
                }
                if (success) {
                    if (isDiscard) {
                        if (discard->contains(FIRST_PLAYER_TILE)) {
                            players[playerIndex]->getBoard()->addToBroken(FIRST_PLAYER_TILE);
                            discard->removeTile(FIRST_PLAYER_TILE);
                        }
                        for (int i = 0; i != discard->getSize(); ++i) {
                            if (discard->getTile(i) == tile) {
                                discard->removeTile(i);
                            }
                        }
                    } else {
                        for (int i = 0; i != factories[factoryNumber]->getSize(); ++i) {
                            if (factories[factoryNumber]->getTile(i) != tile) {
                                discard->addTile(factories[factoryNumber]->getTile(i));
                            }
                            factories[factoryNumber]->removeTile(i);
                        }
                    }
                }
            }
        }
    }
    return success;
}

bool GameManager::validateInputs(std::vector<string> &inputs) {
    return isANumber(inputs[1]) && inputs[2].length() == TILE_LENGTH;
}

bool GameManager::isANumber(const string &input) {
    return input.find_first_not_of("0123456789") == string::npos;
}

bool GameManager::isRoundEnd() const {
    bool roundEnd;
    int i = 0;
    while (i != MAX_FACTORY_INSTANCES && factories[i]->isEmpty()) {
        ++i;
    }
    roundEnd = discard->isEmpty() && i == MAX_FACTORY_INSTANCES;
    return roundEnd;
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
    // Shuffle bag using random engine
    std::shuffle(std::begin(*bag), std::end(*bag), engine);
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
    string path = SAVE_PATH + filename + FILE_EXTENSION;

    std::ofstream outfile;
    outfile.open(path);

    outfile << seed << endl;
    outfile << players[0]->isPlayersTurn() << endl;

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


