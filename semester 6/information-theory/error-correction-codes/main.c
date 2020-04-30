#include <stdio.h>
#include <stdlib.h>
#include "noise.h"
#define DATA_LENGTH 16

int main() {
	char data[DATA_LENGTH];
	noise(data, DATA_LENGTH * sizeof(char));
	printf("This is how data looks after applying noise: 0x");
	for (size_t i = 0; i < DATA_LENGTH; ++i) {
		printf("%02hhx", data[i]);
	}
	putchar('\n');
	return EXIT_SUCCESS;
}
