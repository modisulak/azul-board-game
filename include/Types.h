#ifndef APT_A2_TYPES_H
#define APT_A2_TYPES_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <utility>
#include <vector>
#include <algorithm>
#include <array>

#define BLANK_SPACE ' '
#define EMPTY '.'
#define FIRST_PLAYER_TILE 'F'
#define INPUT_TAB "> "
#define SAVE_PATH "save_files/"
#define FILE_EXTENSION ".txt"
#define TURN "TURN"
#define SAVE "SAVE"
#define HELP "HELP"
#define RULES "RULES"
#define EXIT "EXIT"
#define BROKEN "BROKEN"
#define TURN_ARGC 4
#define SAVE_ARGC 2
#define MAX_FACTORY_TILES 4
#define MAX_FACTORY_INSTANCES_2 5
#define MAX_FACTORY_INSTANCES_3 7
#define MAX_FACTORY_INSTANCES_4 9
#define MAX_DISCARD_TILES 17
#define MAX_TOTAL_TILES 100
#define MAX_AMOUNT_COLOUR 20
#define MAX_PLAYER_INSTANCES_2 2
#define MAX_PLAYER_INSTANCES_3 3
#define MAX_PLAYER_INSTANCES_4 4
#define MAX_BROKEN_TILES 7
#define MAX_BOARD_ROWS 5
#define MAX_BOARD_COLS 5

#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define WHITE "\033[37m"
#define CYAN "\033[36m"
#define RED "\033[31m"

typedef char Tile;

using std::cin;
using std::cout;
using std::endl;

using std::getline;
using std::ifstream;
using std::string;

using std::make_shared;
using std::make_unique;
using std::move;
using std::shared_ptr;
using std::unique_ptr;

#endif //APT_A2_TYPES_H
