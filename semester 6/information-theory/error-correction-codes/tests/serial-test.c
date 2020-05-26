#ifdef NDEBUG
#undef NDEBUG
#endif

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include "bit-array.h"
#include "serial.h"
#include "bytes-to-string.h"
#include "emalloc.h"

int main() {
	bits_t input, encoded, decoded;
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
	assert(serial_packet_length(&cfg) == 10);
	assert(serial_encode(&encoded, &input, &cfg) == 4);
	memory = (uint8_t*) bitarray_to_memory(&encoded, &nbits, &nbytes);
	bitstring = (char*) emalloc(nbytes*8+1);
	bytes_to_bitstring(bitstring, memory, nbytes);
	assert(strncmp(bitstring, "0100011101011101110101010011010010011101", 40) == 0);
	free(bitstring);
	free(memory);
	bitarray_free(&encoded);
	bitarray_free(&input);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_7;
	cfg.parity_bit = PARITY_NONE;
	cfg.stop_bits = STOP_BITS_1;
	assert(serial_packet_length(&cfg) == 9);
	assert(serial_encode(&encoded, &input, &cfg) == 4);
	memory = (uint8_t*) bitarray_to_memory(&encoded, &nbits, &nbytes);
	bitstring = (char*) emalloc(nbytes*8+1);
	bytes_to_bitstring(bitstring, memory, nbytes);
	assert(strncmp(bitstring, "010001111001110111010101001011001001", 36) == 0);
	free(bitstring);
	free(memory);
	bitarray_free(&encoded);
	bitarray_free(&input);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_5;
	cfg.parity_bit = PARITY_NONE;
	cfg.stop_bits = STOP_BITS_1;
	assert(serial_packet_length(&cfg) == 7);
	assert(serial_encode(&encoded, &input, &cfg) == 6);
	memory = (uint8_t*) bitarray_to_memory(&encoded, &nbits, &nbytes);
	bitstring = (char*) emalloc(nbytes*8+1);
	bytes_to_bitstring(bitstring, memory, nbytes);
	assert(strncmp(bitstring, "010001101101110101111001010100110010100111", 42) == 0);
	free(bitstring);
	free(memory);
	bitarray_free(&encoded);
	bitarray_free(&input);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_9;
	cfg.parity_bit = PARITY_NONE;
	cfg.stop_bits = STOP_BITS_1;
	assert(serial_packet_length(&cfg) == 11);
	assert(serial_encode(&encoded, &input, &cfg) == 3);
	memory = (uint8_t*) bitarray_to_memory(&encoded, &nbits, &nbytes);
	bitstring = (char*) emalloc(nbytes*8+1);
	bytes_to_bitstring(bitstring, memory, nbytes);
	assert(strncmp(bitstring, "010001110110110111010101001100101", 33) == 0);
	free(bitstring);
	free(memory);
	bitarray_free(&encoded);
	bitarray_free(&input);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_8;
	cfg.parity_bit = PARITY_NONE;
	cfg.stop_bits = STOP_BITS_2;
	assert(serial_packet_length(&cfg) == 11);
	assert(serial_encode(&encoded, &input, &cfg) == 4);
	memory = (uint8_t*) bitarray_to_memory(&encoded, &nbits, &nbytes);
	bitstring = (char*) emalloc(nbytes*8+1);
	bytes_to_bitstring(bitstring, memory, nbytes);
	assert(strncmp(bitstring, "01000111011011101110110101001101100100111011", 44) == 0);
	free(bitstring);
	free(memory);
	bitarray_free(&encoded);
	bitarray_free(&input);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_fill_from_memory(&input, "qw12", 32);
	cfg.data_bits = DATA_BITS_8;
	cfg.parity_bit = PARITY_ODD;
	cfg.stop_bits = STOP_BITS_1;
	assert(serial_packet_length(&cfg) == 11);
	assert(serial_encode(&encoded, &input, &cfg) == 4);
	memory = (uint8_t*) bitarray_to_memory(&encoded, &nbits, &nbytes);
	bitstring = (char*) emalloc(nbytes*8+1);
	bytes_to_bitstring(bitstring, memory, nbytes);
	assert(strncmp(bitstring, "01000111001011101110010100011001100100110011", 44) == 0);
	free(bitstring);
	free(memory);
	bitarray_free(&encoded);
	bitarray_free(&input);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_fill_from_memory(&input, "qw12", 32);
	cfg.data_bits = DATA_BITS_8;
	cfg.parity_bit = PARITY_EVEN;
	cfg.stop_bits = STOP_BITS_1;
	assert(serial_packet_length(&cfg) == 11);
	assert(serial_encode(&encoded, &input, &cfg) == 4);
	memory = (uint8_t*) bitarray_to_memory(&encoded, &nbits, &nbytes);
	bitstring = (char*) emalloc(nbytes*8+1);
	bytes_to_bitstring(bitstring, memory, nbytes);
	assert(strncmp(bitstring, "01000111011011101110110100011000100100110001", 44) == 0);
	free(bitstring);
	free(memory);
	bitarray_free(&encoded);
	bitarray_free(&input);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_alloc(&decoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_8;
	cfg.parity_bit = PARITY_NONE;
	cfg.stop_bits = STOP_BITS_1;
	assert(serial_packet_length(&cfg) == 10);
	assert(serial_encode(&encoded, &input, &cfg) == 4);
	assert(serial_decode(&decoded, &encoded, &cfg) == 0);
	memory = (uint8_t*) bitarray_to_memory(&decoded, &nbits, &nbytes);
	assert(strncmp((char*) memory, "qwer", 4) == 0);
	free(memory);
	bitarray_free(&input);
	bitarray_free(&encoded);
	bitarray_free(&decoded);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_alloc(&decoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_7;
	cfg.parity_bit = PARITY_NONE;
	cfg.stop_bits = STOP_BITS_1;
	assert(serial_packet_length(&cfg) == 9);
	assert(serial_encode(&encoded, &input, &cfg) == 4);
	assert(serial_decode(&decoded, &encoded, &cfg) == 0);
	memory = (uint8_t*) bitarray_to_memory(&decoded, &nbits, &nbytes);
	assert(strncmp((char*) memory, "qwe", 3) == 0);
	free(memory);
	bitarray_free(&input);
	bitarray_free(&encoded);
	bitarray_free(&decoded);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_alloc(&decoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_5;
	cfg.parity_bit = PARITY_NONE;
	cfg.stop_bits = STOP_BITS_1;
	assert(serial_packet_length(&cfg) == 7);
	assert(serial_encode(&encoded, &input, &cfg) == 6);
	assert(serial_decode(&decoded, &encoded, &cfg) == 0);
	memory = (uint8_t*) bitarray_to_memory(&decoded, &nbits, &nbytes);
	assert(strncmp((char*) memory, "qwe", 3) == 0);
	free(memory);
	bitarray_free(&input);
	bitarray_free(&encoded);
	bitarray_free(&decoded);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_alloc(&decoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_9;
	cfg.parity_bit = PARITY_NONE;
	cfg.stop_bits = STOP_BITS_1;
	assert(serial_packet_length(&cfg) == 11);
	assert(serial_encode(&encoded, &input, &cfg) == 3);
	assert(serial_decode(&decoded, &encoded, &cfg) == 0);
	memory = (uint8_t*) bitarray_to_memory(&decoded, &nbits, &nbytes);
	assert(strncmp((char*) memory, "qwe", 3) == 0);
	free(memory);
	bitarray_free(&input);
	bitarray_free(&encoded);
	bitarray_free(&decoded);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_alloc(&decoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_8;
	cfg.parity_bit = PARITY_EVEN;
	cfg.stop_bits = STOP_BITS_1;
	assert(serial_packet_length(&cfg) == 11);
	assert(serial_encode(&encoded, &input, &cfg) == 4);
	assert(serial_decode(&decoded, &encoded, &cfg) == 0);
	memory = (uint8_t*) bitarray_to_memory(&decoded, &nbits, &nbytes);
	assert(strncmp((char*) memory, "qwer", 4) == 0);
	free(memory);
	bitarray_free(&input);
	bitarray_free(&encoded);
	bitarray_free(&decoded);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_alloc(&decoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_8;
	cfg.parity_bit = PARITY_EVEN;
	cfg.stop_bits = STOP_BITS_2;
	assert(serial_packet_length(&cfg) == 12);
	assert(serial_encode(&encoded, &input, &cfg) == 4);
	assert(serial_decode(&decoded, &encoded, &cfg) == 0);
	memory = (uint8_t*) bitarray_to_memory(&decoded, &nbits, &nbytes);
	assert(strncmp((char*) memory, "qwer", 4) == 0);
	free(memory);
	bitarray_free(&input);
	bitarray_free(&encoded);
	bitarray_free(&decoded);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_alloc(&decoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_8;
	cfg.parity_bit = PARITY_ODD;
	cfg.stop_bits = STOP_BITS_2;
	assert(serial_packet_length(&cfg) == 12);
	assert(serial_encode(&encoded, &input, &cfg) == 4);
	assert(serial_decode(&decoded, &encoded, &cfg) == 0);
	memory = (uint8_t*) bitarray_to_memory(&decoded, &nbits, &nbytes);
	assert(strncmp((char*) memory, "qwer", 4) == 0);
	free(memory);
	bitarray_free(&input);
	bitarray_free(&encoded);
	bitarray_free(&decoded);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_alloc(&decoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_8;
	cfg.parity_bit = PARITY_ODD;
	cfg.stop_bits = STOP_BITS_2;
	assert(serial_packet_length(&cfg) == 12);
	assert(serial_encode(&encoded, &input, &cfg) == 4);
	bitarray_push_back(&encoded, 1);
	bitarray_push_back(&encoded, 0);
	bitarray_push_back(&encoded, 1);
	assert(serial_decode(&decoded, &encoded, &cfg) == 0);
	assert(bitarray_next_back(&encoded) == 1);
	assert(bitarray_next_back(&encoded) == 0);
	assert(bitarray_next_back(&encoded) == 1);
	memory = (uint8_t*) bitarray_to_memory(&decoded, &nbits, &nbytes);
	assert(strncmp((char*) memory, "qwer", 4) == 0);
	free(memory);
	bitarray_free(&input);
	bitarray_free(&encoded);
	bitarray_free(&decoded);

	bitarray_alloc(&input);
	bitarray_alloc(&encoded);
	bitarray_alloc(&decoded);
	bitarray_fill_from_memory(&input, "qwer", 32);
	cfg.data_bits = DATA_BITS_8;
	cfg.parity_bit = PARITY_NONE;
	cfg.stop_bits = STOP_BITS_1;
	assert(serial_packet_length(&cfg) == 10);
	assert(serial_encode(&encoded, &input, &cfg) == 4);
	memory = (uint8_t*) bitarray_to_memory(&encoded, &nbits, &nbytes);
	memory[0] |= 0b00000001; // damage first packet
	bitarray_fill_from_memory(&encoded, memory, nbits);
	assert(serial_decode(&decoded, &encoded, &cfg) == 1);
	free(memory);
	bitarray_free(&input);
	bitarray_free(&encoded);
	bitarray_free(&decoded);

	return EXIT_SUCCESS;
}
