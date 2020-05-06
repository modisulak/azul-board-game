#include <GameManager.h>
#include "../include/main.h"

void displayMenu();

void displayCredits();

int main(int argc, char **argv) {


    string filename;
    int seed;
    for (int i = 0; i != argc; ++i) {
        if (argv[i] == SEED_FLAG){
            seed = std::stoi(argv[i+1]);
        } else if (argv[i] == FILENAME_FLAG){
            filename = argv[i+1];
        }
    }

    unique_ptr<GameManager> manager;

    cout << "Welcome to Azul!" << endl;
    cout << "-------------------" << endl;

    bool gameExit = false;
    while (!gameExit) {
        displayMenu();
        std::cout << "> ";

        string input;
        cin >> input;

        if (cin.good()) {
            if (input == NEW_GAME) {
                cout << "To-do" << endl;
                //TODO - get player names to pass to constructor
                manager = make_unique<GameManager>("","",seed);
                manager->playGame();
            } else if (input == LOAD_GAME) {
                cout << "To-do" << endl;
                manager = make_unique<GameManager>(filename);
                manager->playGame();

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