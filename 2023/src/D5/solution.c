#include <stdio.h>
#include <stdlib.h>

#define SEEDS 25 
#define ASCII_ZERO 48
#define ASCII_ONE 57
#define TRUE 1
#define FALSE 0
#define END -1

void get_seeds(FILE *, long *, int *);
void map_seeds(FILE *, long *, int *);
long lowest_location_number(long *);

int main(int argc, char **argv) {
    /* Declare */
    int *seed_mapped, index;
    long *seeds;
    char fchar;
    FILE *fptr;

    /* Initialize */
    fptr = fopen(*(argv+1), "r");
    seeds = malloc(SEEDS * sizeof(long));
    seed_mapped = malloc(SEEDS * sizeof(int));

    get_seeds(fptr, seeds, seed_mapped);

    while (fchar = fgetc(fptr), fchar != EOF) {
        /* map label */
        fscanf(fptr, "%*s %*s:\n");

        /* reset seed mapped states */
        index = 0;
        while (*(seed_mapped+index) != END) {
            *(seed_mapped+index) = FALSE;
            index++;
        }
        printf("%ld %ld %ld %ld\n", *seeds, *(seeds+1), *(seeds+2), *(seeds+3));

        map_seeds(fptr, seeds, seed_mapped);
    }

    printf("Lowest location: %ld\n", lowest_location_number(seeds));

    fclose(fptr);
    free(seeds);
	return EXIT_SUCCESS;
}

void get_seeds(FILE *fptr, long *seeds_arr, int *map_bool_arr) {
    char fchar;
    int is_num;
    long num;

    /* Consume */
    fscanf(fptr, "seeds: ");

    num = 0;
    do {
       fchar = fgetc(fptr);
       is_num = fchar >= ASCII_ZERO && fchar <= ASCII_ONE;
       if (is_num) {
           num = num * 10 + fchar - ASCII_ZERO;
       } else {
           *(seeds_arr) = num;
           seeds_arr++;
           map_bool_arr++;
           num = 0;
       }
    } while (fchar != '\n');

    *(seeds_arr) = END;
    *(map_bool_arr) = END;
}

void map_seeds(FILE *fptr, long *seeds_arr, int *seed_been_mapped) {
    char scanf_ret;
    long destination, source, length, difference;
    int index, within_source;

    while(scanf_ret = fscanf(fptr, "%ld %ld %ld\n", &destination, &source, &length), scanf_ret == 3 && scanf_ret != EOF) {
        difference = source - destination;
        index = 0;

        while (*(seeds_arr+index) != END) {
            within_source = *(seeds_arr+index) > source && *(seeds_arr+index) < source + length;
            if (within_source && !*(seed_been_mapped+index)) {
                *(seeds_arr+index) = *(seeds_arr+index) - difference;
                *(seed_been_mapped+index) = TRUE;
            }
            index++;
        }
    }
}

long lowest_location_number(long *seeds) {
    long lowest = *seeds;
    while (*seeds != END) {
        if (*seeds < lowest) {
            lowest = *seeds;
        }
        seeds++;
    }
    return lowest;
}
