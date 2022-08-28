#ifdef NDEBUG
#undef NDEBUG
#endif

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bit-array.h"
#include "interleaver.h"

static char msg[] = "123456789\n123456789"; // 20 bytes with null-terminator

void test_loop(size_t length, size_t width) {
	bits_t input, interleaved, output;
	interleaver_t *intr;
	char *decoded;
	size_t nbits, nbytes;
	bitarray_alloc(&input);
	bitarray_alloc(&interleaved);
	bitarray_alloc(&output);

	bitarray_fill_from_memory(&input, msg, sizeof(msg)*8);
	intr = interleaver_init(INTERLEAVER_ENCODE, length, width);
	interleaver_process_data(&interleaved, &input, intr);
	interleaver_free(intr);
	intr = interleaver_init(INTERLEAVER_DECODE, length, width);
	interleaver_process_data(&output, &interleaved, intr);
	interleaver_free(intr);
	decoded = bitarray_to_memory(&output, &nbits, &nbytes);
	assert(strcmp(decoded, msg) == 0);
	free(decoded);

	bitarray_free(&input);
	bitarray_free(&interleaved);
	bitarray_free(&output);
}

void invalid_test() {
	assert(interleaver_init(INTERLEAVER_ENCODE, 16, 1) == NULL);
	assert(interleaver_init(INTERLEAVER_ENCODE, 0, 8) == NULL);
	assert(interleaver_init(INTERLEAVER_ENCODE, 9000LLU * 9000 * 9000, 9000LLU * 9000 * 9000) == NULL);
}

int main() {
	test_loop(1, 2);
	test_loop(1, 4);
	test_loop(1, 5);
	test_loop(2, 2);
	invalid_test();
	return EXIT_SUCCESS;
}
