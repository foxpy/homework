#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include "bit-array.h"
#include "serial.h"
#include "bytes-to-string.h"
#include "emalloc.h"

int main() {
	bits_t input, encoded;
	size_t nbits, nbytes;
	uint8_t *memory;
	char *bitstring;
	serial_cfg_t cfg;

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_8;
	cfg.parity_bit = PARITY_NONE;
	cfg.stop_bits = STOP_BITS_1;
	serial_encode(&encoded, &input, &cfg);
	memory = (uint8_t*) bitarray_to_memory(&encoded, &nbits, &nbytes);
	bitstring = (char*) emalloc(nbytes*8+1);
	bytes_to_bitstring(bitstring, memory, nbytes);
	assert(strncmp(bitstring, "0100011101011101110101010011010010011101", 40) == 0);
	free(bitstring);
	free(memory);
	bitarray_clear(&input);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_7;
	cfg.parity_bit = PARITY_NONE;
	cfg.stop_bits = STOP_BITS_1;
	serial_encode(&encoded, &input, &cfg);
	memory = (uint8_t*) bitarray_to_memory(&encoded, &nbits, &nbytes);
	bitstring = (char*) emalloc(nbytes*8+1);
	bytes_to_bitstring(bitstring, memory, nbytes);
	assert(strncmp(bitstring, "010001111001110111010101001011001001011100001", 45) == 0);
	free(bitstring);
	free(memory);
	bitarray_clear(&input);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_5;
	cfg.parity_bit = PARITY_NONE;
	cfg.stop_bits = STOP_BITS_1;
	serial_encode(&encoded, &input, &cfg);
	memory = (uint8_t*) bitarray_to_memory(&encoded, &nbits, &nbytes);
	bitstring = (char*) emalloc(nbytes*8+1);
	bytes_to_bitstring(bitstring, memory, nbytes);
	assert(strncmp(bitstring, "0100011011011101011110010101001100101001110100001", 49) == 0);
	free(bitstring);
	free(memory);
	bitarray_clear(&input);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_9;
	cfg.parity_bit = PARITY_NONE;
	cfg.stop_bits = STOP_BITS_1;
	serial_encode(&encoded, &input, &cfg);
	memory = (uint8_t*) bitarray_to_memory(&encoded, &nbits, &nbytes);
	bitstring = (char*) emalloc(nbytes*8+1);
	bytes_to_bitstring(bitstring, memory, nbytes);
	assert(strncmp(bitstring, "01000111011011011101010100110010100111000001", 44) == 0);
	free(bitstring);
	free(memory);
	bitarray_clear(&input);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_8;
	cfg.parity_bit = PARITY_NONE;
	cfg.stop_bits = STOP_BITS_2;
	serial_encode(&encoded, &input, &cfg);
	memory = (uint8_t*) bitarray_to_memory(&encoded, &nbits, &nbytes);
	bitstring = (char*) emalloc(nbytes*8+1);
	bytes_to_bitstring(bitstring, memory, nbytes);
	assert(strncmp(bitstring, "01000111011011101110110101001101100100111011", 44) == 0);
	free(bitstring);
	free(memory);
	bitarray_clear(&input);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_fill_from_memory(&input, "qw12", 32);
	cfg.data_bits = DATA_BITS_8;
	cfg.parity_bit = PARITY_ODD;
	cfg.stop_bits = STOP_BITS_1;
	serial_encode(&encoded, &input, &cfg);
	memory = (uint8_t*) bitarray_to_memory(&encoded, &nbits, &nbytes);
	bitstring = (char*) emalloc(nbytes*8+1);
	bytes_to_bitstring(bitstring, memory, nbytes);
	assert(strncmp(bitstring, "01000111001011101110010100011001100100110011", 44) == 0);
	free(bitstring);
	free(memory);
	bitarray_clear(&input);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_fill_from_memory(&input, "qw12", 32);
	cfg.data_bits = DATA_BITS_8;
	cfg.parity_bit = PARITY_EVEN;
	cfg.stop_bits = STOP_BITS_1;
	serial_encode(&encoded, &input, &cfg);
	memory = (uint8_t*) bitarray_to_memory(&encoded, &nbits, &nbytes);
	bitstring = (char*) emalloc(nbytes*8+1);
	bytes_to_bitstring(bitstring, memory, nbytes);
	assert(strncmp(bitstring, "01000111011011101110110100011000100100110001", 44) == 0);
	free(bitstring);
	free(memory);
	bitarray_clear(&input);

	return EXIT_SUCCESS;
}