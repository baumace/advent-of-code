#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 5
#define END_OF_NUMBERS -1
#define ASCII_ZERO 48
#define ASCII_ONE 57

void get_numbers(FILE *, long *);

int main(int argc, char **argv) {
    /* Declare */
    FILE *fptr;
    long *times, *distances;
    long permutation_num, permutation_distance, min_record, max_record;

    /* Initialize */
    fptr = fopen(*(argv+1), "r");
    times = malloc(MAX_NUMBERS * sizeof(int));
    distances = malloc(MAX_NUMBERS * sizeof(int));

    get_numbers(fptr, times);
    get_numbers(fptr, distances);

    printf("%ld %ld\n", *times, *distances);

    permutation_num = 0;
    min_record = -1;
    while (permutation_num < *times) {
        permutation_distance = permutation_num*(*times - permutation_num);
        if (permutation_distance > (long) *distances) {
            if (min_record == -1) {
                min_record = permutation_num;
            }
            max_record = permutation_num;
        }
        permutation_num++;
    }

    printf("%ld\n", (max_record-min_record+1));

    fclose(fptr);
    free(times);
    free(distances);
	return EXIT_SUCCESS;
}

void get_numbers(FILE *fptr, long *output_arr) {
    char fchar;
    long num, is_num, spaces_run;

    fscanf(fptr, "%*s: ");

    num = 0;
    spaces_run = 2;
    do {
        fchar = fgetc(fptr);
        is_num = fchar >= ASCII_ZERO && fchar <= ASCII_ONE;
        if (is_num) {
            spaces_run = 0;
            num = num * 10 + fchar - ASCII_ZERO;
        }
    } while (fchar != '\n');
    *output_arr = num;
    output_arr++;
    *output_arr = END_OF_NUMBERS;
}
