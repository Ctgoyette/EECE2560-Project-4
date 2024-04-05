#include "../include/board.h"

unsigned long totalRecCalls = 0;
int numBoards = 0;

int main()
{
    ifstream fin;

    // Read the sample grid from the file.
    string fileName = "sudoku.txt";

    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try
    {
        //Creates the board based on the information from the given file
        board b1(SquareSize);
        while (fin && fin.peek() != 'Z')
        {
            b1.initialize(fin);
            b1.print();
            cout << "Solving..." << endl;
            b1.solveBoard(0, 0);
            b1.print();
            if (b1.checkWin()) {cout << "Board Solved" << endl;}
            else {cout << "This board has no solution!!!!" << endl;}
            cout << "Recursive Calls: " << b1.getIterations() << "\n" << endl;

            //Calculations for determining total and average recursive calls for solving all boards
            totalRecCalls += b1.getIterations();
            numBoards += 1;
        }
        cout << "Total Recursive Calls: " << totalRecCalls << endl;
        cout << "Total Boards Solved: " << numBoards << endl;
        cout << "Average Recursive Calls: " << totalRecCalls/numBoards << endl;
    }
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}