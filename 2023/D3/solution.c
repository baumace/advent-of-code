#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 200
#define MAX_NUMBER_LINES 200
#define FALSE 0
#define TRUE 1 
#define ASCII_ZERO 48
#define ASCII_NINE 57

int is_num(char);
int adjacent_symbol(char**, int, int, int, int);

int main(int argc, char **argv) {
	/* Variable declarations */
	FILE *fptr;
	char **schematic_matrix, fchar, mchar;
	int index, row, column, row_index, column_index, running_sum, sum, number_has_adjacent;

	/* Initializations */
	fptr = fopen(*(argv+1), "r");
	schematic_matrix = calloc(MAX_NUMBER_LINES, sizeof(char **));
	for (index = 0; index < MAX_NUMBER_LINES; index++) {
		*(schematic_matrix+index) = calloc(MAX_LINE_LENGTH, sizeof(char));
	}

	/* Populate matrix */
	row = 0;
	while (fchar != EOF) {
		fchar = fgetc(fptr);
		if (fchar != EOF) {
			column = 0;
		}
		while (fchar != '\n' && fchar != EOF) {
			if (column != 0) {
				fchar = fgetc(fptr);
			}
			/* Points to matrix[row][column] */
			*(*(schematic_matrix+row)+column) = fchar;
			column++;
		}
		if (fchar != EOF) {
			row++;
		}
	}

	/* Calculate */
	row_index = 0;
	sum = 0;
	while (row_index < row) {
		number_has_adjacent = FALSE;
		running_sum = 0;
		column_index = 0;
		while (column_index < column) {
			mchar = *(*(schematic_matrix+row_index)+column_index); 
			if (is_num(mchar)) {
				if (!number_has_adjacent) {
					number_has_adjacent = adjacent_symbol(schematic_matrix, row, column, row_index, column_index);
				}
				running_sum  = running_sum * 10 + (mchar - ASCII_ZERO);
			} else {
				if (number_has_adjacent) {
					sum += running_sum;
				}
				running_sum = 0;
				number_has_adjacent = FALSE;
			}
			column_index++;
		}
		row_index++;
	}

	printf("Sum: %d\n", sum);

	/* Exit */
	for (index; index < MAX_NUMBER_LINES; index++) {
		free(*(schematic_matrix+index));
	}
	free(schematic_matrix);
	return EXIT_SUCCESS;
}

int is_num(char c) {
	return (c >= ASCII_ZERO) && (c <= ASCII_NINE);
}
int adjacent_symbol(char **schematic_matrix, int row, int column, int row_index, int column_index) {
	int has_adjacent = FALSE;

	/* Check above */
	if (row_index > 0) {
		if (!is_num(*(*(schematic_matrix+row_index-1)+column_index)) && *(*(schematic_matrix+row_index-1)+column_index) != '.') {
			has_adjacent = TRUE;
		}
	}
	/* Check below */
	if (row_index < row - 2) {
		if (!is_num(*(*(schematic_matrix+row_index+1)+column_index)) && *(*(schematic_matrix+row_index+1)+column_index) != '.') {
			has_adjacent = TRUE;
		}
	}
	/* Check left */
	if (column_index > 0) {
		if (!is_num(*(*(schematic_matrix+row_index)+column_index-1)) && *(*(schematic_matrix+row_index)+column_index-1) != '.') {
			has_adjacent = TRUE;
		}
	}
	/* Check right */
	if (column_index < column - 2) {
		if (!is_num(*(*(schematic_matrix+row_index)+column_index+1)) && *(*(schematic_matrix+row_index)+column_index+1) != '.') {
			has_adjacent = TRUE;
		}
	}
	/* Check upper right */
	if (row_index > 0 && column_index < column - 2) {
		if (!is_num(*(*(schematic_matrix+row_index-1)+column_index+1)) && *(*(schematic_matrix+row_index-1)+column_index+1) != '.') {
			has_adjacent = TRUE;
		}
	}
	/* Check upper left */
	if (row_index > 0 && column_index > 0) {
		if (!is_num(*(*(schematic_matrix+row_index-1)+column_index-1)) && *(*(schematic_matrix+row_index-1)+column_index-1) != '.') {
			has_adjacent = TRUE;
		}
	}
	/* Check lower left */
	if (row_index < row - 2 && column_index > 0) {
		if (!is_num(*(*(schematic_matrix+row_index+1)+column_index-1)) && *(*(schematic_matrix+row_index+1)+column_index-1) != '.') {
			has_adjacent = TRUE;
		}
	}
	/* Check lower right */
	if (row_index < row - 2 && column_index < column - 2) {
		if (!is_num(*(*(schematic_matrix+row_index+1)+column_index+1)) && *(*(schematic_matrix+row_index+1)+column_index+1) != '.') {
			has_adjacent = TRUE;
		}
	}
	
	return has_adjacent;
}
