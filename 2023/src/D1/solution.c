#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 150
#define ASCII_ZERO 48
#define ASCII_NINE 57
#define FALSE 0
#define TRUE 1
#define EQUAL 0
#define NAN -1

int is_num(char);
int string_to_digit(char *, char *, int, int);

int main(int argc, char** argv) {
	FILE *fptr;
	char *input, scanf_return_value, *input_substring;
	int is_first = 1, final_sum = 0, first_digit, last_digit, index;
	int index_start, index_end, str_digit;

	/* Setup */
	input = malloc(MAX_LINE_LENGTH * sizeof(char));
	fptr = fopen(*(argv+1), "r");

	/* Get numbers */
	while (scanf_return_value = fscanf(fptr, "%s\n", input), scanf_return_value != EOF) {
		index = 0;
		while (*(input + index) != '\0') {
			input_substring = malloc(MAX_LINE_LENGTH * sizeof(char));
			if (is_num(*(input+index))) {
				if (is_first) {
					first_digit = *(input+index) - ASCII_ZERO;
					is_first = FALSE;
				}
				last_digit = *(input+index) - ASCII_ZERO;
				index++;
			} else {
				index_start = index;
				while (str_digit = string_to_digit(input, input_substring, index_start, index), *(input+index) != '\0' && !is_num(*(input+index)) && str_digit == NAN) {
					index++;
				}

				/* digit found in the letters? */
				if (str_digit != NAN) {
					if (is_first) {
						first_digit = str_digit;
						is_first = FALSE;
					}
					last_digit = str_digit;
					index--;
				}
			}
		}
		is_first = TRUE;

		/* Add line to sum */
		final_sum += first_digit*10 + last_digit;
	}

	/* Print result */ 
	printf("Result: %d", final_sum);

	/* New line for console */
	printf("\n");

	/* Close and exit success */ 
	fclose(fptr);
	free(input);
	free(input_substring);
	return EXIT_SUCCESS;
}

int is_num(char c) {
	return (c >= ASCII_ZERO) && (c <= ASCII_NINE);
}

int string_to_digit(char *str, char *sub_str, int start, int end) {
	int index = 0;
	int size = end - start;
	strncpy(sub_str, str+start, size);

	/* Look through possible digits within substring */
	while (index < size) {
		if (strcmp(sub_str, "zero") == EQUAL) {
			return 0;
		}
		if (strcmp(sub_str, "one") == EQUAL) {
			return 1;
		}
		if (strcmp(sub_str, "two") == EQUAL) {
			return 2;
		}
		if (strcmp(sub_str, "three") == EQUAL) {
			return 3;
		}
		if (strcmp(sub_str, "four") == EQUAL) {
			return 4;
		}
		if (strcmp(sub_str, "five") == EQUAL) {
			return 5;
		}
		if (strcmp(sub_str, "six") == EQUAL) {
			return 6;
		}
		if (strcmp(sub_str, "seven") == EQUAL) {
			return 7;
		}
		if (strcmp(sub_str, "eight") == EQUAL) {
			return 8;
		}
		if (strcmp(sub_str, "nine") == EQUAL) {
			return 9;
		}
		sub_str++;
		index++;
	}
	return NAN;
}
