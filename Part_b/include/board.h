#ifndef BOARD_H
#define BOARD_H

#include "constants.h"
#include <iostream>
#include <algorithm>

class board
// Stores the entire Sudoku board
{
    public:
        board(int);
        void clear();
        void initialize(ifstream &fin);
        void print();
        bool isBlank(int, int);
        ValueType getCell(int, int);
        void setCell(int i, int j, int val);
        void eraseCell(int i, int j);
        void initializeConflicts();
        bool checkRow(int i, int k);
        bool checkColumn(int column, int k);
        bool checkSquare(int square_num, int k);
        void printConflicts();
        bool checkWin();
        bool completeColumn(int i);
        bool completeRow(int j);
        bool completeSquares();
        bool solveBoard(int row, int col);
        unsigned long getIterations();
        vector<int> nextCell();

    private:
        // The following matrices go from 1 to BoardSize in each
        // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)

        matrix<ValueType> value; // Board
        matrix<bool> row_conflicts; // Conflict Vectors
        matrix<bool> column_conflicts;
        matrix<bool> square_conflicts;

        vector<vector<int>> backtracking_steps;

        int determineSquare(int i, int j);
        bool checkValid(int i, int j, int k);
        unsigned long iterations;
};

#endif