#ifndef APT_A2_TYPES_H
#define APT_A2_TYPES_H

#include <iostream>
#include <string>
#include <fstream>
#include <memory>

#define BLANK_SPACE             ' '
#define EMPTY                   '.'
#define MAX_FACTORY_TILES       4
#define MAX_FACTORY_INSTANCES   5
#define MAX_DISCARD_TILES       25
#define MAX_TOTAL_TILES         100
#define MAX_AMOUNT_COLOUR       20
#define MAX_PLAYER_INSTANCES    2


typedef char Tile;

using std::string;
using std::endl;
using std::ifstream;

using std::move;
using std::shared_ptr;
using std::make_shared;


#endif //APT_A2_TYPES_H
