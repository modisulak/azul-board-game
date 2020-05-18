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
    bag = make_unique<LinkedList>();
    boxLid = make_unique<LinkedList>();

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
    bag = make_unique<LinkedList>();
    boxLid = make_unique<LinkedList>();

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
            bag->addBack(c);
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

    while (!p1Board->getMosaic()->isAnyRowComplete() && !p2Board->getMosaic()->isAnyRowComplete()) {
        playRound();
        endOfRound(p1Board, p2Board);
        prepareNextRound(p1Board, p2Board);
    }

    addEndOfGamePoints(p1Board, p2Board);

    cout << endl << "Final Scores:" << endl;
    cout << players[0]->getName() << ": " << players[0]->getScore() << endl;
    cout << players[1]->getName() << ": " << players[1]->getScore() << endl;

    string winner = "The winner is: ";

    getWinner(p1Board, p2Board, winner);

    cout << winner << endl;
    cout << "Press enter to return to the main menu." << endl;
    waitForEnter();
}

void GameManager::waitForEnter() const {
    cout << INPUT_TAB;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void
GameManager::getWinner(const shared_ptr<Board> &p1Board, const shared_ptr<Board> &p2Board,
                       string &winner) const {
    if (players[0]->getScore() > players[1]->getScore()) {
        winner += players[0]->getName();
    } else if (players[0]->getScore() < players[1]->getScore()) {
        winner += players[1]->getName();
    } else {
        int p1CompletedRows = 0;
        int p2CompletedRows = 0;
        for (int i = 0; i != MAX_BOARD_ROWS; ++i) {
            p1CompletedRows += p1Board->getMosaic()->isRowComplete(i);
            p2CompletedRows += p2Board->getMosaic()->isRowComplete(i);
        }
        if (p1CompletedRows > p2CompletedRows) {
            winner += players[0]->getName();
        } else if (p1CompletedRows < p2CompletedRows) {
            winner += players[1]->getName();
        } else {
            winner = "The game is a draw!";
        }
    }
}


void GameManager::playRound() {
    bool roundEnd = false;

    cout << endl << "=== Start Round ===" << endl;
    cout << endl << "Scores:" << endl;
    cout << players[0]->getName() << ": " << players[0]->getScore() << endl;
    cout << players[1]->getName() << ": " << players[1]->getScore() << endl;

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
        getPlayerInput(input, inputs);

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
            cout << endl;
            info(HELP_FILE);
            message = "";
        } else if (command == RULES) {
            cout << endl;
            info(RULES_FILE);
            message = "";
        } else if (command == EXIT) {
            cout << endl << "Quitting Game...\nGoodbye" << endl;
            exit(EXIT_SUCCESS);

        }
        cout << message << endl;
    }
}

void GameManager::endOfRound(shared_ptr<Board> &p1Board, shared_ptr<Board> &p2Board) const {
    cout << endl << "=== END OF ROUND ===" << endl;

    unsigned int p1Points = 0;
    unsigned int p2Points = 0;
    // Update mosaic and get score for newly placed tiles
    for (int row = 0; row != MAX_BOARD_ROWS; ++row) {
        // Ensure storage row is full of tiles
        if (p1Board->getStorage()->isRowComplete(row)) {
            p1Points += tileMosaic(p1Board, row);
        }
        if (p2Board->getStorage()->isRowComplete(row)) {
            p2Points += tileMosaic(p2Board, row);
        }
    }

    // remove lost points for broken tiles
    p1Points -= p1Board->getBroken()->lostPoints();
    p2Points -= p2Board->getBroken()->lostPoints();

    // Update players score
    players[0]->setScore(players[0]->getScore() + p1Points);
    players[1]->setScore(players[1]->getScore() + p2Points);

    cout << endl << "Round points after deductions:" << endl;
    cout << players[0]->getName() << ": " << p1Points << endl;
    cout << players[1]->getName() << ": " << p2Points << endl;
}

int GameManager::tileMosaic(const shared_ptr<Board> &board, int row) const {
    // Add the rightmost tile to the mosaic and get its points
    Tile tile = board->getStorage()->getTile(row, MAX_BOARD_COLS - 1);
    int col = board->getMosaic()->add(tile, row);

    //get the points for the move
    int points = board->getMosaic()->getPoints(row, col);

    // Add left over tiles to the box lid
    for (int i = 0; i != row; ++i) {
        boxLid->addBack(tile);
    }

    // Clear the row ready for the next round
    board->getStorage()->clearRow(row);
    return points;
}

