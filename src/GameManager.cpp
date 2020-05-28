#include "../include/GameManager.h"

GameManager::GameManager(string p1, string p2, string p3, string p4, int seed, int numofplayers) : seed(seed)
{
    engine.seed(seed);
    numOfPlayers = numofplayers;

    string pl;
    if (numOfPlayers == 2)
    {
        string pl[MAX_PLAYER_INSTANCES_2] = {move(p1), move(p2)};
        players = make_unique<unique_ptr<Player>[]>(numOfPlayers);
        for (int i = 0; i != numOfPlayers; ++i)
        {
            players[i] = make_unique<Player>(pl[i], 0);
        }
        maxNumOfFactories = 4;
    }
    else if (numOfPlayers == 3)
    {
        string pl[MAX_PLAYER_INSTANCES_3] = {move(p1), move(p2), move(p3)};
        players = make_unique<unique_ptr<Player>[]>(numOfPlayers);
        for (int i = 0; i != numOfPlayers; ++i)
        {
            players[i] = make_unique<Player>(pl[i], 0);
        }
        maxNumOfFactories = 7;
    }
    else if (numOfPlayers == 4)
    {
        string pl[MAX_PLAYER_INSTANCES_4] = {move(p1), move(p2), move(p3), move(p4)};
        players = make_unique<unique_ptr<Player>[]>(numOfPlayers);
        for (int i = 0; i != numOfPlayers; ++i)
        {
            players[i] = make_unique<Player>(pl[i], 0);
        }
        maxNumOfFactories = 9;
    }

    setFirstTurn();

    discard = make_unique<Factory>(MAX_DISCARD_TILES);
    bag = make_unique<LinkedList>();
    boxLid = make_unique<LinkedList>();

    populateBag();

    //CHANGE HERE CHECK FOR THE FACTORIES:
    if (numOfPlayers == 2)
    {
        factories = make_unique<unique_ptr<Factory>[]>(maxNumOfFactories);
        for (int i = 0; i != maxNumOfFactories; ++i)
        {
            factories[i] = make_unique<Factory>(MAX_FACTORY_TILES);
        }
    }
    else if (numOfPlayers == 3)
    {
        factories = make_unique<unique_ptr<Factory>[]>(maxNumOfFactories);
        for (int i = 0; i != maxNumOfFactories; ++i)
        {
            factories[i] = make_unique<Factory>(MAX_FACTORY_TILES);
        }
    }
    else if (numOfPlayers == 4)
    {
        factories = make_unique<unique_ptr<Factory>[]>(maxNumOfFactories);
        for (int i = 0; i != maxNumOfFactories; ++i)
        {
            factories[i] = make_unique<Factory>(MAX_FACTORY_TILES);
        }
    }

    populateFactories();
}

