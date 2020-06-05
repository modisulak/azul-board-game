#include "Mosaic.h"

Mosaic::Mosaic()
{
    string defaultMosaic = DEFAULT_MOSAIC;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row)
    {
        for (int col = 0; col != MAX_BOARD_COLS; ++col)
        {
            tiles[row][col] = defaultMosaic[col];
        }
        shiftMosaic(defaultMosaic);
    }
}

Mosaic::Mosaic(const std::basic_string<char> &input) : Grid(input) {}

Mosaic::~Mosaic() = default;

void Mosaic::shiftMosaic(string &mosaicRow)
{
    if (!mosaicRow.empty())
    {
        char temp = mosaicRow.at(mosaicRow.size() - 1);
        for (unsigned int i = mosaicRow.size() - 1; i != 0; --i)
        {
            mosaicRow.at(i) = mosaicRow.at(i - 1);
        }
        mosaicRow.at(0) = temp;
    }
}

int Mosaic::add(Tile tile, int row)
{
    Tile location = std::tolower(tile);
    int col = 0;
    // Find location in mosaic for current storage row's colour
    while (col != MAX_BOARD_COLS && tiles[row][col] != location)
    {
        ++col;
    }
    // Update mosaic
    setTile(row, col, tile);
    return col;
}

int Mosaic::getPoints(int row, int col)
{
    //Get points horizontally and vertically (all 4 axis)
    int horizontalPoints = getPoints(row + INCREMENT, col, INCREMENT, 0);
    horizontalPoints += getPoints(row + DECREMENT, col, DECREMENT, 0);
    int verticalPoints = getPoints(row, col + INCREMENT, 0, INCREMENT);
    verticalPoints += getPoints(row, col + DECREMENT, 0, DECREMENT);

    // Score a point for placing a tile + adjacent tiles
    int points = 1 + horizontalPoints + verticalPoints;

    // If points are scored in both directions, add an extra point
    points += (horizontalPoints > 0 && verticalPoints > 0);
    return points;
}

int Mosaic::getPoints(int row, int col, int rowOffset, int colOffset)
{
    int points = 0;
    if (row == MAX_BOARD_ROWS || row < 0 || col == MAX_BOARD_COLS || col < 0)
    {
        points = 0;
    }
    else if (tiles[row][col] == toupper(tiles[row][col]))
    {
        points = 1 + getPoints(row + rowOffset, col + colOffset, rowOffset, colOffset);
    }

    return points;
}

bool Mosaic::isAnyRowComplete() const
{
    bool complete = false;
    int row = 0;
    while (row != MAX_BOARD_ROWS && !complete)
    {
        complete = isRowComplete(row);
        ++row;
    }
    return complete;
}

bool Mosaic::isRowComplete(int row) const
{
    bool complete = false;
    int col = 0;
    // Check each column of row to ensure it is not Uppercase
    while (col != MAX_BOARD_COLS && isupper(tiles[row][col]))
    {
        ++col;
    }
    // If every column was uppercase, set finished to true
    if (col == MAX_BOARD_COLS)
    {
        complete = true;
    }
    return complete;
}

bool Mosaic::isColumnComplete(int col) const
{
    bool complete = false;
    int row = 0;
    // Check each row of column to ensure it is Uppercase
    while (row != MAX_BOARD_ROWS && isupper(tiles[row][col]))
    {
        ++row;
    }
    // If every row was uppercase, set finished to true
    if (row == MAX_BOARD_ROWS)
    {
        complete = true;
    }
    return complete;
}

int Mosaic::numberOfTilesCompleted()
{
    std::array<Tile, 5> array = {'R', 'Y', 'B', 'L', 'U'};
    int completed = 0;

    for (int tile = 0; tile != array.size(); ++tile)
    {
        int count = 0;
        int row = 0;

        while (row != MAX_BOARD_ROWS && row == count)
        {
            int col = 0;
            while (col != MAX_BOARD_COLS && row == count)
            {
                if (tiles[row][col] == array[tile])
                {
                    ++count;
                }
                ++col;
            }
            ++row;
        }
        completed += count == MAX_BOARD_ROWS;
    }

    return completed;
}
