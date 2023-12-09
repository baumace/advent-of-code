#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 30
#define END_OF_NUMBERS -1
#define NAN -1
#define ASCII_ZERO 48
#define ASCII_NINE 57
#define FALSE 0
#define TRUE 1

void populate_numbers(FILE *, int *, int);
int is_winning_number(int *, int);

int main(int argc, char **argv) {
	/* Declarations */
	FILE *fptr;
	int *winning_numbers, *possible_numbers, total_points, card_points, index, running_num;
	char fchar;

	/* Initializations */
	fptr = fopen(*(argv + 1), "r");
	winning_numbers = calloc(MAX_NUMBERS, sizeof(int));
	possible_numbers = calloc(MAX_NUMBERS, sizeof(int));

	/* Read through cards */
	total_points = 0;
	while (fchar = fgetc(fptr), fchar != EOF) {
		populate_numbers(fptr, winning_numbers, TRUE);
		populate_numbers(fptr, possible_numbers, FALSE);
		card_points = 0;
		index = 0;
		while (*(possible_numbers+index) != END_OF_NUMBERS) {
			if (is_winning_number(winning_numbers, *(possible_numbers+index))) {
				if (card_points == 0) {
					card_points = 1;
				} else {
					card_points *= 2;
				}
			}
			index++;
		}
		total_points += card_points;
	}

	printf("Points: %d\n", total_points);

	fclose(fptr);
	free(winning_numbers);
	free(possible_numbers);
	return EXIT_SUCCESS;
}

void populate_numbers(FILE *fptr, int *numbers, int winning_numbers) {
	char fchar;
	int num, num_index;

	if (winning_numbers) {
		/* Card X: */
		fscanf(fptr, "%*s %*d: ");
	} else {
		/* ' ' */
		fgetc(fptr);
	}

	num = NAN;
	num_index = 0;
	do {
        fchar = fgetc(fptr); 
		if (fchar >= ASCII_ZERO && fchar <= ASCII_NINE) {
			if (num == NAN) {
				num = 0;
			}
			num = num * 10 + fchar - ASCII_ZERO;
		} else if (num != NAN) {
			*(numbers+num_index++) = num;
			num = NAN;
		} else {
			num = NAN;
		}
	} while (fchar != '|' && fchar != '\n');
	*(numbers+num_index) = END_OF_NUMBERS;
}

int is_winning_number(int *winning_numbers, int number) {
	int is_winning, index;

	is_winning = FALSE;
	index = 0;
	while (!is_winning && *(winning_numbers+index) != END_OF_NUMBERS) {
		if (number == *(winning_numbers+index++)) {
			is_winning = TRUE;
		}
	}

	return is_winning;
}
