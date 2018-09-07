#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	float A, B, C, D;
	puts("Ax^2+Bx+C=0");

	printf("Enter A: ");
	scanf("%f", &A);

	printf("Enter B: ");
	scanf("%f", &B);

	printf("Enter C: ");
	scanf("%f", &C);

	D = B*B - 4*A*C;

	if (D < 0) {
		puts("Sorry. I cannot solve this equation.");
		puts("Basically because I know nothing about imaginary numbers. :)");
		exit(1);
	}

	printf("Calculated D: %f.\n", D);

	return 0;
}
