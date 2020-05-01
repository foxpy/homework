#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noise.h"

int main() {
	char message[] = "The quick brown fox jumps over the lazy dog";
	noise_t ntype ;
	noise_cfg_t nconfig;
	printf("Original message:                                        %s\n", message);

	ntype = NOISE_BIT_FLIP;
	nconfig.bit_flip.num_bit_flips = 2;
	apply_noise(message, strlen(message), ntype, nconfig);
	printf("This is how message looks after applying bit flip noise: %s\n", message);

	ntype = NOISE_LINEAR;
	nconfig.linear.damage_length = 15;
	apply_noise(message, strlen(message), ntype, nconfig);
	printf("This is how message looks after applying linear noise:   %s\n", message);

	return EXIT_SUCCESS;
}
