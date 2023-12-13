#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 5
#define END_OF_NUMBERS -1
#define ASCII_ZERO 48
#define ASCII_ONE 57

void get_numbers(FILE *, int *);

int main(int argc, char **argv) {
    /* Declare */
    FILE *fptr;
    int *times, *times_traversal, *distances, *distances_traversal;
    int permutation_num, permutation_distance, min_product, min_record, max_record;

    /* Initialize */
    fptr = fopen(*(argv+1), "r");
    times = malloc(MAX_NUMBERS * sizeof(int));
    distances = malloc(MAX_NUMBERS * sizeof(int));

    get_numbers(fptr, times);
    get_numbers(fptr, distances);

    times_traversal = times;
    distances_traversal = distances;
    min_product = 1;
    while (*times_traversal != END_OF_NUMBERS) {
        permutation_num = 0;
        min_record = -1;
        while (permutation_num < *times_traversal) {
            permutation_distance = permutation_num*(*times_traversal - permutation_num);
            if (permutation_distance > *distances_traversal) {
                if (min_record == -1) {
                    min_record = permutation_num;
                }
                max_record = permutation_num;
            }
            permutation_num++;
        }
        if (max_record - min_record > 0) {
            min_product *= (max_record-min_record+1);
        }
        times_traversal++;
        distances_traversal++;
    }

    printf("%d\n", min_product);

    fclose(fptr);
    free(times);
    free(distances);
	return EXIT_SUCCESS;
}

void get_numbers(FILE *fptr, int *output_arr) {
    char fchar;
    int num, is_num, spaces_run;

    fscanf(fptr, "%*s: ");

    num = 0;
    spaces_run = 2;
    do {
        fchar = fgetc(fptr);
        is_num = fchar >= ASCII_ZERO && fchar <= ASCII_ONE;
        if (is_num) {
            spaces_run = 0;
            num = num * 10 + fchar - ASCII_ZERO;
        } else {
            spaces_run++;
            if (spaces_run == 1) {
                *output_arr = num;
                output_arr++;
                num = 0;
            }
        }
    } while (fchar != '\n');
    *output_arr = END_OF_NUMBERS;
}
