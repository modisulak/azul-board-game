#include "../include/GameManager.h"
#include "../include/Main.h"

void displayMenu();

void displayCredits();

int getSeed(int argc, char **argv);

bool getSaveFiles(std::vector<string> &saveFiles);

int main(int argc, char **argv) {
    unique_ptr<GameManager> manager;

    cout << "Welcome to Azul!" << endl;
    cout << "-------------------" << endl;

    bool gameExit = false;
    while (!gameExit) {
        int seed = getSeed(argc, argv);
        displayMenu();
        std::cout << INPUT_TAB;

        string input;
        cin >> input;

        if (cin.good()) {
            if (input == NEW_GAME) {
                string players[MAX_PLAYER_INSTANCES];
                for (auto &player : players) {
                    bool success = false;
                    cout << endl << "Enter player name: ";
                    cout << endl << INPUT_TAB;
                    while (!success) {
                        try {
                            cin >> player;
                            success = true;
                        }
                        catch (...) {
                            cout << "Selection is invalid. Please try again." << endl;
                        }
                    }
                }
                cout << endl << "Starting a new game..." << endl;
                manager = make_unique<GameManager>(players[0], players[1], seed);
                manager->playGame();
            } else if (input == LOAD_GAME) {
                int saveSelection;
                bool selection = false;
                std::vector<string> saveFiles;
                cout << endl;
                bool files = getSaveFiles(saveFiles);
                if (files) {
                    for (int i = 0; i < saveFiles.size(); i++) {
                        cout << i + 1 << ": " << saveFiles[i] << endl;
                    }
                    cout << endl << "Please select save file to load from list: " << endl << INPUT_TAB;
                    while (!selection) {
                        cin >> saveSelection;
                        if ((saveSelection <= 0) || (saveSelection >= saveFiles.size() + 1)) {
                            cout << "Selection is invalid. Please try again." << endl;
                        } else { selection = true; }
                    }
                    string filename = SAVE_PATH + saveFiles[saveSelection - 1];
                    cout << "Loading game from selection" << endl;
                    manager = make_unique<GameManager>(filename);
                    manager->playGame();
                } else {
                    cout << "There are no current save files available to choose from. Please start a new game" << endl;
                }
            } else if (input == CREDITS) {
                displayCredits();
            } else if (input == QUIT) {
                gameExit = true;
            } else {
                cout << "Selection is invalid. Please try again." << endl;
            }
        }
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
    if (file.is_open()) {
        while (!file.eof()) {
            string line;
            getline(file, line);
            cout << line << endl;
        }
        file.close();
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
            if ((strcmp(ent->d_name, str1) != 0) && (strcmp(ent->d_name, str2) != 0)) {
                files = true;
                saveFiles.emplace_back(ent->d_name);
            }
        }
    }
    closedir(directory);
    return files;
}