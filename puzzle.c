#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

#define SIZE_ROWS 9
#define SIZE_COLUMNS 9

typedef struct Square {
    int number;
    int row;
    int column;
    int solvable;
    int *possible;
} Square;

Square *** setUpPuzzle(int ** puzzle) {
    Square ***sudoku;
    int i, j, x;

    sudoku = (Square ***)malloc(sizeof(Square **) * 9);
    /* loop through rows */
    for (i = 0; i < SIZE_ROWS; i++) {
        sudoku[i] = (Square **)malloc(sizeof(Square *) * 9);
        // loop through columns
        for (j = 0; j < SIZE_COLUMNS; j++) {
            sudoku[i][j] = (Square *)malloc(sizeof(Square));
            sudoku[i][j]->possible = (int *)malloc(sizeof(int) * SIZE_ROWS);  // Allocate memory for possible array

            sudoku[i][j]->number = puzzle[i][j];
            sudoku[i][j]->row = i;
            sudoku[i][j]->column = j;
            sudoku[i][j]->solvable = 9;

            for (x = 0; x < SIZE_ROWS; x++) {
                sudoku[i][j]->possible[x] = 0;
            }
        }
    }

    for (i = 0; i < SIZE_ROWS; i++) {
        for (j = 0; j < SIZE_COLUMNS; j++) {
            if (sudoku[i][j]->number != 0) {
                sudoku[i][j]->solvable = 0;
                updateSudoku(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }
    return sudoku;
}

int updateSudoku(Square *** sudoku, int row, int column) {
    int x;
    int number = sudoku[row][column]->number;

    for (x = 0; x < SIZE_ROWS; x++) {
        if (sudoku[x][column]->possible[number - 1] == 0) {
            sudoku[x][column]->solvable--;
        }
        sudoku[x][column]->possible[number - 1] = 1;
    }
    for (x = 0; x < SIZE_COLUMNS; x++) {
        if (sudoku[row][x]->possible[number - 1] == 0) {
            sudoku[row][x]->solvable--;
        }
        sudoku[row][x]->possible[number - 1] = 1;
    }

    return 1;
}

int checkPuzzle(Square *** sudoku) {
    int i, j, x;
    for (i = 0; i < SIZE_ROWS; i++) {
        for (j = 0; j < SIZE_COLUMNS; j++) {
            if (sudoku[i][j]->solvable == 1) {
                solveSquare(sudoku[i][j]);
                updateSudoku(sudoku, i, j);
            }
        }
    }
    return 1;
}

int ** createPuzzle() {
    int **puzzle;
    int i, j;
    int array[9][9] = { 
        0, 1, 9, 0, 0, 2, 0, 0, 0,
        4, 7, 0, 6, 9, 0, 0, 0, 1,
        0, 0, 0, 4, 0, 0, 0, 9, 0,
        8, 9, 4, 5, 0, 7, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 2, 0, 1, 9, 5, 8,
        0, 5, 0, 0, 0, 6, 0, 0, 0,
        6, 0, 0, 0, 2, 8, 0, 7, 9,
        0, 0, 0, 1, 0, 0, 8, 6, 0 
    };

    puzzle = (int **)malloc(sizeof(int *) * 9);

    for (i = 0; i < 9; i++) {
        puzzle[i] = (int *)malloc(sizeof(int) * 9);
        for (j = 0; j < 9; j++) {
            puzzle[i][j] = array[i][j];
        }
    }
    return puzzle;
}

void printPuzzle(Square *** sudoku) {
    int i, j;
    printf("-------------------------------\n");
    for (i = 0; i < SIZE_ROWS; i++) {
        /* print each row */
        printf("|"); 
        for (j = 0; j < SIZE_COLUMNS; j++) {
            printf(" %d ", sudoku[i][j]->number);
            if ((j + 1) % 3 == 0) {
                printf("|");
            }
        }
        printf("\n");
        if ((i + 1) % 3 == 0) {
            printf("-------------------------------\n");
        }
    }
}

void freePuzzle(Square *** sudoku) {
    int i, j;

    for (i = 0; i < SIZE_ROWS; i++) {
        for (j = 0; j < SIZE_COLUMNS; j++) {
            free(sudoku[i][j]->possible);  // Free possible array
            free(sudoku[i][j]);            // Free Square struct
        }
        free(sudoku[i]);                   // Free row pointers
    }
    free(sudoku);                          // Free the main array
}
