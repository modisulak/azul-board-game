#include "../include/GameManager.h"

GameManager::GameManager(std::vector<string> &newplayers, int seed, int numofplayers, int numofcfactory) : seed(seed)
{
    engine.seed(seed);
    numOfPlayers = numofplayers;
    numOfCFactory = numofcfactory;
    players = make_unique<unique_ptr<Player>[]>(numOfPlayers);
    for (int i = 0; i < numOfPlayers; ++i)
    {
        players[i] = make_unique<Player>(newplayers.at(i), 0);
    }

    if (numOfPlayers == TWO_PLAYER_GAME)
    {
        maxNumOfFactories = MAX_FACTORY_INSTANCES_2;
    }
    else if (numOfPlayers == THREE_PLAYER_GAME)
    {
        maxNumOfFactories = MAX_FACTORY_INSTANCES_3;
    }
    else if (numOfPlayers == FOUR_PLAYER_GAME)
    {
        maxNumOfFactories = MAX_FACTORY_INSTANCES_4;
    }

    setFirstTurn();

    discard = make_unique<Factory>(MAX_DISCARD_TILES);
    discard2 = NULL;
    if (numOfCFactory == TWO_CENTER_FACTORY)
    {
        discard2 = make_unique<Factory>(MAX_DISCARD_TILES);
    }
    bag = make_unique<LinkedList>();
    boxLid = make_unique<LinkedList>();

    populateBag();

    factories = make_unique<unique_ptr<Factory>[]>(maxNumOfFactories);
    for (int i = 0; i != maxNumOfFactories; ++i)
    {
        factories[i] = make_unique<Factory>(MAX_FACTORY_TILES);
    }
    populateFactories();
}

GameManager::GameManager(const string &filename)
{

    bag = make_unique<LinkedList>();
    boxLid = make_unique<LinkedList>();

    ifstream file;
    file.open(filename);
    if (file.is_open())
    {
        string line;
        getline(file, line);

        seed = stoi(line);
        engine.seed(seed);

        getline(file, line);
        numOfPlayers = stoi(line);
        players = make_unique<unique_ptr<Player>[]>(numOfPlayers);

        getline(file, line);
        maxNumOfFactories = stoi(line);
        factories = make_unique<unique_ptr<Factory>[]>(maxNumOfFactories);

        getline(file, line);
        numOfCFactory = stoi(line);

        getline(file, line);
        pTurn = stoi(line);

        std::vector<string> playersname;
        std::vector<string> playersscoreSTR;
        std::vector<int> playerscore;

        for (int i = 0; i < numOfPlayers; ++i)
        {
            getline(file, line);
            playersname.push_back(line);
            getline(file, line);
            playersscoreSTR.push_back(line);
            playerscore.push_back(std::stoi(playersscoreSTR.at(i)));
        }

        string discardAsString;
        string discard2AsString;
        getline(file, discardAsString);
        if (discardAsString.length() > MAX_DISCARD_TILES)
        {
            throw std::invalid_argument("Discard invalid.");
        }
        else
        {
            discard = make_unique<Factory>(MAX_DISCARD_TILES, discardAsString);
        }
        if (numOfCFactory == TWO_CENTER_FACTORY)
        {
            getline(file, discard2AsString);
            if (discard2AsString.length() > MAX_DISCARD_TILES)
            {
                throw std::invalid_argument("Discard invalid.");
            }
            else
            {
                discard2 = make_unique<Factory>(MAX_DISCARD_TILES, discard2AsString);
            }
        }

        for (int i = 0; i != maxNumOfFactories; ++i)
        {
            string factoryAsString;
            getline(file, factoryAsString);
            if (factoryAsString.length() > MAX_FACTORY_TILES)
            {
                throw std::invalid_argument("Factory invalid.");
            }
            if (!factoryAsString.empty())
            {
                factories[i] = make_unique<Factory>(MAX_FACTORY_TILES, factoryAsString);
            }
        }

        std::vector<string> playerStorageString;
        std::vector<string> playerBrokenString;
        std::vector<string> playerMosiacString;

        for (int count = 0; count < numOfPlayers; ++count)
        {
            getline(file, line);
            if (line.length() != MAX_BOARD_ROWS * MAX_BOARD_COLS)
            {
                throw std::invalid_argument("Player Storage invalid.");
            }
            playerStorageString.push_back(line);

            getline(file, line);
            playerBrokenString.push_back(line);
            if (playerBrokenString[count].length() > MAX_BROKEN_TILES)
            {
                throw std::invalid_argument("Player Broken invalid.");
            }
            getline(file, line);
            playerMosiacString.push_back(line);
            if (playerMosiacString[count].length() != MAX_BOARD_ROWS * MAX_BOARD_COLS)
            {
                throw std::invalid_argument("Player Mosaic invalid.");
            }
        }

        for (int i = 0; i < numOfPlayers; ++i)
        {
            bool pTurnBool = false;

            if (pTurn == i)
            {
                pTurnBool = true;
            }
            players[i] = make_unique<Player>(playersname[i], playerscore.at(i),
                                             playerStorageString.at(i), playerMosiacString.at(i),
                                             playerBrokenString.at(i), pTurnBool);
        }

        getline(file, line);
        for (char c : line)
        {
            boxLid->addBack(c);
        }
        if (boxLid->size() > MAX_TOTAL_TILES)
        {
            throw std::invalid_argument("Box Lid invalid.");
        }

        getline(file, line);
        for (char c : line)
        {
            bag->addBack(c);
        }
        if (bag->size() > MAX_TOTAL_TILES)
        {
            throw std::invalid_argument("Bag invalid.");
        }
        file.close();
    }
}

