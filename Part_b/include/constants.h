#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include <numeric>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1; // Indicates that a cell is blank

const int SquareSize = 3;   // The number of cells in a small square
                            // (usually 3). The board has
                            // SquareSize^2 rows and SquareSize^2
                            // columns.
const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

const vector<bool> FullConflictVector (MaxValue, 1);

#endif