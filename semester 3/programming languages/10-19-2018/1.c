#include <stdio.h>
#include <time.h>

#define MATRIX_SIZE_X 3
#define MATRIX_SIZE_Y 3
#define MATRIX \
 {{3,  3, -5, -1}, \
  {2, -1,  3, 13}, \
  {1,  2, -1, 9}}

int main(int argc, char *argv[]) {
	double matrix[MATRIX_SIZE_X][MATRIX_SIZE_Y+1] = MATRIX;

	clock_t start_time = clock();
	for (int step = 0; step < MATRIX_SIZE_X; step++) {
		double mult = matrix[step][step];
		for (int y = 0; y < MATRIX_SIZE_Y+1; y++) {
			matrix[step][y] /= mult;
		}
		for (int x = 0; x < MATRIX_SIZE_X; x++) {
			if (x != step) {
				mult = matrix[x][step];
				for(int y = 0; y < MATRIX_SIZE_Y+1; y++) {
					matrix[x][y] -= matrix[step][y]*mult;
				}
			}
		}
	}
	double elapsed_time = (clock() - start_time);

	puts("Answers:");
	for (int i = 0; i < MATRIX_SIZE_X; i++) {
		printf("x%d = %.2f\n", i+1, matrix[i][MATRIX_SIZE_Y]);
	}

	printf("Time elapsed: %.0f microseconds.\n",
		elapsed_time / CLOCKS_PER_SEC*1000000);
	return 0;
}
