#ifndef BOARD_H
#define BOARD_H

#include "constants.h"

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

    private:
        // The following matrices go from 1 to BoardSize in each
        // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)

        matrix<ValueType> value; //Board
};

#endif