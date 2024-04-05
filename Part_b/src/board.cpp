#include "../include/board.h"

board::board(int sqSize) : 
value(BoardSize,BoardSize), 
row_conflicts(BoardSize,MaxValue),
column_conflicts(BoardSize,MaxValue),
square_conflicts(BoardSize,MaxValue)

// Board constructor
{
    clear();
}

// Mark all possible values as legal for each board entry
void board::clear()
{
    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            value[i][j] = Blank;
        }
    }
}

// Read a Sudoku board from the input file.
void board::initialize(ifstream &fin)
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
                setCell(i, j, Blank);
            }
        }
    }
    initializeConflicts();
}

// Returns the value stored in a cell. Throws an exception
// if bad values are passed.
ValueType board::getCell(int i, int j)
{
    if (i >= 0 && i < BoardSize && j >= 0 && j < BoardSize)
    {
        return value[i][j];
    }
    else
    {
        throw rangeError("bad value in getCell");
    }
}

// Returns true if cell i,j is blank, and false otherwise.
bool board::isBlank(int i, int j)
{
    if (i < 0 || i >= BoardSize || j < 0 || j >= BoardSize)
    {
        throw rangeError("bad value in setCell");
    }
    return (getCell(i,j) == Blank);
}

// Prints the current board.
void board::print()
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

//Sets the specified cells to the specified value updates conflict vectors
void board::setCell(int i, int j, int set_val)
{
    value[i][j] = set_val;

    row_conflicts[i][set_val-1] = 1;
    column_conflicts[j][set_val-1] = 1;
    square_conflicts[determineSquare(i, j)][set_val-1] = 1;

}

//Erases the specified cell and updates conflict vectors
void board::eraseCell(int i, int j)
{
    int cur_val = value[i][j];

    row_conflicts[i][cur_val-1] = 0;
    column_conflicts[j][cur_val-1] = 0;
    square_conflicts[determineSquare(i, j)][cur_val-1] = 0;

    value[i][j] = Blank;
}

//Initializes all the conflict vectors of the board
void board::initializeConflicts()
{
    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < MaxValue; j++)
        {
            row_conflicts[i][j] = checkRow(i,j+1);
            column_conflicts[i][j] = checkColumn(i, j+1);
            square_conflicts[i][j] = checkSquare(i, j+1);
        }
    }
}

//Checks if the specified value is present in the row
bool board::checkRow(int row, int k)
{
    for (int j = 0; j < BoardSize; j++)
    {
        if (value[row][j] == k)
        {
            return 1;
        }
    }

    return 0;
}

//Checks if the specified value is present in the column
bool board::checkColumn(int column, int k)
{
    for (int i = 0; i < BoardSize; i++)
    {
        if (value[i][column] == k)
        {
            return 1;
        }
    }

    return 0;
}