GameManager::~GameManager() = default;

void GameManager::setFirstTurn()
{
    int min = 0;
    int max = numOfPlayers;

    std::uniform_int_distribution<int> uniform_dist(min, max);
    int index = uniform_dist(engine);

    players[index]->setPlayerTurn(true);
}

void GameManager::playGame()
{
    bool gameEnded = false;
    cout << endl
         << "Let's Play!" << endl;

    for (int i = 0; i < numOfPlayers; ++i)
    {
        if (players[i]->getBoard()->getMosaic()->isAnyRowComplete())
        {
            gameEnded = true;
        }
    }

    while (!gameEnded)
    {
        playRound();
        endOfRound();
        prepareNextRound();
    }

    addEndOfGamePoints();

    cout << endl
         << "Final Scores:" << endl;
    for (int i = 0; i < numOfPlayers; ++i)
    {
        cout << players[i]->getName() << ": " << players[i]->getScore() << endl;
    }

    string winner = "The winner is: ";

    getWinner(winner);

    cout << winner << endl;
    cout << "Press enter to return to the main menu." << endl;
    waitForEnter();
}

void GameManager::waitForEnter() const
{
    cout << INPUT_TAB;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void GameManager::getWinner(string &winner) const
{
    bool success = false;
    int maxScore = players[0]->getScore();
    string name;
    for (int i = 0; i < numOfPlayers; ++i)
    {
        if (players[i]->getScore() > maxScore)
        {
            maxScore = players[i]->getScore();
            name = players[i]->getName();
            success = true;
        }
    }
    winner += name;
    if (success == false)
    {
        std::array<int, 4> pCompletedRows = {0};
        bool winnerFound = false;
        for (int i = 0; i != MAX_BOARD_ROWS; ++i)
        {
            for (int j = 0; j < numOfPlayers; ++j)
            {
                pCompletedRows[i] = players[i]->getBoard()->getMosaic()->isRowComplete(i);
            }
        }
        if (winnerFound == false)
        {
            int maxCompletedRows = pCompletedRows[0];
            for (int i = 0; i < numOfPlayers; ++i)
            {
                if (pCompletedRows[i] > maxCompletedRows)
                {
                    maxCompletedRows = pCompletedRows[i];
                    winner += players[i]->getName();
                    winnerFound = true;
                }
            }
        }
        else if (!winnerFound)
        {
            winner = "The game is a draw!";
        }
    }
}

void GameManager::playRound()
{
    bool roundEnd = false;

    cout << endl
         << "=== Start Round ===" << endl;
    cout << endl
         << "Scores:" << endl;
    for (int i = 0; i < numOfPlayers; ++i)
    {
        cout << players[i]->getName() << ": " << players[i]->getScore() << endl;
    }

    while (!roundEnd)
    {
        int playerIndex;
        for (int i = 0; i < numOfPlayers; ++i)
        {
            if (players[i]->isPlayersTurn())
            {
                playerIndex = i;
            }
        }

        string input = promptPlayer(playerIndex);
        transform(input.begin(), input.end(), input.begin(), ::toupper);
        std::vector<string> inputs;
        getPlayerInput(input, inputs);

        string message = "Invalid input, try again.";
        string command = inputs[0];
        if (command == TURN)
        {
            if (numOfCFactory == TWO_CENTER_FACTORY)
            {
                if (inputs.size() == TURN_ARG2C || inputs[1] == FIRST_C_FACTORY_STR ||
                    inputs[1] == SECOND_C_FACTORY_STR)
                {
                    bool success = playTurn(inputs, playerIndex);
                    if (success)
                    {
                        roundEnd = isRoundEnd();
                        setNextPlayer(playerIndex);
                        message = "Turn successful.";
                    }
                }
            }
            else
            {
                if (inputs.size() == TURN_ARGC)
                {
                    bool success = playTurn(inputs, playerIndex);
                    if (success)
                    {
                        roundEnd = isRoundEnd();
                        setNextPlayer(playerIndex);
                        message = "Turn successful.";
                    }
                }
            }
        }
        else if (command == SAVE)
        {
            if (inputs.size() == SAVE_ARGC)
            {
                string filename = inputs[1];
                transform(filename.begin(), filename.end(), filename.begin(), ::tolower);
                saveGame(filename);
                message = "Game Saved.";
            }
        }
        else if (command == HELP)
        {
            cout << endl;
            Utils::info(HELP_FILE);
            message = "";
        }
        else if (command == RULES)
        {
            cout << endl;
            Utils::info(RULES_FILE);
            message = "";
        }
        else if (command == EXIT)
        {
            cout << endl
                 << "Quitting Game...\nGoodbye" << endl;
            exit(EXIT_SUCCESS);
        }
        cout << message << endl;
    }
}

void GameManager::endOfRound() const
{
    cout << endl
         << "=== END OF ROUND ===" << endl;

    std::array<unsigned int, 4> playerpoints = {0};
    // Update mosaic and get score for newly placed tiles
    for (int row = 0; row != MAX_BOARD_ROWS; ++row)
    {
        for (int i = 0; i < numOfPlayers; ++i)
        {
            if (players[i]->getBoard()->getStorage()->isRowComplete(row))
            {
                playerpoints[i] += tileMosaic(players[i]->getBoard(), row);
            }
        }
    }

    // remove lost points for broken tiles
    for (int i = 0; i < numOfPlayers; ++i)
    {
        playerpoints[i] -= players[i]->getBoard()->getBroken()->lostPoints();
    }
    // Update players score
    for (int i = 0; i < numOfPlayers; ++i)
    {
        players[i]->setScore(players[i]->getScore() + playerpoints[i]);
    }
    cout << endl
         << "Round points after deductions:" << endl;
    for (int i = 0; i < numOfPlayers; ++i)
    {
        cout << players[i]->getName() << ": " << playerpoints[i] << endl;
    }
}

int GameManager::tileMosaic(const shared_ptr<Board> &board, int row) const
{
    // Add the rightmost tile to the mosaic and get its points
    Tile tile = board->getStorage()->getTile(row, MAX_BOARD_COLS - 1);
    int col = board->getMosaic()->add(tile, row);

    //get the points for the move
    int points = board->getMosaic()->getPoints(row, col);

    // Add left over tiles to the box lid
    for (int i = 0; i != row; ++i)
    {
        boxLid->addBack(tile);
    }

    // Clear the row ready for the next round
    board->getStorage()->clearRow(row);
    return points;
}

void GameManager::prepareNextRound()
{
    for (int i = 0; i < numOfPlayers; ++i)
    {
        players[i]->setPlayerTurn(processBroken(players[i]->getBoard()));
    }
    populateFactories();
}

bool GameManager::processBroken(const shared_ptr<Board> &board) const
{
    std::shared_ptr<Broken> broken = board->getBroken();
    bool firstTurn = false;
    for (Tile tile : broken->getTiles())
    {
        if (tile != FIRST_PLAYER_TILE)
        {
            boxLid->addBack(tile);
        }
        else
        {
            firstTurn = true;
        }
    }
    broken->clear();
    return firstTurn;
}

string GameManager::promptPlayer(int index)
{
    if (numOfCFactory == TWO_CENTER_FACTORY)
    {
        cout << endl
             << "Factories: " << endl
             << "10: ";
        cout << displayColoured(discard->toString()) << endl;
        cout << "20: ";
        cout << displayColoured(discard2->toString()) << endl;
    }
    else
    {
        cout << endl
             << "Factories: " << endl
             << "0: ";
        cout << displayColoured(discard->toString()) << endl;
    }

    for (int i = 0; i < maxNumOfFactories; ++i)
    {
        cout << i + 1 << ": ";
        //cout << factories[i]->toString() << endl;
        cout << displayColoured(factories[i]->toString()) << endl;
    }

    // Outputting the current player to the board.
    for (int i = 0; i < numOfPlayers; ++i)
    {
        if (players[i]->isPlayersTurn())
        {
            cout << endl
                 << "Mosaic for "
                 << "★" << players[i]->getName() << ":" << endl;

            cout << players[i]->getBoard()->toString() << endl;
        }
    }
    // Outputting opponents board.
    std::vector<string> boardToStringArray;
    for (int i = 0; i < numOfPlayers; ++i)
    {
        if (!players[i]->isPlayersTurn())
        {
            boardToStringArray.push_back(players[i]->getBoard()->toString());
        }
    }
    cout << endl
         << "OPPONENT BOARDS: "
         << endl
         << endl;

    for (int i = 0; i < numOfPlayers; ++i)
    {
        if (!players[i]->isPlayersTurn())
        {
            cout << "Player: " << players[i]->getName()
                 << string((BOARD_SPACE * 3) - (players[i]->getName().length() + NAME_STRING_LENGTH), ' ');
        }
    }
    cout << endl;

    int x = 0;
    int j = 0;
    for (int i = 0; i != MAX_BOARD_ROWS; ++i)
    {
        for (string line : boardToStringArray)
        {
            j = x;
            while (j != line.length() && line[j] != '\n')
            {
                cout << line[j];
                ++j;
            }
            cout << string(BOARD_SPACE, ' ');
        }
        cout << endl;
        x = j + 1;
    }
    for (string line : boardToStringArray)
    {
        j = x;
        int space = 0;
        while (j != line.length() && line[j] != '\n')
        {
            cout << line[j];
            ++j;
            space++;
        }
        cout << string(((BOARD_SPACE * 3) + SPACE_OFFSET) - space, ' ');
    }
    cout << endl;
    x = j + 1;

    cout << endl
         << players[index]->getName()
         << INPUT_TAB;
    string line;
    while (line.empty())
    {
        getline(cin, line);
        if (cin.eof())
        {
            line = EXIT;
        }
    }
    return line;
}

void GameManager::getPlayerInput(string &input, std::vector<string> &inputs) const
{
    std::istringstream stream(input);
    for (string string; stream >> string;)
    {
        inputs.push_back(string);
    }
}

bool GameManager::playTurn(std::vector<string> &inputs, int playerIndex)
{
    bool success = false;
    int factoryNumber;
    Tile tile = inputs[2][0];
    if (validateInputs(inputs, factoryNumber))
    {
        bool isDiscard = false;
        bool isDiscard2 = false;
        if (numOfCFactory == TWO_CENTER_FACTORY)
        {
            if (factoryNumber == FIRST_C_FACTORY)
            {
                isDiscard = true;
            }
            else if (factoryNumber == SECOND_C_FACTORY)
            {
                isDiscard2 = true;
            }
            else
            {
                factoryNumber -= 1;
            }
        }
        else
        {
            if (factoryNumber == NORMAL_C_FACTORY)
            {
                isDiscard = true;
            }
            else
            {
                factoryNumber -= 1;
            }
        }

        if (tile != FIRST_PLAYER_TILE)
        {
            unsigned int noOfTiles;
            if (isDiscard)
            {
                noOfTiles = discard->getTilesOfSameColour(tile);
            }
            else if (isDiscard2)
            {
                noOfTiles = discard2->getTilesOfSameColour(tile);
            }
            else
            {
                noOfTiles = factories[factoryNumber]->getTilesOfSameColour(tile);
            }
            if (noOfTiles > 0)
            {
                success = addTiles(inputs[3], playerIndex, tile, noOfTiles);
                if (success)
                {
                    removePlayedTiles(playerIndex, inputs[4], factoryNumber, isDiscard, isDiscard2, tile);
                }
            }
        }
    }
    return success;
}

bool GameManager::validateInputs(std::vector<string> &inputs, int &factoryNumber)
{
    bool valid = false;
    // Validate factory selection
    if (isANumber(inputs[1]))
    {
        factoryNumber = std::stoi(inputs[1]);
        if ((factoryNumber >= 0 && factoryNumber <= maxNumOfFactories) ||
            factoryNumber == FIRST_C_FACTORY || factoryNumber == SECOND_C_FACTORY)
        {
            // Validate destination selection
            if (!inputs[3].empty() && isANumber(inputs[3]))
            {
                int destination = std::stoi(inputs[3]);
                if (destination >= 0 && destination <= BROKEN)
                {
                    valid = true;
                }
            }
            if (numOfCFactory != TWO_CENTER_FACTORY)
            {
                inputs.push_back(FIRST_C_FACTORY_STR);
            }
            if (factoryNumber == FIRST_C_FACTORY)
            {
                inputs.push_back(FIRST_C_FACTORY_STR);
            }
            else if (factoryNumber == SECOND_C_FACTORY)
            {
                inputs.push_back(SECOND_C_FACTORY_STR);
            }
        }
    }
    return valid;
}

bool GameManager::isANumber(const string &input)
{
    return input.find_first_not_of("0123456789") == string::npos;
}

bool GameManager::addTiles(const string &destination, int playerIndex, Tile tile, unsigned int noOfTiles)
{
    bool success = false;
    if (isANumber(destination))
    {
        int input = std::stoi(destination);
        if (input != BROKEN)
        {
            int storageRow = std::stoi(destination) - 1;
            bool validMove = players[playerIndex]->getBoard()->validateMove(tile, storageRow);
            if (validMove)
            {
                while (noOfTiles != 0)
                {
                    bool addedToStorage = players[playerIndex]->getBoard()->getStorage()->add(tile, storageRow);
                    if (!addedToStorage)
                    {
                        bool addedToBroken = players[playerIndex]->getBoard()->getBroken()->add(tile);
                        if (!addedToBroken)
                        {
                            boxLid->addBack(tile);
                        }
                    }
                    --noOfTiles;
                }
                success = true;
            }
        }
        else if (input == BROKEN)
        {
            for (unsigned int count = 0; count != noOfTiles; ++count)
            {
                bool addedToBroken = players[playerIndex]->getBoard()->getBroken()->add(tile);
                if (!addedToBroken)
                {
                    boxLid->addBack(tile);
                }
            }
            success = true;
        }
    }

    return success;
}

void GameManager::removePlayedTiles(int playerIndex, const string cFactory, int factoryNumber, bool isDiscard,
                                    bool isDiscard2, Tile tile) const
{
    if (isDiscard || isDiscard2)
    {
        if (discard->contains(FIRST_PLAYER_TILE))
        {
            players[playerIndex]->getBoard()->getBroken()->add(FIRST_PLAYER_TILE);
            discard->removeTile(FIRST_PLAYER_TILE);
            if (numOfCFactory == TWO_CENTER_FACTORY)
            {
                discard2->removeTile(FIRST_PLAYER_TILE);
            }
        }
        if (isDiscard)
        {
            for (unsigned int i = 0; i != discard->getSize(); ++i)
            {
                if (discard->getTile(i) == tile)
                {
                    discard->removeTile(i);
                }
            }
            discard->sortTiles();
        }
        else if (isDiscard2)
        {
            for (unsigned int i = 0; i != discard2->getSize(); ++i)
            {
                if (discard2->getTile(i) == tile)
                {
                    discard2->removeTile(i);
                }
            }
            discard2->sortTiles();
        }
    }
    else
    {
        for (unsigned int i = 0; i != factories[factoryNumber]->getSize(); ++i)
        {
            if (factories[factoryNumber]->getTile(i) != tile)
            {
                if (cFactory == FIRST_C_FACTORY_STR)
                {
                    discard->addTile(factories[factoryNumber]->getTile(i));
                }
                else if (cFactory == SECOND_C_FACTORY_STR)
                {
                    discard2->addTile(factories[factoryNumber]->getTile(i));
                }
                else
                {
                    discard->addTile(factories[factoryNumber]->getTile(i));
                }
            }
            factories[factoryNumber]->removeTile(i);
        }
        factories[factoryNumber]->sortTiles();
    }
}

bool GameManager::isRoundEnd() const
{
    bool roundEnd;
    int i = 0;
    while (i != maxNumOfFactories && factories[i]->isEmpty())
    {
        ++i;
    }
    if (numOfCFactory == TWO_CENTER_FACTORY)
    {
        roundEnd = discard->isEmpty() && discard2->isEmpty() && i == maxNumOfFactories;
    }
    else
    {
        roundEnd = discard->isEmpty() && i == maxNumOfFactories;
    }
    return roundEnd;
}

void GameManager::addEndOfGamePoints()
{
    std::array<int, 4> pCompletedRows;
    std::array<int, 4> pCompletedCols;

    for (int i = 0; i != MAX_BOARD_ROWS; ++i)
    {
        for (int j = 0; j < numOfPlayers; ++j)
        {
            pCompletedRows[j] = players[j]->getBoard()->getMosaic()->isRowComplete(i);
            pCompletedCols[j] = players[j]->getBoard()->getMosaic()->isColumnComplete(i);
        }
    }

    // Find how many tiles the mosaic contains all 5 completed for
    std::array<int, 4> pTileColourComplete;
    for (int i = 0; i < numOfPlayers; ++i)
    {
        pTileColourComplete[i] = players[i]->getBoard()->getMosaic()->numberOfTilesCompleted();
    }
    // Update players score
    for (int i = 0; i < numOfPlayers; ++i)
    {
        players[i]->setScore(players[i]->getScore() + (pCompletedRows[i] * ROW_COMPLETE_POINTS) +
                             (pCompletedCols[i] * COL_COMPLETE_POINTS) +
                             (pTileColourComplete[i] * TILE_COMPLETE_POINTS));
    }
}

void GameManager::populateBag()
{
    int i = 0;
    std::vector<Tile> tempBag;
    while (i != MAX_TOTAL_TILES)
    {
        if (i < MAX_AMOUNT_COLOUR)
        {
            tempBag.push_back('R');
        }
        else if (i < 2 * MAX_AMOUNT_COLOUR)
        {
            tempBag.push_back('Y');
        }
        else if (i < 3 * MAX_AMOUNT_COLOUR)
        {
            tempBag.push_back('B');
        }
        else if (i < 4 * MAX_AMOUNT_COLOUR)
        {
            tempBag.push_back('L');
        }
        else
        {
            tempBag.push_back('U');
        }
        ++i;
    }
    // Shuffle bag using random engine
    std::shuffle(std::begin(tempBag), std::end(tempBag), engine);

    for (char j : tempBag)
    {
        bag->addBack(j);
    }
}

void GameManager::populateFactories()
{
    if (bag->size() < (maxNumOfFactories * MAX_FACTORY_TILES))
    {
        TransferLidToBag();
    }
    for (int fNo = 0; fNo != maxNumOfFactories; ++fNo)
    {
        for (int noTiles = 0; noTiles != MAX_FACTORY_TILES; ++noTiles)
        {
            factories[fNo]->addTile(bag->get(0));
            bag->removeFront();
        }
    }
    discard->addTile(FIRST_PLAYER_TILE);
    if (numOfCFactory == TWO_CENTER_FACTORY)
    {
        discard2->addTile(FIRST_PLAYER_TILE);
    }
}

void GameManager::TransferLidToBag()
{
    for (unsigned int i = 0; i != boxLid->size() - 1; ++i)
    {
        bag->addBack(boxLid->get(i));
    }
    boxLid->clear();
}

void GameManager::info(string filename)
{
    ifstream file;
    file.open(filename);
    if (file.is_open())
    {
        string line;
        while (!file.eof())
        {
            getline(file, line);
            cout << line << endl;
        }
    }
    file.close();

    cout << "Press enter to return to the game." << endl;
    waitForEnter();
}

void GameManager::setNextPlayer(int playerIndex)
{
    players[playerIndex]->setPlayerTurn(false);
    playerIndex = (playerIndex + 1) % numOfPlayers;
    players[playerIndex]->setPlayerTurn(true);
}

void GameManager::saveGame(const string &filename)
{
    string path = SAVE_PATH + filename + FILE_EXTENSION;

    std::ofstream outfile;
    outfile.open(path);
    if (!outfile)
    {
        std::cerr << "Error: game could not be saved" << endl;
    }
    else
    {
        outfile << seed << endl;
        outfile << numOfPlayers << endl;
        outfile << maxNumOfFactories << endl;
        outfile << numOfCFactory << endl;

        outfile << findCurrentPlayer() << endl;

        for (int i = 0; i != numOfPlayers; ++i)
        {
            outfile << players[i]->getName() << endl;
            outfile << players[i]->getScore() << endl;
        }

        outfile << discard->toString() << endl;
        if (numOfCFactory == 2)
        {
            outfile << discard2->toString() << endl;
        }

        for (int i = 0; i != maxNumOfFactories; ++i)
        {
            outfile << factories[i]->toString() << endl;
        }

        for (int i = 0; i != numOfPlayers; i++)
        {
            outfile << players[i]->getStrings("storage") << endl;
            outfile << players[i]->getStrings("broken") << endl;
            outfile << players[i]->getStrings("mosaic") << endl;
        }

        outfile << boxLid->toString() << endl;
        outfile << bag->toString();

        outfile.close();
    }
}

string GameManager::displayColoured(string input)
{
    string out;
    for (int i = 0; i < input.length(); ++i)
    {
        if (input[i] == 'B')
        {
            out += BLUE;
            out += input[i];
            out += RESET;
        }
        else if (input[i] == 'R')
        {
            out += RED;
            out += input[i];
            out += RESET;
        }
        else if (input[i] == 'Y')
        {
            out += YELLOW;
            out += input[i];
            out += RESET;
        }
        else if (input[i] == 'U')
        {
            out += WHITE;
            out += input[i];
            out += RESET;
        }
        else if (input[i] == 'L')
        {
            out += CYAN;
            out += input[i];
            out += RESET;
        }
        else if (input[i] == FIRST_PLAYER_TILE)
        {
            out += input[i];
            out += RESET;
        }
    }
    return out;
}

int GameManager::findCurrentPlayer()
{
    for (int i = 0; i < numOfPlayers; ++i)
    {
        if (players[i]->isPlayersTurn())
        {
            return i;
        }
    }
    return -1;
}