void GameManager::prepareNextRound(const shared_ptr<Board> &p1Board, const shared_ptr<Board> &p2Board) {
    // Add broken tiles to back of the box lid
    bool p1FirstTurn = processBroken(p1Board);
    bool p2FirstTurn = processBroken(p2Board);

    //Update players turn depending who had the First player Tile
    players[0]->setPlayerTurn(p1FirstTurn);
    players[1]->setPlayerTurn(p2FirstTurn);

    populateFactories();
}

bool GameManager::processBroken(const shared_ptr<Board> &board) const {
    std::shared_ptr<Broken> broken = board->getBroken();
    bool firstTurn = false;
    for (Tile tile : broken->getTiles()) {
        if (tile != FIRST_PLAYER_TILE) {
            boxLid->addBack(tile);
        } else {
            firstTurn = true;
        }
    }
    broken->clear();
    return firstTurn;
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
        if (cin.eof()) {
            line = EXIT;
        }
    }
    return line;
}

void GameManager::getPlayerInput(string &input, std::vector<string> &inputs) const {
    std::istringstream stream(input);
    for (string string; stream >> string;) {
        inputs.push_back(string);
    }
}

bool GameManager::playTurn(std::vector<string> &inputs, int playerIndex) {
    bool success = false;
    int factoryNumber;
    Tile tile = inputs[2][0];
    if (validateInputs(inputs, factoryNumber)) {
        bool isDiscard = true;
        if (factoryNumber != 0) {
            factoryNumber -= 1;
            isDiscard = false;
        }

        if (tile != FIRST_PLAYER_TILE) {
            unsigned int noOfTiles = isDiscard ? discard->getTilesOfSameColour(tile)
                                               : factories[factoryNumber]->getTilesOfSameColour(tile);
            if (noOfTiles > 0) {
                success = addTiles(inputs[3], playerIndex, tile, noOfTiles);
                if (success) {
                    removePlayedTiles(playerIndex, factoryNumber, isDiscard, tile);
                }
            }
        }
    }
    return success;
}

bool GameManager::validateInputs(std::vector<string> &inputs, int &factoryNumber) {
    bool valid = false;
    // Validate factory selection
    if (isANumber(inputs[1])) {
        factoryNumber = std::stoi(inputs[1]);
        if (factoryNumber >= 0 && factoryNumber <= MAX_FACTORY_INSTANCES) {
            // Validate destination selection
            if (!inputs[3].empty() && isANumber(inputs[3])) {
                int destination = std::stoi(inputs[3]);
                if (destination >= 0 && destination <= MAX_BOARD_ROWS) {
                    valid = true;
                }
            } else if (inputs[3] == BROKEN) {
                valid = true;
            }
        }
    }
    return valid;
}

bool GameManager::isANumber(const string &input) {
    return input.find_first_not_of("0123456789") == string::npos;
}

bool GameManager::addTiles(const string &destination, int playerIndex, Tile tile, unsigned int noOfTiles) {
    bool success = false;
    if (isANumber(destination)) {
        int storageRow = std::stoi(destination) - 1;
        bool validMove = players[playerIndex]->getBoard()->validateMove(tile, storageRow);
        if (validMove) {
            while (noOfTiles != 0) {
                bool addedToStorage = players[playerIndex]->getBoard()->getStorage()->add(tile, storageRow);
                if (!addedToStorage) {
                    bool addedToBroken = players[playerIndex]->getBoard()->getBroken()->add(tile);
                    if (!addedToBroken) {
                        boxLid->addBack(tile);
                    }
                }
                --noOfTiles;
            }
            success = true;
        }
    } else if (destination == BROKEN) {
        for (unsigned int count = 0; count != noOfTiles; ++count) {
            bool addedToBroken = players[playerIndex]->getBoard()->getBroken()->add(tile);
            if (!addedToBroken) {
                boxLid->addBack(tile);
            }
        }
        success = true;
    }
    return success;
}

