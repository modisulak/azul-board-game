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
#define DEFAULT "DEFAULT"
#define FIRST_C_FACTORY_STR "10"
#define SECOND_C_FACTORY_STR "20"
#define BROKEN 6
#define TURN_ARGC 4
#define TURN_ARG2C 5
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
#define TWO_PLAYER_GAME 2
#define THREE_PLAYER_GAME 3
#define FOUR_PLAYER_GAME 4
#define TWO_CENTER_FACTORY 2
#define BOARD_SPACE 10
#define NAME_STRING_LENGTH 4
#define FIRST_C_FACTORY 10
#define SECOND_C_FACTORY 20
#define NORMAL_C_FACTORY 0
#define SPACE_OFFSET 4

#define RESET "\033[0m"
#define YELLOW "\u001b[33;1m"
#define BLUE "\u001b[34;1m"
#define WHITE "\u001b[37;1m"
#define CYAN "\u001b[36;1m"
#define RED "\u001b[31;1m"

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
