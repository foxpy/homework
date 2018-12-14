#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	unsigned long state = 0xEAFF;
	int s, d, f, b;
	s = state & 0b1110000000000000; s >>= 13;
	d = state & 0b0000100000000000; d >>= 11;
	f = state & 0b0000001000000000; f >>= 9;
	b = state & 0b0000000011111111;
	printf("%d %d %d %d\n", s, d, f, b);
	return EXIT_SUCCESS;
}
