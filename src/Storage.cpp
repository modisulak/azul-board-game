#include "Storage.h"

Storage::Storage()
{
    for (int row = 0; row != MAX_BOARD_ROWS; ++row)
    {
        clearRow(row);
    }
}

Storage::Storage(const std::basic_string<char> &input) : Grid(input) {}

Storage::~Storage() = default;

bool Storage::isRowComplete(int row)
{
    int colMin = MAX_BOARD_COLS - (row + 1);
    return tiles[row][colMin] != EMPTY;
}

bool Storage::add(const Tile tile, const unsigned int row)
{
    bool success = false;
    int col = MAX_BOARD_COLS - 1;
    int colMin = MAX_BOARD_COLS - (row + 1);

    while (col >= colMin && tiles[row][col] != EMPTY)
    {
        --col;
    }
    if (col >= colMin)
    {
        setTile(row, col, tile);
        success = true;
    }

    return success;
}

void Storage::clearRow(int row)
{
    int minStorageCol = MAX_BOARD_COLS - row - 1;
    for (int col = 0; col != MAX_BOARD_COLS; ++col)
    {
        if (col >= minStorageCol)
        {
            tiles[row][col] = EMPTY;
        }
        else
        {
            tiles[row][col] = BLANK_SPACE;
        }
    }
}