GameManager::GameManager(const string &filename)
{
    players = make_unique<unique_ptr<Player>[]>(numOfPlayers);
    //CHANGE
    if (numOfPlayers == 2)
    {
        factories = make_unique<unique_ptr<Factory>[]>(maxNumOfFactories);
    }
    else if (numOfPlayers == 3)
    {
        factories = make_unique<unique_ptr<Factory>[]>(maxNumOfFactories);
    }
    else if (numOfPlayers == 4)
    {
        factories = make_unique<unique_ptr<Factory>[]>(maxNumOfFactories);
    }

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
        bool p1Turn = false;
        if (line == "1")
        {
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

        if (discardAsString.length() > MAX_DISCARD_TILES)
        {
            throw std::invalid_argument("Discard invalid.");
        }
        discard = make_unique<Factory>(MAX_DISCARD_TILES, discardAsString);

        for (int i = 0; i != maxNumOfFactories; ++i)
        {
            string factoryAsString;
            getline(file, factoryAsString);
            if (factoryAsString.length() > MAX_FACTORY_TILES)
            {
                throw std::invalid_argument("Factory invalid.");
            }
            factories[i] = make_unique<Factory>(MAX_FACTORY_TILES, factoryAsString);
        }

        string p1storageAsString;
        for (int i = 0; i != MAX_BOARD_ROWS; ++i)
        {
            int blankSpaces = MAX_BOARD_COLS - i - 1;
            for (int j = 0; j < blankSpaces; ++j)
            {
                p1storageAsString += BLANK_SPACE;
            }
            getline(file, line);

            p1storageAsString += line;
        }
        if (p1storageAsString.length() != MAX_BOARD_ROWS * MAX_BOARD_COLS)
        {
            throw std::invalid_argument("Player 1 Storage invalid.");
        }

        string p1BrokenAsString;
        getline(file, p1BrokenAsString);
        if (p1BrokenAsString.length() > MAX_BROKEN_TILES)
        {
            throw std::invalid_argument("Player 1 Broken invalid.");
        }

        string p1MosaicAsString;
        getline(file, p1MosaicAsString);
        if (p1MosaicAsString.length() != MAX_BOARD_ROWS * MAX_BOARD_COLS)
        {
            throw std::invalid_argument("Player 1 Mosaic invalid.");
        }

        string p2storageAsString;
        for (int i = 0; i != MAX_BOARD_ROWS; ++i)
        {
            int blankSpaces = MAX_BOARD_COLS - i - 1;
            for (int j = 0; j < blankSpaces; ++j)
            {
                p2storageAsString += BLANK_SPACE;
            }
            getline(file, line);
            p2storageAsString += line;
        }
        if (p2storageAsString.length() != MAX_BOARD_ROWS * MAX_BOARD_COLS)
        {
            throw std::invalid_argument("Player 2 Storage invalid.");
        }
        string p2BrokenAsString;
        getline(file, p2BrokenAsString);
        if (p1BrokenAsString.length() > MAX_BROKEN_TILES)
        {
            throw std::invalid_argument("Player 2 Broken invalid.");
        }

        string p2MosaicAsString;
        getline(file, p2MosaicAsString);
        if (p2MosaicAsString.length() != MAX_BOARD_ROWS * MAX_BOARD_COLS)
        {
            throw std::invalid_argument("Player 2 Mosaic invalid.");
        }

        players[0] = make_unique<Player>(player1Name, player1Score,
                                         p1storageAsString, p1MosaicAsString,
                                         p1BrokenAsString, p1Turn);
        players[1] = make_unique<Player>(player2Name, player2Score,
                                         p2storageAsString, p2MosaicAsString,
                                         p2BrokenAsString, !p1Turn);

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
    shared_ptr<Board> p1Board = players[0]->getBoard();
    shared_ptr<Board> p2Board = players[1]->getBoard();
    shared_ptr<Board> p3Board = NULL;
    shared_ptr<Board> p4Board = NULL;
    if (numOfPlayers > 2 && numOfPlayers < 4)
    {
        p3Board = players[2]->getBoard();
    }
    if (numOfPlayers == 4)
    {
        p4Board = players[3]->getBoard();
    }

    cout << endl
         << "Let's Play!" << endl;

    while (!p1Board->getMosaic()->isAnyRowComplete() && !p2Board->getMosaic()->isAnyRowComplete())
    {
        playRound();
        endOfRound(p1Board, p2Board, p3Board, p4Board);
        prepareNextRound(p1Board, p2Board, p3Board, p4Board);
    }

    addEndOfGamePoints(p1Board, p2Board, p3Board, p4Board);

    cout << endl
         << "Final Scores:" << endl;
    for (int i = 0; i < numOfPlayers; ++i)
    {
        cout << players[i]->getName() << ": " << players[i]->getScore() << endl;
    }

    string winner = "The winner is: ";

    getWinner(p1Board, p2Board, p3Board, p4Board, winner);

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

void GameManager::getWinner(const shared_ptr<Board> &p1Board, const shared_ptr<Board> &p2Board,
                            const shared_ptr<Board> &p3Board, const shared_ptr<Board> &p4Board,
                            string &winner) const
{

    if (players[0]->getScore() > players[1]->getScore() && players[2]->getScore() && players[3]->getScore())
    {
        winner += players[0]->getName();
    }
    else if (players[1]->getScore() > players[0]->getScore() && players[2]->getScore() && players[3]->getScore())
    {
        winner += players[1]->getName();
    }
    else if (players[2]->getScore() > players[0]->getScore() && players[1]->getScore() && players[3]->getScore())
    {
        winner += players[2]->getName();
    }
    else if (players[3]->getScore() > players[0]->getScore() && players[2]->getScore() && players[1]->getScore())
    {
        winner += players[3]->getName();
    }
    else
    {
        int p1CompletedRows = 0;
        int p2CompletedRows = 0;
        int p3CompletedRows = 0;
        int p4CompletedRows = 0;
        for (int i = 0; i != MAX_BOARD_ROWS; ++i)
        {
            p1CompletedRows += p1Board->getMosaic()->isRowComplete(i);
            p2CompletedRows += p2Board->getMosaic()->isRowComplete(i);
            if (p3Board != NULL)
            {
                p3CompletedRows += p3Board->getMosaic()->isRowComplete(i);
            }
            if (p4Board != NULL)
            {
                p4CompletedRows += p4Board->getMosaic()->isRowComplete(i);
            }
        }
        if (p1CompletedRows > p2CompletedRows > p3CompletedRows > p4CompletedRows)
        {
            winner += players[0]->getName();
        }
        else if (p2CompletedRows > p1CompletedRows > p3CompletedRows > p4CompletedRows)
        {
            winner += players[1]->getName();
        }
        else if (p3CompletedRows > p1CompletedRows > p2CompletedRows > p4CompletedRows)
        {
            winner += players[2]->getName();
        }
        else if (p4CompletedRows > p1CompletedRows > p3CompletedRows > p2CompletedRows)
        {
            winner += players[3]->getName();
        }
        else
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
            if (inputs.size() == TURN_ARGC)
            {
                bool success = playTurn(inputs, playerIndex);
                if (success)
                {
                    roundEnd = isRoundEnd();
                    for (int i = 0; i < numOfPlayers; ++i)
                    {
                        players[i]->setPlayerTurn(!players[i]->isPlayersTurn());
                    }
                    message = "Turn successful.";
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
            info(HELP_FILE);
            message = "";
        }
        else if (command == RULES)
        {
            cout << endl;
            info(RULES_FILE);
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

void GameManager::endOfRound(shared_ptr<Board> &p1Board, shared_ptr<Board> &p2Board, shared_ptr<Board> &p3Board, shared_ptr<Board> &p4Board) const
{
    cout << endl
         << "=== END OF ROUND ===" << endl;

    unsigned int p1Points = 0;
    unsigned int p2Points = 0;
    unsigned int p3Points = 0;
    unsigned int p4Points = 0;
    unsigned int playerpoints[4];
    // Update mosaic and get score for newly placed tiles
    for (int row = 0; row != MAX_BOARD_ROWS; ++row)
    {
        // Ensure storage row is full of tiles
        if (p1Board->getStorage()->isRowComplete(row))
        {
            playerpoints[0] += tileMosaic(p1Board, row);
        }
        if (p2Board->getStorage()->isRowComplete(row))
        {
            playerpoints[1] += tileMosaic(p2Board, row);
        }
        if (p3Board != NULL && p3Board->getStorage()->isRowComplete(row))
        {
            playerpoints[2] += tileMosaic(p3Board, row);
        }
        if (p4Board != NULL && p4Board->getStorage()->isRowComplete(row))
        {
            playerpoints[3] += tileMosaic(p4Board, row);
        }
    }

    // remove lost points for broken tiles
    playerpoints[0] -= p1Board->getBroken()->lostPoints();
    playerpoints[1] -= p2Board->getBroken()->lostPoints();
    if (p3Board != NULL)
    {
        playerpoints[2] -= p3Board->getBroken()->lostPoints();
    }
    if (p4Board != NULL)
    {
        playerpoints[3] -= p4Board->getBroken()->lostPoints();
    }

    // Update players score
    players[0]->setScore(players[0]->getScore() + playerpoints[0]);
    players[1]->setScore(players[1]->getScore() + playerpoints[1]);
    if (p3Board != NULL)
    {
        players[2]->setScore(players[2]->getScore() + playerpoints[2]);
    }
    if (p3Board != NULL)
    {
        players[3]->setScore(players[3]->getScore() + playerpoints[3]);
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

void GameManager::prepareNextRound(const shared_ptr<Board> &p1Board, const shared_ptr<Board> &p2Board,
                                   const shared_ptr<Board> &p3Board, const shared_ptr<Board> &p4Board)
{
    // Add broken tiles to back of the box lid
    bool p1FirstTurn = processBroken(p1Board);
    bool p2FirstTurn = processBroken(p2Board);
    bool p3FirstTurn;
    bool p4FirstTurn;
    if (p3Board != NULL)
    {
        p3FirstTurn = processBroken(p3Board);
    }
    if (p4Board != NULL)
    {
        p4FirstTurn = processBroken(p4Board);
    }

    //Update players turn depending who had the First player Tile
    players[0]->setPlayerTurn(p1FirstTurn);
    players[1]->setPlayerTurn(p2FirstTurn);
    if (p3Board != NULL)
    {
        players[2]->setPlayerTurn(p3FirstTurn);
    }
    if (p4Board != NULL)
    {
        players[3]->setPlayerTurn(p4FirstTurn);
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

    cout << endl
         << "Factories: " << endl
         << "0: ";
    cout << discard->toString() << endl;

    int numOfFactories = 0;
    if (numOfPlayers == 2)
    {
        numOfFactories = maxNumOfFactories;
    }
    else if (numOfPlayers == 3)
    {
        numOfFactories = maxNumOfFactories;
    }
    else if (numOfPlayers == 4)
    {
        numOfFactories = maxNumOfFactories;
    }

    for (int i = 0; i < numOfFactories; ++i)
    {
        cout << i + 1 << ": ";
        cout << factories[i]->toString() << endl;
    }

    for (int i = 0; i < numOfPlayers; ++i)
    {
        cout << endl
             << "Mosaic for " << players[i]->getName() << ":" << endl;

        cout << players[i]->getBoard()->toString() << endl;
    }

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
        bool isDiscard = true;
        if (factoryNumber != 0)
        {
            factoryNumber -= 1;
            isDiscard = false;
        }

        if (tile != FIRST_PLAYER_TILE)
        {
            unsigned int noOfTiles = isDiscard ? discard->getTilesOfSameColour(tile)
                                               : factories[factoryNumber]->getTilesOfSameColour(tile);
            if (noOfTiles > 0)
            {
                success = addTiles(inputs[3], playerIndex, tile, noOfTiles);
                if (success)
                {
                    removePlayedTiles(playerIndex, factoryNumber, isDiscard, tile);
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
        if (factoryNumber >= 0 && factoryNumber <= maxNumOfFactories)
        {
            // Validate destination selection
            if (!inputs[3].empty() && isANumber(inputs[3]))
            {
                int destination = std::stoi(inputs[3]);
                if (destination >= 0 && destination <= MAX_BOARD_ROWS)
                {
                    valid = true;
                }
            }
            else if (inputs[3] == BROKEN)
            {
                valid = true;
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
    else if (destination == BROKEN)
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
    return success;
}

void GameManager::removePlayedTiles(int playerIndex, int factoryNumber, bool isDiscard, Tile tile) const
{
    if (isDiscard)
    {
        if (discard->contains(FIRST_PLAYER_TILE))
        {
            players[playerIndex]->getBoard()->getBroken()->add(FIRST_PLAYER_TILE);
            discard->removeTile(FIRST_PLAYER_TILE);
        }
        for (unsigned int i = 0; i != discard->getSize(); ++i)
        {
            if (discard->getTile(i) == tile)
            {
                discard->removeTile(i);
            }
        }
        discard->sortTiles();
    }
    else
    {
        for (unsigned int i = 0; i != factories[factoryNumber]->getSize(); ++i)
        {
            if (factories[factoryNumber]->getTile(i) != tile)
            {
                discard->addTile(factories[factoryNumber]->getTile(i));
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
    while (i != numOfPlayers && factories[i]->isEmpty())
    {
        ++i;
    }
    roundEnd = discard->isEmpty() && i == maxNumOfFactories;
    return roundEnd;
}

void GameManager::addEndOfGamePoints(const shared_ptr<Board> &p1Board, const shared_ptr<Board> &p2Board,
                                     const shared_ptr<Board> &p3Board, const shared_ptr<Board> &p4Board)
{
    //Tally end of game points //TODO MAKE 2D ARRAY
    int p1CompletedRows = 0;
    int p1CompletedCols = 0;
    int p2CompletedRows = 0;
    int p2CompletedCols = 0;
    int p3CompletedRows = 0;
    int p3CompletedCols = 0;
    int p4CompletedRows = 0;
    int p4CompletedCols = 0;

    for (int i = 0; i != MAX_BOARD_ROWS; ++i)
    {
        p1CompletedRows += p1Board->getMosaic()->isRowComplete(i);
        p1CompletedCols += p1Board->getMosaic()->isColumnComplete(i);
        p2CompletedRows += p2Board->getMosaic()->isRowComplete(i);
        p2CompletedCols += p2Board->getMosaic()->isColumnComplete(i);
        if (p3Board != NULL)
        {
            p3CompletedRows += p3Board->getMosaic()->isRowComplete(i);
            p3CompletedCols += p3Board->getMosaic()->isColumnComplete(i);
        }
        if (p4Board != NULL)
        {
            p4CompletedRows += p4Board->getMosaic()->isRowComplete(i);
            p4CompletedCols += p4Board->getMosaic()->isColumnComplete(i);
        }
    }

    // Find how many tiles the mosaic contains all 5 completed for
    int p1TileColourComplete = p1Board->getMosaic()->numberOfTilesCompleted();
    int p2TileColourComplete = p2Board->getMosaic()->numberOfTilesCompleted();
    int p3TileColourComplete;
    int p4TileColourComplete;
    if (p3Board != NULL)
    {
        p3TileColourComplete = p3Board->getMosaic()->numberOfTilesCompleted();
    }
    if (p4Board != NULL)
    {
        p4TileColourComplete = p4Board->getMosaic()->numberOfTilesCompleted();
    }

    // Update players score
    players[0]->setScore(players[0]->getScore() + (p1CompletedRows * ROW_COMPLETE_POINTS) +
                         (p1CompletedCols * COL_COMPLETE_POINTS) +
                         (p1TileColourComplete * TILE_COMPLETE_POINTS));
    players[1]->setScore(players[1]->getScore() + (p2CompletedRows * ROW_COMPLETE_POINTS) +
                         (p2CompletedCols * COL_COMPLETE_POINTS) +
                         (p2TileColourComplete * TILE_COMPLETE_POINTS));
    if (p3Board != NULL)
    {
        players[2]->setScore(players[2]->getScore() + (p3CompletedRows * ROW_COMPLETE_POINTS) +
                             (p3CompletedCols * COL_COMPLETE_POINTS) +
                             (p3TileColourComplete * TILE_COMPLETE_POINTS));
    }
    if (p4Board != NULL)
    {
        players[3]->setScore(players[3]->getScore() + (p4CompletedRows * ROW_COMPLETE_POINTS) +
                             (p4CompletedCols * COL_COMPLETE_POINTS) +
                             (p4TileColourComplete * TILE_COMPLETE_POINTS));
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
        outfile << players[0]->isPlayersTurn() << endl;

        for (int i = 0; i != numOfPlayers; ++i)
        {
            outfile << players[i]->getName() << endl;
            outfile << players[i]->getScore() << endl;
        }

        outfile << discard->toString() << endl;

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