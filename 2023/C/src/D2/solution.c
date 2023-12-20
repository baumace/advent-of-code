#include <stdio.h>
#include <stdlib.h>

#define MAX_STR_LENGTH 200
#define NUM_RED 12
#define NUM_GREEN 13
#define NUM_BLUE 14
#define FALSE 0
#define TRUE 1

char update_color_count_set(FILE *, int *, int *, int *);

int main(int argc, char **argv) {
	/* Variable declarations */ 
	FILE *fptr;
	char fchar;
	int game_id, game_id_sum = 0, red_count = 0, green_count = 0, blue_count = 0, game_possible;
	int minimum_set_powers_sum = 0, red_max= 0, green_max = 0, blue_max = 0;
	fptr = fopen(*(argv+1), "r");

	do {
		fscanf(fptr, "Game %d:", &game_id); 
		game_possible = TRUE;

		/* Evalute a line */
		fchar = fgetc(fptr);
		while (fchar != '\n' && fchar != EOF) {
			fchar = update_color_count_set(fptr, &red_count, &green_count, &blue_count);

			/* Update maximums */
			if (red_count > red_max) {
				red_max = red_count;
			}
			if (green_count > green_max) {
				green_max = green_count;
			}
			if (blue_count > blue_max) {
				blue_max = blue_count;
			}

			/* Same set? */
			if (fchar == ',') {
				fgetc(fptr);
			} else {
				/* Verify if possible */
				if (red_count > NUM_RED || green_count > NUM_GREEN || blue_count > NUM_BLUE) {
					game_possible = FALSE;
				}

				/* End of game */
				if (fchar == '\n') {
					if (game_possible) {
						game_id_sum += game_id;
					}
					minimum_set_powers_sum += red_max * green_max * blue_max;
					red_max = 0, green_max = 0, blue_max = 0;
				}

				/* Reset color counts */
				red_count = 0, green_count = 0, blue_count = 0;
			}
		}

	} while (fchar != EOF);

	printf("ID sums: %d\n", game_id_sum);
	printf("Power sums: %d\n", minimum_set_powers_sum);
	
	/* Close and exit */ 
	fclose(fptr);
	return EXIT_SUCCESS;
}

/* takes in with format {num} {color}... */
char update_color_count_set(FILE *fptr, int *red, int *green, int *blue) {
	char color, fchar;
	int num_cubes;

	fscanf(fptr, "%d %c", &num_cubes, &color);

	switch (color) {
		case 'r':
			*red += num_cubes;
			break;
		case 'g':
			*green += num_cubes;
			break;
		case 'b':
			*blue += num_cubes;
			break;
	}

	/* Consume remaining set */
	while (fchar = fgetc(fptr), fchar != ',' && fchar != ';' && fchar != '\n') {
	}

	return fchar;
}
