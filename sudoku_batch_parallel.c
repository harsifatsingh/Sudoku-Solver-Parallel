// sudoku_batch_parallel.c
// Ultra-fast parallel batch Sudoku solver using OpenMP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <omp.h>
#include "sudoku.h"    // solver API: definitions & externs for UNSOLVED, propagation_count, backtrack_count

// Ensure each OpenMP thread has its own copy of solver globals
#pragma omp threadprivate(UNSOLVED, propagation_count, backtrack_count)

#define INPUT_CSV   "data/input_shortened.csv"
#define OUTPUT_CSV  "data/output.csv"
#define MAX_LINE    512

// Trim leading/trailing spaces, quotes, CR/LF
static char *trim(char *s) {
    while (*s==' ' || *s=='"' || *s=='\r' || *s=='\n') s++;
    char *end = s + strlen(s) - 1;
    while (end >= s && (*end==' ' || *end=='"' || *end=='\r' || *end=='\n')) {
        *end-- = '\0';
    }
    return s;
}

// Puzzle+clue container
typedef struct {
    char puzzle[82];
    char clue[256];
} Puzzle;

int main(void) {
    omp_set_num_threads(omp_get_num_procs());

    // Read all puzzles into memory
    FILE *fin = fopen(INPUT_CSV, "r");
    if (!fin) { perror("opening import.csv"); return 1; }
    char line[MAX_LINE];
    if (!fgets(line, sizeof(line), fin)) { fprintf(stderr, "No header in import.csv\n"); fclose(fin); return 1; }

    Puzzle *tasks = NULL;
    size_t tasks_size = 0, tasks_cap = 0;
    while (fgets(line, sizeof(line), fin)) {
        size_t L = strcspn(line, "\r\n"); line[L] = '\0';
        char *comma = strchr(line, ','); if (!comma) continue;
        *comma = '\0'; char *f1 = trim(line), *f2 = trim(comma+1);
        size_t l1=strlen(f1), l2=strlen(f2); char *puz=NULL,*cl=NULL;
        if (l1==81&&l2>0) { puz=f1;cl=f2; }
        else if(l2==81&&l1>0){ puz=f2;cl=f1; }
        else { fprintf(stderr,"Skipping bad fields (len1=%zu,len2=%zu)\n",l1,l2);continue; }
        if (tasks_size==tasks_cap) {
            tasks_cap = tasks_cap?tasks_cap*2:1024;
            tasks = realloc(tasks,tasks_cap*sizeof(Puzzle));
        }
        memcpy(tasks[tasks_size].puzzle,puz,82);
        strncpy(tasks[tasks_size].clue,cl,sizeof(tasks[tasks_size].clue)-1);
        tasks[tasks_size].clue[sizeof(tasks[tasks_size].clue)-1]='\0';
        tasks_size++;
    }
    fclose(fin);

    // Prepare output CSV
    FILE *fout = fopen(OUTPUT_CSV, "a+");
    if (!fout) { perror("opening output.csv"); free(tasks); return 1; }
    struct stat st; if (stat(OUTPUT_CSV,&st)==0 && st.st_size==0) {
        fputs("clue_numbers,solving_time_ms,backtrack_count,propagation_count\n",fout);
    }

    // Parallel solve
    #pragma omp parallel for schedule(dynamic)
    for (size_t i=0;i<tasks_size;i++){
        UNSOLVED=81; propagation_count=0; backtrack_count=0;
        double t0=omp_get_wtime();
        int **grid = createPuzzle(tasks[i].puzzle);
        Sudoku *s = setUpPuzzle(grid);
        while (checkPuzzle(s->squares,s->boxes)>0){}
        if(UNSOLVED>0) backtrackSolve(s);
        double elapsed_ms=(omp_get_wtime()-t0)*1e3;
        // freeSudoku(s);

        #pragma omp critical
        fprintf(fout,"%s,%.3f,%ld,%ld\n",
            tasks[i].clue, elapsed_ms, backtrack_count, propagation_count);
    }

    fclose(fout);
    free(tasks);
    return 0;
}
