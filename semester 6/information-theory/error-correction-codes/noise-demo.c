#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "noise.h"
#include "bytes-to-string.h"

#define PRINT_MESSAGE(str) { \
	fputs(str, stdout); \
	fwrite(message, sizeof(char), sizeof(message)/sizeof(char), stdout); \
	bytes_to_bitstring(bitstring, message, sizeof(message)); \
	bytes_to_hexstring(hexstring, message, sizeof(message)); \
	printf("\n0b%s\n0x%s\n", bitstring, hexstring); \
}

int main() {
	noise_t ntype ;
	noise_cfg_t nconfig;
	char message[] = "The quick";
	char *bitstring = (char*) emalloc(sizeof(message)*8+1);
	char *hexstring = (char*) emalloc(sizeof(message)*2+1);

	PRINT_MESSAGE("Original message: ");

	ntype = NOISE_BIT_FLIP;
	nconfig.bit_flip.num_bit_flips = 1;
	apply_noise(message, strlen(message), ntype, nconfig);
	PRINT_MESSAGE("After bit flip: ");

	ntype = NOISE_LINEAR;
	nconfig.linear.damage_length = 4;
	apply_noise(message, strlen(message), ntype, nconfig);
	PRINT_MESSAGE("After linear noise: ");

	free(bitstring);
	free(hexstring);
	return EXIT_SUCCESS;
}
