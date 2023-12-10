#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 30
#define MAX_LINES 200 
#define END_OF_NUMBERS -1
#define NAN -1
#define ASCII_ZERO 48
#define ASCII_NINE 57
#define FALSE 0
#define TRUE 1

void populate_numbers(FILE *, long *, long);
int is_winning_number(long *, long);

int main(int argc, char **argv) {
	/* Declarations */
	FILE *fptr;
	long *winning_numbers, *possible_numbers, total_points, card_points, index, number_of_wins, card_num;
	long *card_occurrences, total_occurrences;
	char fchar;

	/* Initializations */
	fptr = fopen(*(argv + 1), "r");
	winning_numbers = calloc(MAX_NUMBERS, sizeof(long));
	possible_numbers = calloc(MAX_NUMBERS, sizeof(long));
	card_occurrences = calloc(MAX_LINES, sizeof(long));

	index = 0;
	while (index < MAX_LINES) {
		*(card_occurrences+index) = 0;
		index++;
	}

	/* Read through cards */
	total_points = 0;
	total_occurrences = 0;
    card_num = 0;
	while (fchar = fgetc(fptr), fchar != EOF) {
		populate_numbers(fptr, winning_numbers, TRUE);
		populate_numbers(fptr, possible_numbers, FALSE);
		card_points = 0;
		number_of_wins = 0;
		index = 0;
		while (*(possible_numbers+index) != END_OF_NUMBERS) {
			if (is_winning_number(winning_numbers, *(possible_numbers+index))) {
				if (card_points == 0) {
					card_points = 1;
				} else {
					card_points *= 2;
				}
				number_of_wins++;
			}
			index++;
		}
		total_points += card_points;

		/* Handle future occurrences */
		(*(card_occurrences+card_num))++;
		if (number_of_wins > 0) {
			index = card_num + 1;
			while ((index-card_num) <= number_of_wins) {
				*(card_occurrences+index) += *(card_occurrences+card_num);
				index++;
			}
		}
		total_occurrences += *(card_occurrences+card_num);
		card_num++;
	}

	printf("Points: %d\n", total_points);
	printf("Occurrences: %d\n", total_occurrences);

	fclose(fptr);
	free(winning_numbers);
	free(possible_numbers);
	free(card_occurrences);
	return EXIT_SUCCESS;
}

void populate_numbers(FILE *fptr, long *numbers, long winning_numbers) {
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

int is_winning_number(long *winning_numbers, long number) {
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
