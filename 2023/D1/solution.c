#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 150
#define ASCII_ZERO 48
#define ASCII_NINE 57
#define FALSE 0
#define TRUE 1

int is_num(char);

int main(int argc, char** argv) {
	FILE *fptr;
	char *input, scanf_return_value;
	int is_first = 1, final_sum = 0, first_digit, last_digit, index;

	/* Setup */
	input = malloc(MAX_LINE_LENGTH * sizeof(char));
	fptr = fopen(*(argv+1), "r");

	/* Get numbers */
	while (scanf_return_value = fscanf(fptr, "%s\n", input), scanf_return_value != EOF) {
		index = 0;
		while (*(input + index) != '\0') {
			if (is_num(*(input+index)) != FALSE) {
				if (is_first) {
					first_digit = *(input+index) - ASCII_ZERO;
					is_first = FALSE;
				}
				last_digit = *(input+index) - ASCII_ZERO;
			}
			index++;
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
	return EXIT_SUCCESS;
}

int is_num(char c) {
	return (c >= ASCII_ZERO) && (c <= ASCII_NINE);
}
