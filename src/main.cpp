#include "../include/main.h"

using std::cout; 
using std::cin; 
using std::endl;
using std::string;
using std::ifstream;

void displayMenu(); 
void displayCredits();

const string filename = "credits.txt";

int input; 

bool gameExit = false;

int main(int argc, char** argv) {
    cout << "Welcome to Azul!" << endl;
    cout << "-------------------" << endl << endl;
    
    while (gameExit != true) {
        displayMenu();
        std::cout << "> ";
        cin >> input; 
        
        switch(input) { 
            case 1: 
                cout << "To-do" << endl;
                break;
            case 2: 
                cout << "To-do" << endl;
                break;
            case 3: 
                 displayCredits();
                 break;
            case 4: 
                gameExit = true;  
                break;   
        }
        
    }

    return EXIT_SUCCESS; 
    
}

void displayMenu() { 
     cout << "\n";
     cout << "Menu" << endl;
     cout << "----" << endl;
     cout << "1. New Game" << endl;
     cout << "2. Load Game" << endl;
     cout << "3. Credits (Show Student Information" << endl;
     cout << "4. Quit" << endl << endl;
}

void displayCredits() { 
    string line;
    ifstream file(filename); 
    cout << "------------------------------------" << endl; 
     if(file.is_open()) {
        while(!file.eof()) {
            getline(file,line);
            cout << line << endl;
            
             }
        file.close();
    }
    cout << "-------------------------------------" << endl; 
}