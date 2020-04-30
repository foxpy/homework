#include <stdio.h>
#include <stdlib.h>
#include "noise.h"
#define DATA_LENGTH 16

int main() {
	char data[DATA_LENGTH];
	noise_t ntype ;
	noise_cfg_t nconfig;

	ntype = NOISE_BIT_FLIP;
	nconfig.bit_flip.num_bit_flips = 2;
	apply_noise(data, DATA_LENGTH * sizeof(char), ntype, nconfig);
	printf("This is how data looks after applying bit flip noise: 0x");
	for (size_t i = 0; i < DATA_LENGTH; ++i) {
		printf("%02hhx", data[i]);
	}
	putchar('\n');

	ntype = NOISE_LINEAR;
	nconfig.linear.damage_length = 3;
	apply_noise(data, DATA_LENGTH * sizeof(char), ntype, nconfig);
	printf("This is how data looks after applying linear noise:   0x");
	for (size_t i = 0; i < DATA_LENGTH; ++i) {
		printf("%02hhx", data[i]);
	}
	putchar('\n');

	return EXIT_SUCCESS;
}