//Checks if the specified value is present in the square
bool board::checkSquare(int square_num, int k)
{
    int square_row = square_num/SquareSize;
    int square_column = square_num%SquareSize;
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

//Prints all the conflict vectors
void board::printConflicts()
{
    cout << "Row Conflict Vectors:" << endl;
    for (int i = 0; i < BoardSize; i++)
    {
        cout << "Row " << i << ": ";
        for (int j = 0; j < MaxValue; j++)
        {
            cout << row_conflicts[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Column Conflict Vectors:" << endl;
    for (int i = 0; i < BoardSize; i++)
    {
        cout << "Column " << i << ": ";
        for (int j = 0; j < MaxValue; j++)
        {
            cout << column_conflicts[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Square Conflict Vectors:" << endl;
    for (int i = 0; i < BoardSize; i++)
    {
        cout << "Square " << i << ": ";
        for (int j = 0; j < MaxValue; j++)
        {
            cout << square_conflicts[i][j] << " ";
        }
        cout << endl;
    }

}

//Checks if a column is complete and contains all possible digits once
bool board::completeColumn(int i)
{
    vector<int> numVector (BoardSize);
    for (int num = 1; num <= BoardSize; num++) {numVector[num-1] = num;}
    
    for (int j = 0; j < BoardSize; j++)
    {
        auto index = find(numVector.begin(), numVector.end(), value[i][j]);
        if (index != numVector.end())
        {
            numVector.erase(index);
        }
    }
    if (numVector.empty()) {return true;}
    else {return false;}
}

//Checks if a row is complete and contains all possible digits once
bool board::completeRow(int j)
{
    vector<int> numVector (BoardSize);
    for (int num = 1; num <= BoardSize; num++) {numVector[num-1] = num;}

    for (int i = 0; i < BoardSize; i++)
    {
        auto index = find(numVector.begin(), numVector.end(), value[i][j]);
        if (index != numVector.end())
        {
            numVector.erase(index);
        }
    }
    if (numVector.empty()) {return true;}
    else {return false;}
}

//Checks if a square is complete and contains all possible digits once
bool board::completeSquares()
{
    int count = 0;
    int xstart = 0;
    int ystart = 0;
    vector<int> numVector (BoardSize);
    vector<int> placeHolder (BoardSize);
    for (int num = 1; num <= BoardSize; num++) {placeHolder[num-1] = num;}

    while (count < BoardSize)
    {
        xstart = count%SquareSize*SquareSize;
        ystart = count/SquareSize*SquareSize;

        numVector = placeHolder;
        //cout << " xstart: " << xstart << " ystart: " << ystart;
        for (int i = xstart; i < xstart+SquareSize; i++)
        {
            for (int j = ystart; j < ystart+SquareSize; j++)
            {
                //cout << " i: " << i << " j: " << j; 
                auto index = find(numVector.begin(), numVector.end(), value[i][j]);
                if (index != numVector.end())
                {
                    numVector.erase(index);
                }
            }
        }
        if (!numVector.empty()) {return false;}
        count++;
    }
    return true;
}

//Checks is a board has been solved by observing if all conflict vectors are 1
//All conflict vectors being 1 indicates that every row, column, and square has the values it need and the board is therefore solved
bool board::checkWin()
{
    for (int i = 0; i < BoardSize; i++)
    {
        if (row_conflicts[i] != FullConflictVector || column_conflicts[i] != FullConflictVector || square_conflicts[i] != FullConflictVector)
        {
            return false;
        }
    }
    return true;
}

//Determines with square a cell is in based on its coordinates 
//Squares are:
// | 1 | 2 | 3 |
// -------------
// | 4 | 5 | 6 |
// -------------
// | 7 | 8 | 9 |
int board::determineSquare(int i, int j)
{
    int square_row = i/SquareSize;
    int square_column = j/SquareSize;

    int square_num = (square_row*SquareSize) + square_column;
    return square_num;
}

//Checks if a digit can be placed in a cell (returns true if there are no conflicts and false if conflicts are found)
bool board::checkValid(int i, int j, int k)
{
    if (row_conflicts[i][k-1] == 1 || column_conflicts[j][k-1] == 1 || square_conflicts[determineSquare(i, j)][k-1] == 1)
    {
        return false;
    }
    return true;
}

//Recursion algorithm to solve board
bool board::solveBoard(int row, int col)
{
    if (row == 0 && col == 0){iterations = 1;}
    else {iterations += 1;}

    if (row == BoardSize) {return true;}
    else if (col == BoardSize) {return solveBoard(row+1, 0);}
    else if (value[row][col] != Blank) {return solveBoard(row, col+1);}
    else 
    {
        for (int k = 1; k <= MaxValue; k++)
        {
            if (checkValid(row, col, k))
            {
                setCell(row, col, k);
                if (solveBoard(row, col+1))
                {
                    return true;
                }
                eraseCell(row, col);
            }
        }
        return false;
    }
}

unsigned long board::getIterations()
{
    return iterations;
}