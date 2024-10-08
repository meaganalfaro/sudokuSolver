#include "sudoku.h"

int UNSOLVED = 81;
int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;

int main()
{
	int ** puzzle;
	Square *** sudoku;

	puzzle = createPuzzle();

	sudoku = setUpPuzzle(puzzle);

	printPuzzle(puzzle);

	checkPuzzle(sudoku);
	
	printf("\n\n");

	printPuzzle(puzzle);

	return 0;
}
