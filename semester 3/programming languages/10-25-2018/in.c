#include <stdio.h>
#include <stdlib.h>

int parse(int s, int d, int f, int b, unsigned long *state) {
	if ((s > 0b111) || (d > 0b1) || (f > 0b1) || (b > 0xff)) {
		return EXIT_FAILURE;
	}

	*state |= s; *state <<= 2;
	*state |= d; *state <<= 2;
	*state |= f; *state <<= 9;
	*state |= b;
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
	int s, d, f, b;
	unsigned long state = 0;
	scanf("%d%d%d%d", &s, &d, &f, &b);

	if (parse(s, d, f, b, &state) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	printf("0x%lx\n", state);
	return EXIT_SUCCESS;
}
