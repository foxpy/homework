#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
	float A, B, C, D, x1, x2;
	puts("Ax^2+Bx+C=0");

	printf("Enter A: ");
	scanf("%f", &A);

	printf("Enter B: ");
	scanf("%f", &B);

	printf("Enter C: ");
	scanf("%f", &C);

	D = B*B - 4*A*C;
	puts("Answers:");

	if (D < 0) {
		// We are basically reusing existing variable for imaginary part
		x1 = -B/2/A;
		x2 = sqrt(fabs(D))/2/A;
		printf("x1: %f+%fi,\nx2: %f-%fi.\n", x1, x2, x1, x2);
		return 0;
	}

	x1 = (-B + sqrt(D))/2/A;
	x2 = (-B - sqrt(D))/2/A;

	printf("x1: %f,\nx2: %f.\n", x1, x2);

	return 0;
}
