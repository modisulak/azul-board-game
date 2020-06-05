#include "Utils.h"

void waitForEnter();

bool Utils::totalOrdering(Tile x, Tile y)
{
    std::vector<Tile> tiles = {FIRST_PLAYER_TILE, 'R', 'Y', 'B', 'L', 'U', BLANK_SPACE};

    unsigned int xPos = 0;
    while (xPos != tiles.size() && x != tiles[xPos])
    {
        ++xPos;
    }
    unsigned int yPos = 0;
    while (yPos != tiles.size() && y != tiles[yPos])
    {
        ++yPos;
    }

    return xPos < yPos;
}

void Utils::info(string filename)
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

void waitForEnter()
{
    cout << INPUT_TAB;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}