#include "sudoku.h"
#include <omp.h>

// Give each OpenMP thread its own copy of these solver globals
#pragma omp threadprivate(UNSOLVED, propagation_count, backtrack_count)

short int UNSOLVED = 81;
int         POSSIBLE = 0x1FF;
int         SIZE_ROWS = 9;
int         SIZE_COLUMNS = 9;
long        propagation_count = 0;
long        backtrack_count   = 0;

#ifndef BATCH_BUILD
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Not enough arguments. Usage: %s <81-digit-number>\n", argv[0]);
        return 1;
    }

    if (strlen(argv[1]) != 81) {
        printf("Error: Argument must be exactly 81 digits long.\n");
        return 1;
    }

    for (int i = 0; i < 81; i++) {
        if (!isdigit(argv[1][i])) {
            printf("Error: Argument must contain only digits.\n");
            return 1;
        }
    }

    int progress;
    struct timespec t0, t1;

    // Load and initialize puzzle
    int **puzzle = createPuzzle(argv[1]);
    Sudoku *sudoku = setUpPuzzle(puzzle);

    // Start timing
    clock_gettime(CLOCK_MONOTONIC, &t0);

    // Constraint propagation loop
    while ((progress = checkPuzzle(sudoku->squares, sudoku->boxes)) > 0) {
        // no-op
    }

    // If still unsolved, switch to backtracking
    if (UNSOLVED > 0) {
        if (!backtrackSolve(sudoku)) {
            printf("No solution found.\n");
            return 1;
        }
    }

    // End timing
    clock_gettime(CLOCK_MONOTONIC, &t1);

    // Calculate and print elapsed time in microseconds and counts
    double elapsed_ms = (t1.tv_sec - t0.tv_sec) * 1e3 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
    printf("%.3f %ld %ld\n", elapsed_ms, backtrack_count, propagation_count);

    return 0;
}
#endif
