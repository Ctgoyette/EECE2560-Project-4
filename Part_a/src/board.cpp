#include "../include/board.h"

board::board(int sqSize) : value(BoardSize+1,BoardSize+1), conflicts(BoardSize+1,BoardSize+1)
// Board constructor
{
    clear();
}

void board::clear()
// Mark all possible values as legal for each board entry
{
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            value[i][j] = Blank;
        }
    }
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
    char ch;

    clear();

    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            fin >> ch;
            // If the read char is not Blank
            if (ch != '.')
            {
                setCell(i, j, ch-'0'); // Convert char to int
            }
            else 
            {
                setCell(i, j, -1);
            }
        }
    }
    initializeConflicts();
    getConflicts();
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell. Throws an exception
// if bad values are passed.
{
    if (i >= 0 && i < BoardSize && j >= 0 && j <= BoardSize)
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
    if (i < 0 || i >= BoardSize || j < 0 || j >= BoardSize)
    {
        throw rangeError("bad value in setCell");
    }
    return (getCell(i,j) == Blank);
}

void board::print()
// Prints the current board.
{
    for (int i = 0; i < BoardSize; i++)
    {
        if ((i) % SquareSize == 0)
        {
            cout << " -";
            for (int j = 0; j < BoardSize; j++)
            {
                cout << "---";
            }
            cout << "-";
            cout << endl;
        }
        for (int j = 0; j < BoardSize; j++)
        {
            if ((j) % SquareSize == 0)
            {
                cout << "|";
            }
            if (!isBlank(i,j))
            {
                cout << " " << getCell(i,j) << " ";
            }
            else
            {
                cout << "   ";
            }
        }
        cout << "|";
        cout << endl;
    }
    cout << " -";
    for (int j = 0; j < BoardSize; j++)
    {
        cout << "---";
    }
    cout << "-";
    cout << endl;
}

void board::setCell(int i, int j, char val)
{
    value[i][j] = int(val);
}

void board::initializeConflicts()
{
    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            for (int k = 1; k <= BoardSize; k++)
            {
                //cout << "i: " << i << " j: " << j << " k: " << k << endl;
                conflicts[i][j].push_back(int(0));
            }
        }
    }
}

void board::getConflicts()
{
    int num_conflicts;
    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            for (int k = 1; k <= BoardSize; k++)
            {
                num_conflicts = 0;
                num_conflicts += checkRow(i,j,k);
                //cout << "row conflicts: " << num_conflicts << endl;
                num_conflicts += checkColumn(i,j,k);
                //cout << "With column conflicts: " << num_conflicts << " ";
                num_conflicts += checkSquare(i,j,k);
                conflicts[i][j][k-1] = num_conflicts;
            }
        }
    }
}

int board::checkRow(int i, int j, int k)
{
    bool check = false;
    if (check) {cout << "i: " << i << " j: " << j << " k: " << k << endl;}
    int square_column = j/SquareSize;
    if (check) {cout << "i: " << i << " j: " << j << " k: " << k << endl;}
    for (int j = 0; j < SquareSize*square_column; j++)
    {
        if (value[i][j] == k)
        {
            return 1;
        }
    }
    if (check) {cout << "i: " << i << " j: " << j << " k: " << k << endl;}
    if (square_column < SquareSize - 1)
    {
        for (int j = square_column+SquareSize; j < BoardSize; j++)
        {
            if (value[i][j] == k)
            {
                return 1;
            }
        }
    }
    return 0;
}

int board::checkColumn(int i, int j, int k)
{   
    // bool check = false;
    // if (i == 7 && j == 6) {check = true;}
    int square_row = i/SquareSize;
    //if (check) {cout << "square_row: " << square_row << endl;}
    //if (check) {cout << "i: " << i << " j: " << j << " k: " << k << endl;}
    for (int n = 0; n < SquareSize*square_row; n++)
    {  
        // if (check) {cout << "n: " << n << " j: " << j << " k: " << k;}
        // if (check) {cout << " " << value[n][j] << " " << endl;}
        if (value[n][j] == k)
        {
            return 1;
        }
    }
    //if (check) {cout << "i: " << i << " j: " << j << " k: " << k << endl;}
    if (square_row < SquareSize - 1)
    {
        for (int n = square_row+SquareSize; n < BoardSize; n++)
        {
            if (value[n][j] == k)
            {
                return 1;
            }
        }
    }
    return 0;
}

int board::checkSquare(int i, int j, int k)
{
    int square_row = i/SquareSize;
    int square_column = j/SquareSize;
    for (int m = SquareSize*square_row; m < SquareSize*square_row+SquareSize; m++)
    {
        for (int n = SquareSize*square_column; n < SquareSize*square_column+SquareSize; n++)
        if (value[m][n] == k)
        {
            return 1;
        }
    }
    return 0;
}

void board::printConflicts()
{
    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            cout << "(" << i << ", " << j << ")" << ": ";
            for (int k = 0; k < BoardSize; k++)
            {
                cout << conflicts[i][j][k] << " ";
            }
            cout << endl;
        }
    }
}