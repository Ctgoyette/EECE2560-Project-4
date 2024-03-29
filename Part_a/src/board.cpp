#include "../include/board.h"

board::board(int sqSize) : value(BoardSize+1,BoardSize+1)
// Board constructor
{
    clear();
}

void board::clear()
// Mark all possible values as legal for each board entry
{
    for (int i = 1; i <= BoardSize; i++)
    for (int j = 1; j <= BoardSize; j++)
    {
        value[i][j] = Blank;
    }
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
    char ch;

    clear();

    for (int i = 1; i <= BoardSize; i++)
    for (int j = 1; j <= BoardSize; j++)
    {
        fin >> ch;
        // If the read char is not Blank
        if (ch != '.')
        {
            setCell(i,j,ch-'0'); // Convert char to int
        }
    }
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell. Throws an exception
// if bad values are passed.
{
    if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
    {
        return value[i][j];
    }
    else
    {
        throw rangeError("bad value in getCell");
    }
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
    if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
    {
        throw rangeError("bad value in setCell");
    }
    return (getCell(i,j) == Blank);
}

void board::print()
// Prints the current board.
{
    for (int i = 1; i <= BoardSize; i++)
    {
        if ((i-1) % SquareSize == 0)
        {
            cout << " -";
            for (int j = 1; j <= BoardSize; j++)
            {
                cout << "---";
            }
            cout << "-";
            cout << endl;
        }
        for (int j = 1; j <= BoardSize; j++)
        {
            if ((j-1) % SquareSize == 0)
            {
                cout << "|";
            }
            if (!isBlank(i,j))
            {
                cout << " " << getCell(i,j) << " ";
            }
            else
            {
                cout << " ";
            }
        }
        cout << "|";
        cout << endl;
    }
    cout << " -";
    for (int j = 1; j <= BoardSize; j++)
    {
        cout << "---";
    }
    cout << "-";
    cout << endl;
}