void GameManager::removePlayedTiles(int playerIndex, int factoryNumber, bool isDiscard, Tile tile) const {
    if (isDiscard) {
        if (discard->contains(FIRST_PLAYER_TILE)) {
            players[playerIndex]->getBoard()->getBroken()->add(FIRST_PLAYER_TILE);
            discard->removeTile(FIRST_PLAYER_TILE);
        }
        for (unsigned int i = 0; i != discard->getSize(); ++i) {
            if (discard->getTile(i) == tile) {
                discard->removeTile(i);
            }
        }
        discard->sortTiles();
    } else {
        for (unsigned int i = 0; i != factories[factoryNumber]->getSize(); ++i) {
            if (factories[factoryNumber]->getTile(i) != tile) {
                discard->addTile(factories[factoryNumber]->getTile(i));
            }
            factories[factoryNumber]->removeTile(i);
        }
        factories[factoryNumber]->sortTiles();
    }
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

void GameManager::addEndOfGamePoints(const shared_ptr<Board> &p1Board, const shared_ptr<Board> &p2Board) {
    //Tally end of game points
    int p1CompletedRows = 0;
    int p1CompletedCols = 0;
    int p2CompletedRows = 0;
    int p2CompletedCols = 0;

    for (int i = 0; i != MAX_BOARD_ROWS; ++i) {
        p1CompletedRows += p1Board->getMosaic()->isRowComplete(i);
        p1CompletedCols += p1Board->getMosaic()->isColumnComplete(i);
        p2CompletedRows += p2Board->getMosaic()->isRowComplete(i);
        p2CompletedCols += p2Board->getMosaic()->isColumnComplete(i);
    }

    // Find how many tiles the mosaic contains all 5 completed for
    int p1TileColourComplete = p1Board->getMosaic()->numberOfTilesCompleted();
    int p2TileColourComplete = p2Board->getMosaic()->numberOfTilesCompleted();

    // Update players score
    players[0]->setScore(players[0]->getScore() + (p1CompletedRows * ROW_COMPLETE_POINTS)
                         + (p1CompletedCols * COL_COMPLETE_POINTS) +
                         (p1TileColourComplete * TILE_COMPLETE_POINTS));
    players[1]->setScore(players[1]->getScore() + (p2CompletedRows * ROW_COMPLETE_POINTS)
                         + (p2CompletedCols * COL_COMPLETE_POINTS) +
                         (p2TileColourComplete * TILE_COMPLETE_POINTS));
}

void GameManager::info(string filename) {
    ifstream file;
    file.open(filename);
    if (file.is_open()) {
        string line;
        while (!file.eof()) {
            getline(file, line);
            cout << line << endl;
        }
    }
    file.close();

    cout << "Press enter to return to the game." << endl;
    waitForEnter();
}

void GameManager::populateBag() {
    int i = 0;
    std::vector<Tile> tempBag;
    while (i != MAX_TOTAL_TILES) {
        if (i < MAX_AMOUNT_COLOUR) { tempBag.push_back('R'); }
        else if (i < 2 * MAX_AMOUNT_COLOUR) { tempBag.push_back('Y'); }
        else if (i < 3 * MAX_AMOUNT_COLOUR) { tempBag.push_back('B'); }
        else if (i < 4 * MAX_AMOUNT_COLOUR) { tempBag.push_back('L'); }
        else { tempBag.push_back('U'); }
        ++i;
    }
    // Shuffle bag using random engine
    std::shuffle(std::begin(tempBag), std::end(tempBag), engine);

    for (char j : tempBag) {
        bag->addBack(j);
    }
}

void GameManager::populateFactories() {
    if (bag->size() < (MAX_FACTORY_INSTANCES * MAX_FACTORY_TILES)) {
        TransferLidToBag();
    }
    for (int fNo = 0; fNo != MAX_FACTORY_INSTANCES; ++fNo) {
        for (int noTiles = 0; noTiles != MAX_FACTORY_TILES; ++noTiles) {
            factories[fNo]->addTile(bag->get(0));
            bag->removeFront();
        }
    }
    discard->addTile(FIRST_PLAYER_TILE);
}

void GameManager::TransferLidToBag() {
    for (unsigned int i = 0; i != boxLid->size()-1; ++i) {
        bag->addBack(boxLid->get(i));
    }
    boxLid->clear();
}

void GameManager::saveGame(const string &filename) {
    string path = SAVE_PATH + filename + FILE_EXTENSION;

    std::ofstream outfile;
    outfile.open(path);
    if( !outfile ) {
      std::cerr << "Error: game could not be saved" << endl;
    } else {
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
        outfile << bag->toString();

        outfile.close();
    }
}

