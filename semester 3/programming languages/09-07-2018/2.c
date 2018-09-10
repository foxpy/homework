#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
	double A, B, C, D;
	puts("Ax^2+Bx+C=0");

	printf("Enter A: ");
	scanf("%lf", &A);

	printf("Enter B: ");
	scanf("%lf", &B);

	printf("Enter C: ");
	scanf("%lf", &C);

	D = B*B - 4*A*C;
	puts("Answers:");

	if (D < 0) {
		double re = -B/2/A;
		double im = sqrt(fabs(D))/2/A;
		printf("x1: %f+%fi,\nx2: %f-%fi.\n", re, im, re, im);
		return 0;
	}

	double x1 = (-B + sqrt(D))/2/A;
	double x2 = (-B - sqrt(D))/2/A;

	printf("x1: %f,\nx2: %f.\n", x1, x2);

	return 0;
}
