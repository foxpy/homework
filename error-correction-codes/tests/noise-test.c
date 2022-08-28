#ifdef NDEBUG
#undef NDEBUG
#endif

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "noise.h"
#include "util.h"

char original_message[] =
"The quick brown fox jumps over the lazy dog\n"
"The quick brown fox jumps over the lazy dog\n"
"The quick brown fox jumps over the lazy dog\n"
"The quick brown fox jumps over the lazy dog\n"
"The quick brown fox jumps over the lazy dog\n"
"The quick brown fox jumps over the lazy dog\n"
"The quick brown fox jumps over the lazy dog\n"
"The quick brown fox jumps over the lazy dog\n"
"The quick brown fox jumps over the lazy dog\n"
"The quick brown fox jumps over the lazy dog\n";

int main() {
	noise_t* gen;
	bits_t in, out;
	size_t nbits, nbytes;
	char *damaged_message;
	bitarray_alloc(&in);
	bitarray_alloc(&out);

	bitarray_fill_from_memory(&in, original_message, strlen(original_message) * 8);
	gen = noise_init_bit_flip(0.0);
	assert(noise_apply(&out, &in, gen) == 0);
	damaged_message = bitarray_to_memory(&out, &nbits, &nbytes);
	assert(memcmp(original_message, damaged_message, strlen(original_message)) == 0);
	free(damaged_message);
	noise_free(gen);

	bitarray_fill_from_memory(&in, original_message, strlen(original_message) * 8);
	gen = noise_init_bit_flip(0.1);
	assert(noise_apply(&out, &in, gen) > 0);
	damaged_message = bitarray_to_memory(&out, &nbits, &nbytes);
	assert(memcmp(original_message, damaged_message, strlen(original_message)) != 0);
	free(damaged_message);
	noise_free(gen);

	bitarray_fill_from_memory(&in, original_message, strlen(original_message) * 8);
	gen = noise_init_temporal(2);
	assert(noise_apply(&out, &in, gen) > 0);
	damaged_message = bitarray_to_memory(&out, &nbits, &nbytes);
	assert(memcmp(original_message, damaged_message, strlen(original_message)) != 0);
	free(damaged_message);
	noise_free(gen);

	bitarray_fill_from_memory(&in, original_message, strlen(original_message) * 8);
	gen = noise_init_burst(NOISE_BURST_UP, 0.01, 4, 2);
	assert(noise_apply(&out, &in, gen) > 0);
	damaged_message = bitarray_to_memory(&out, &nbits, &nbytes);
	assert(memcmp(original_message, damaged_message, strlen(original_message)) != 0);
	free(damaged_message);
	noise_free(gen);

	bitarray_fill_from_memory(&in, original_message, strlen(original_message) * 8);
	gen = noise_init_burst(NOISE_BURST_DOWN, 0.01, 6, 2);
	assert(noise_apply(&out, &in, gen) > 0);
	damaged_message = bitarray_to_memory(&out, &nbits, &nbytes);
	assert(memcmp(original_message, damaged_message, strlen(original_message)) != 0);
	free(damaged_message);
	noise_free(gen);

	bitarray_free(&in);
	bitarray_free(&out);
	return EXIT_SUCCESS;
}
