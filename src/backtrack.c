#include "sudoku.h"

int isValidMove(Sudoku *sudoku, int row, int col, int num)
{
    propagation_count++;
    for (int i = 0; i < SIZE_ROWS; i++)
    {
        if (sudoku->squares[row][i]->number == num)
            return 0;
        if (sudoku->squares[i][col]->number == num)
            return 0;
    }
    int boxR = (row / 3) * 3;
    int boxC = (col / 3) * 3;
    for (int dr = 0; dr < 3; dr++)
    {
        for (int dc = 0; dc < 3; dc++)
        {
            if (sudoku->squares[boxR + dr][boxC + dc]->number == num)
                return 0;
        }
    }
    return 1;
}

int backtrackSolve(Sudoku *sudoku)
{
    backtrack_count++;
    if (UNSOLVED == 0)
        return 1;

    int row = -1, col = -1;
    for (int i = 0; i < SIZE_ROWS && row < 0; i++)
    {
        for (int j = 0; j < SIZE_COLUMNS; j++)
        {
            if (sudoku->squares[i][j]->number == 0)
            {
                row = i;
                col = j;
                break;
            }
        }
    }

    for (int num = 1; num <= 9; num++)
    {
        if (isValidMove(sudoku, row, col, num))
        {
            sudoku->squares[row][col]->number = num;
            UNSOLVED--;

            if (backtrackSolve(sudoku))
                return 1;

            sudoku->squares[row][col]->number = 0;
            UNSOLVED++;
        }
    }

    return 0;
}
