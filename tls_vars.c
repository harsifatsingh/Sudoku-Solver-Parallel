// tls_vars.c
#include "sudoku.h"

// define the globals once:
short int    UNSOLVED           = 81;
long   backtrack_count    = 0;
long   propagation_count  = 0;

// and mark them threadprivate
#pragma omp threadprivate(UNSOLVED, backtrack_count, propagation_count)
