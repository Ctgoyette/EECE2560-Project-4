#include "../include/board.h"

int numSolutions = 0;

int main()
{
    ifstream fin;

    // Read the sample grid from the file.
    string fileName = "sudoku_test.txt";

    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try
    {
        board b1(SquareSize);
        while (fin && fin.peek() != 'Z')
        {
            b1.initialize(fin);
            b1.print();
            b1.printConflicts();
            if (b1.checkWin())
            {
                cout << endl << "You won!" << endl;
            }
            else{
                cout << endl << "Keep Going..." << endl;
            }
        }
    }
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}