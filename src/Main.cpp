#include "../include/Main.h"

void displayMenu();

void displayCredits();

int getSeed(int argc, char **argv);

bool getSaveFiles(std::vector<string> &saveFiles);

bool checkEqual(std::vector<string> &players, int numofplayers);

bool validatePlayers(int numofplayers);

bool validateCFactory(int numofCFactory);

int main(int argc, char **argv)
{
    unique_ptr<GameManager> manager;
    int seed = getSeed(argc, argv);
    cout << endl
         << "Welcome to Azul!" << endl;

    bool gameExit = false;
    while (!gameExit)
    {
        cout << "-------------------";
        displayMenu();
        std::cout << INPUT_TAB;

        int input = 0;
        string inputStr = "";
        cin >> inputStr;
        transform(inputStr.begin(), inputStr.end(), inputStr.begin(), ::toupper);
        if (inputStr != "HELP")
        {
            try
            {
                input = std::stoi(inputStr);
            }
            catch (const std::exception)
            {
                cout << "Selection is invalid. Please try again." << endl;
            }
        }
        cout << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (input == NEW_GAME)
        {

            int numofplayers = 0;
            do
            {
                cout << "Number of Players: ";
                std::cout << INPUT_TAB;
                cin >> numofplayers;
                cout << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } while (!validatePlayers(numofplayers));

            int numofcfactory = 0;
            do
            {
                cout << "Number of Center Factories: ";
                std::cout << INPUT_TAB;
                cin >> numofcfactory;
                cout << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } while (!validateCFactory(numofcfactory));

            std::vector<string> players;
            players.reserve(numofplayers);

            for (int i = 0; i < numofplayers; ++i)
            {
                cout << "Enter player " << i + 1 << "'s name: " << endl;
                cout << INPUT_TAB;
                string line;
                getline(cin, line);
                players.push_back(line);
                transform(players.at(i).begin(), players.at(i).end(), players.at(i).begin(), ::toupper);
            }

            if (!cin.eof())
            {
                if (checkEqual(players, numofplayers))
                {
                    cout << endl
                         << "Players cannot have the same name" << endl;
                }
                else
                {
                    cout << endl
                         << "Starting a new game..." << endl;

                    manager = make_unique<GameManager>(players, seed, numofplayers, numofcfactory);

                    manager->playGame();
                }
            }
        }
        else if (input == LOAD_GAME)
        {
            string saveSelection;
            bool selection = false;
            std::vector<string> saveFiles;
            bool files = getSaveFiles(saveFiles);

            if (files)
            {
                std::sort(saveFiles.begin(), saveFiles.end());
                for (auto &saveFile : saveFiles)
                {
                    cout << saveFile << endl;
                }
                cout << endl
                     << "Please enter the name of the save file you wish to load: " << endl
                     << INPUT_TAB;
                cin >> saveSelection;
                // Check if file exists
                for (auto &saveFile : saveFiles)
                {
                    if (saveFile == saveSelection)
                    {
                        selection = true;
                    }
                }
                if (!selection)
                {
                    cout << endl
                         << "There are no current files under that name." << endl
                         << endl;
                }
                else
                {
                    string filename = SAVE_PATH + saveSelection;
                    cout << "Loading game from selection..." << endl;
                    try
                    {
                        manager = make_unique<GameManager>(filename);
                        manager->playGame();
                    }
                    catch (const std::exception &e)
                    {
                        std::cout << endl
                                  << "Incorrect game file format. Try again." << endl;

                        std::cerr << e.what();
                    }
                }
            }
            else
            {
                cout << "There are no save files available to choose from. Please start a new game"
                     << endl;
            }
        }
        else if (input == CREDITS)
        {
            displayCredits();
        }
        else if (input == QUIT || cin.eof())
        {
            cout << endl
                 << "Quitting Game...\nGoodbye" << endl;
            gameExit = true;
        }
        else if (inputStr == "HELP")
        {
            string message;
            cout << endl;
            Utils::info(HELP_MENU);
            message = "";
            cout << message << endl;
        }
    }
    return EXIT_SUCCESS;
}

int getSeed(int argc, char **argv)
{
    // Generate random seed
    std::random_device engine;
    int min = std::numeric_limits<int>::min();
    int max = std::numeric_limits<int>::max();

    std::uniform_int_distribution<int> uniform_dist(min, max);
    int seed = uniform_dist(engine);

    //Override seed with command line argument
    for (int i = 0; i != argc; ++i)
    {
        if (argv[i] == std::string(SEED_FLAG))
        {
            seed = std::stoi(argv[i + 1]);
        }
    }
    return seed;
}

void displayMenu()
{
    cout << endl
         << "Menu" << endl;
    cout << "----" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Credits (Show Student Information)" << endl;
    cout << "4. Quit" << endl
         << endl;
}

void displayCredits()
{
    string filename = CREDITS_PATH;
    ifstream file;
    file.open(filename);
    cout << "-------------------------------------" << endl;
    if (!file.fail())
    {
        if (file.is_open())
        {
            while (!file.eof())
            {
                string line;
                getline(file, line);
                cout << line << endl;
            }
            file.close();
        }
    }
    else
    {
        cout << "Credits data could not be found" << endl;
    }
    cout << "-------------------------------------" << endl;
}

bool getSaveFiles(std::vector<string> &saveFiles)
{
    bool files = false;
    struct dirent *ent;
    DIR *directory = opendir(SAVE_PATH);

    if (directory != nullptr)
    {
        char str1[] = ".", str2[] = "..";
        while ((ent = readdir(directory)) != nullptr)
        {
            if ((strcmp(ent->d_name, "save_tests") != 0) && (strcmp(ent->d_name, str1) != 0) &&
                (strcmp(ent->d_name, str2) != 0))
            {
                files = true;
                saveFiles.emplace_back(ent->d_name);
            }
        }
        closedir(directory);
    }
    return files;
}

bool checkEqual(std::vector<string> &players, int numofplayers)
{
    for (int i = 0; i < numofplayers; i++)
    {
        for (int j = 0; j < numofplayers; ++j)
        {
            if (players.at(i) == players.at(j) && i != j)
            {
                return true;
            }
        }
    }
    return false;
}

bool validatePlayers(int numofplayers)
{
    if (numofplayers >= 2 && numofplayers <= 4)
    {
        return true;
    }
    cout << "Invalid number of Player. Must be between 2 and 4" << endl;
    return false;
}

bool validateCFactory(int numofCFactory)
{
    if (numofCFactory >= 1 && numofCFactory <= 2)
    {
        return true;
    }
    cout << "Invalid number of Center Factory. Must be either 1 or 2" << endl;
    return false;
}
