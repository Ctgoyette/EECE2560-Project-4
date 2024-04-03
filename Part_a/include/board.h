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
        void setCell(int i, int j, char val);
        void initializeConflicts();
        void getConflicts();
        int checkRow(int i, int j, int k);
        int checkColumn(int i, int j, int k);
        int checkSquare(int i, int j, int k);
        void printConflicts();
        bool checkWin();
        bool completeColumn(int i);
        bool completeRow(int j);
        bool completeSquares();

    private:
        // The following matrices go from 1 to BoardSize in each
        // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)

        matrix<ValueType> value; // Board
        matrix<vector<ValueType> > conflicts; // Conflict Vectors
};

#endif