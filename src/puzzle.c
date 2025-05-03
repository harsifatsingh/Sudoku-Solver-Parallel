#include "sudoku.h"

Sudoku *createSodoku(Square ***squares, Box **boxes)
{
    Sudoku *sudoku = malloc(sizeof(Sudoku));

    sudoku->squares = squares;
    sudoku->boxes = boxes;

    return sudoku;
};

Sudoku *setUpPuzzle(int **puzzle)
{
    Square ***sudoku;
    Box **boxes;
    int currentBox = 0;

    sudoku = malloc(sizeof(Square **) * SIZE_ROWS);
    boxes = createBoxes();

    for (int i = 0; i < SIZE_ROWS; i++)
    {
        sudoku[i] = malloc(sizeof(Square *) * SIZE_COLUMNS);

        for (int j = 0; j < SIZE_COLUMNS; j++)
        {
            sudoku[i][j] = malloc(sizeof(Square));

            sudoku[i][j]->number = puzzle[i][j];
            sudoku[i][j]->row = i;
            sudoku[i][j]->column = j;
            sudoku[i][j]->solvable = 9;

            boxes[currentBox]->squares[(boxes[currentBox]->numbers)] = sudoku[i][j];
            sudoku[i][j]->box = boxes[currentBox];
            boxes[currentBox]->numbers++;

            for (int x = 0; x < SIZE_ROWS; x++)
            {
                sudoku[i][j]->possible[x] = 0;
            }

            if (j == 2 || j == 5)
            {
                currentBox++;
            }
        }
        currentBox -= 2;
        if (i == 2)
        {
            currentBox = 3;
        }
        if (i == 5)
        {
            currentBox = 6;
        }
    }
    for (int i = 0; i < SIZE_ROWS; i++)
    {
        for (int j = 0; j < SIZE_COLUMNS; j++)
        {
            if (sudoku[i][j]->number != 0)
            {
                sudoku[i][j]->solvable = 0;
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }
    return createSodoku(sudoku, boxes);
}

int updateSudoku(Square ***sudoku, int row, int column)
{
    int number = sudoku[row][column]->number;

    for (int x = 0; x < SIZE_ROWS; x++)
    {
        if (sudoku[x][column]->possible[number - 1] == 0)
        {
            sudoku[x][column]->solvable--;
        }
        sudoku[x][column]->possible[number - 1] = 1;
    }

    for (int x = 0; x < SIZE_COLUMNS; x++)
    {
        if (sudoku[row][x]->possible[number - 1] == 0)
        {
            sudoku[row][x]->solvable--;
        }
        sudoku[row][x]->possible[number - 1] = 1;
    }
    return 0;
}

int checkPuzzle(Square ***sudoku, Box **boxes)
{
    for (int i = 0; i < SIZE_ROWS; i++)
    {
        for (int j = 0; j < SIZE_COLUMNS; j++)
        {
            if (sudoku[i][j]->solvable == 1)
            {
                solveSquare(sudoku[i][j]);
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);

                return 1;
            }
        }
    }

    return boxSingles(sudoku, boxes);
}

int **createPuzzle(char *puzzleString)
{
    int **arr = malloc(SIZE_ROWS * sizeof(int *)); // Allocate memory for rows

    for (int i = 0; i < SIZE_ROWS; i++)
    {
        arr[i] = malloc(SIZE_COLUMNS * sizeof(int)); // Allocate memory for columns
    }

    int index = 0;
    for (int i = 0; i < SIZE_ROWS; i++)
    {
        for (int j = 0; j < SIZE_COLUMNS; j++)
        {
            arr[i][j] = (puzzleString[index]) - '0';
            index++;
        }
    }

    return arr;
}

void printPuzzle(Square ***puzzle)
{
    printf("\n");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int val = puzzle[i][j]->number;
            if (val == 0)
            {
                printf("- ");
            }
            else
            {
                printf("%d ", val);
            }
            if ((j + 1) % 3 == 0 && j != 8)
            {
                printf("| ");
            }
        }
        printf("\n");
        if ((i + 1) % 3 == 0 && i != 8)
        {
            printf("---------------------\n");
        }
    }
    printf("\n");
}