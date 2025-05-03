#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

extern short int UNSOLVED;
extern int POSSIBLE;
extern int SIZE_ROWS;
extern int SIZE_COLUMNS;
extern long propagation_count;
extern long backtrack_count;
#ifdef _OPENMP
#pragma omp threadprivate(UNSOLVED, propagation_count, backtrack_count)
#endif


typedef struct Sudoku
{
    struct Square ***squares;
    struct Box **boxes;
} Sudoku;

typedef struct Box
{
    struct Square **squares;
    int numbers;
    int possible[9];
    int solvable;
    struct Box *next;
} Box;

typedef struct Square
{
    int number;
    int possible[9];
    int solvable;
    Box *box;
    int row;
    int column;
} Square;

int **createPuzzle(char *puzzleString);
void printPuzzle(Square ***puzzle);
Sudoku *setUpPuzzle(int **puzzle);
Sudoku *createSodoku(Square ***squares, Box **boxes);
int updateSudoku(Square ***sudoku, int row, int column);
int boxSingles(Square ***sudoku, Box **boxes);
int checkPuzzle(Square ***sudoku, Box **boxes);
void solveSquare(Square *square);
Box **createBoxes();
int updateBoxes(Square ***sudoku, int row, int column);
int backtrackSolve(Sudoku *sudoku);
int isValidMove(Sudoku *sudoku, int row, int col, int num);

#endif // SUDOKU_H