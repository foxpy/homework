#ifdef NDEBUG
#undef NDEBUG
#endif

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bytes-to-string.h"
#include "emalloc.h"

#include <stdio.h>

int main() {
	char *data = "The quick brown fox jumps over the lazy dog\n";
	char *hexstring = (char*) emalloc(strlen(data)*2+1);
	char *bitstring = (char*) emalloc(strlen(data)*8+1);
	char *bitstring_predefined = "0010101000010110101001100000010010001110101011101001011011000110110101100000010001000110010011101111011011101110011101100000010001100110111101100001111000000100010101101010111010110110000011101100111000000100111101100110111010100110010011100000010000101110000101101010011000000100001101101000011001011110100111100000010000100110111101101110011001010000";
	char *hexstring_predefined = "54686520717569636b2062726f776e20666f78206a756d7073206f76657220746865206c617a7920646f670a";

	bytes_to_bitstring(bitstring, data, strlen(data));
	bytes_to_hexstring(hexstring, data, strlen(data));
	assert(strcmp(bitstring, bitstring_predefined) == 0);
	assert(strcmp(hexstring, hexstring_predefined) == 0);
	return EXIT_SUCCESS;
}
