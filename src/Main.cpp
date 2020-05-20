#include "../include/Main.h"

void displayMenu();

void displayCredits();

int getSeed(int argc, char **argv);

bool getSaveFiles(std::vector<string> &saveFiles);

int main(int argc, char **argv) {
    unique_ptr<GameManager> manager;
    int seed = getSeed(argc, argv);
    cout << endl << "Welcome to Azul!" << endl;

    bool gameExit = false;
    while (!gameExit) {
        cout << "-------------------";
        displayMenu();
        std::cout << INPUT_TAB;

        int input = 0;
        cin >> input;
        cout << endl;
        if (input == NEW_GAME) {
            string players[MAX_PLAYER_INSTANCES];
            int i = 0;
            while (!cin.eof() && i != MAX_PLAYER_INSTANCES) {
                cout << "Enter player " << i + 1 << "'s name: " << endl;
                cout << INPUT_TAB;
                getline(cin, players[i]);
                transform(players[i].begin(), players[i].end(), players[i].begin(), ::toupper);
                ++i;
            }
            if (!cin.eof()) {
                if (players[0] == players[1]) {
                    cout << endl << "Players cannot have the same name" << endl;
                } else {
                    cout << endl << "Starting a new game..." << endl;
                    manager = make_unique<GameManager>(players[0], players[1], seed);
                    manager->playGame();
                }
            }
        } else if (input == LOAD_GAME) {
            string saveSelection;
            bool selection = false;
            std::vector<string> saveFiles;
            bool files = getSaveFiles(saveFiles);

            if (files) {
                for (auto &saveFile : saveFiles) {
                    cout << saveFile << endl;
                }
                cout << endl << "Please enter the name of the save file you wish to load: " << endl
                     << INPUT_TAB;
                cin >> saveSelection;
                // Transform to lower case
                transform(saveSelection.begin(), saveSelection.end(), saveSelection.begin(),
                          ::tolower);
                // Check if file exists
                for (auto &saveFile : saveFiles) {
                    if (saveFile == saveSelection) {
                        selection = true;
                    }
                }
                if (!selection) {
                    cout << endl << "There are no current files under that name." << endl << endl;
                } else {
                    string filename = SAVE_PATH + saveSelection;
                    cout << "Loading game from selection..." << endl;
                    manager = make_unique<GameManager>(filename);
                    manager->playGame();
                }
            } else {
                cout << "There are no save files available to choose from. Please start a new game"
                     << endl;
            }
        } else if (input == CREDITS) {
            displayCredits();
        } else if (input == QUIT || cin.eof()) {
            cout << endl << "Quitting Game...\nGoodbye" << endl;
            gameExit = true;
        } else {
            cout << "Selection is invalid. Please try again." << endl;
        }
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return EXIT_SUCCESS;
}

int getSeed(int argc, char **argv) {
    // Generate random seed
    std::random_device engine;
    int min = std::numeric_limits<int>::min();
    int max = std::numeric_limits<int>::max();

    std::uniform_int_distribution<int> uniform_dist(min, max);
    int seed = uniform_dist(engine);

    //Override seed with command line argument
    for (int i = 0; i != argc; ++i) {
        if (argv[i] == std::string(SEED_FLAG)) {
            seed = std::stoi(argv[i + 1]);
            cout << seed << endl;
        }
    }
    return seed;
}

void displayMenu() {
    cout << endl << "Menu" << endl;
    cout << "----" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Credits (Show Student Information)" << endl;
    cout << "4. Quit" << endl << endl;
}

void displayCredits() {
    string filename = "../resources/credits.txt";
    ifstream file;
    file.open(filename);
    cout << "-------------------------------------" << endl;
    if (!file.fail()) {
        if (file.is_open()) {
            while (!file.eof()) {
                string line;
                getline(file, line);
                cout << line << endl;
            }
            file.close();
        }
    } else {
        cout << "Credits data could not be found" << endl;
    }
    cout << "-------------------------------------" << endl;
}

bool getSaveFiles(std::vector<string> &saveFiles) {
    bool files = false;
    struct dirent *ent;
    DIR *directory = opendir(SAVE_PATH);

    if (directory != nullptr) {
        char str1[] = ".", str2[] = "..";
        while ((ent = readdir(directory)) != nullptr) {
            if ((strcmp(ent->d_name, "save_tests") != 0) && (strcmp(ent->d_name, str1) != 0) &&
                (strcmp(ent->d_name, str2) != 0)) {
                files = true;
                saveFiles.emplace_back(ent->d_name);
            }
        }
        closedir(directory);
    }
    return files;
}
