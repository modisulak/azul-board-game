#include "../include/Board.h"

Board::Board()
{
    storage = make_unique<Storage>();
    mosaic = make_unique<Mosaic>();
    broken = make_shared<Broken>();
}

Board::Board(const string &storageInput, const string &mosaicInput, const string &brokenInput)
{
    storage = make_unique<Storage>(storageInput);
    mosaic = make_unique<Mosaic>(mosaicInput);
    broken = make_shared<Broken>(brokenInput);
}

Board::~Board() = default;

const unique_ptr<Storage> &Board::getStorage() const
{
    return storage;
}

const unique_ptr<Mosaic> &Board::getMosaic() const
{
    return mosaic;
}

const shared_ptr<Broken> &Board::getBroken() const
{
    return broken;
}

bool Board::validateMove(const Tile tile, const unsigned int row) const
{
    bool success = false;

    // Ensure the mosaic doesn't already contain tile colour
    int col = 0;
    while (col != MAX_BOARD_COLS && mosaic->getTile(row, col) != tile)
    {
        ++col;
    }
    if (col == MAX_BOARD_COLS)
    {
        int colMin = MAX_BOARD_COLS - (row + 1);

        // Ensure storage row isn't full of tiles
        bool spaceAvailable = storage->getTile(row, colMin) == EMPTY;

        if (spaceAvailable)
        {
            Tile firstTile = storage->getTile(row, col - 1);
            // Ensure row will accept tile colour
            success = firstTile == tile || firstTile == EMPTY;
        }
    }
    return success;
}

string Board::toString() const
{

    string boardToString;
    for (int row = 0; row != MAX_BOARD_ROWS; ++row)
    {
        boardToString += std::to_string(row + 1);
        boardToString += ": ";
        for (int col = 0; col != MAX_BOARD_COLS; ++col)
        {
            boardToString += storage->getTile(row, col);
            boardToString += " ";
        }
        boardToString += "☰"; //RIGHTO
        for (int col = 0; col != MAX_BOARD_COLS; ++col)
        {
            boardToString += " ";
            if (mosaic->getTile(row, col) == 'b')

            {
                boardToString += BLUE;
                boardToString += mosaic->getTile(row, col);
                boardToString += RESET;
            }
            else if (mosaic->getTile(row, col) == 'y')
            {
                boardToString += YELLOW;
                boardToString += mosaic->getTile(row, col);
                boardToString += RESET;
            }
            else if (mosaic->getTile(row, col) == 'r')
            {
                boardToString += RED;
                boardToString += mosaic->getTile(row, col);
                boardToString += RESET;
            }
            else if (mosaic->getTile(row, col) == 'u')
            {
                boardToString += WHITE;
                boardToString += mosaic->getTile(row, col);
                boardToString += RESET;
            }
            else if (mosaic->getTile(row, col) == 'l')
            {
                boardToString += CYAN;
                boardToString += mosaic->getTile(row, col);
                boardToString += RESET;
            }
        }
        boardToString += "\n";
    }
    boardToString += "Broken:                  ";
    boardToString += broken->toString();
    return boardToString;
}
