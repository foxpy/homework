#ifdef NDEBUG
#undef NDEBUG
#endif

#include <stdlib.h>
#include <assert.h>
#include "bit-array.h"
#include "hamming-code.h"

void test_encoding() {
	bit input_cases[] = {
		0, 0, 0, 0,
		1, 1, 1, 1,
		0, 1, 1, 0,
		1, 0, 1, 1,
	};
	bit output_cases[] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 0, 1, 1, 0, 0,
		1, 0, 1, 1, 0, 1, 0, 0,
	};
	bits_t in, out;
	bitarray_alloc(&in);
	bitarray_alloc(&out);
	for (int i = 0; i < 16; ++i) bitarray_push_back(&in, input_cases[i]);
	bitarray_push_back(&in, 0);
	assert(hamming_encode(&out, &in) == 4);
	assert(bitarray_size(&in) == 1);
	assert(bitarray_back(&in) == 0);
	assert(bitarray_size(&out) == 32);
	for (int i = 0; i < 32; ++i) assert(bitarray_next_front(&out) == output_cases[i]);
	bitarray_free(&in);
	bitarray_free(&out);
}

void test_decoding() {
	bit input_cases[] = {
		0, 0, 0, 0, 0, 1, 0, 0,
		1, 1, 0, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 1, 0, 0,
	};
	bit output_cases[] = {
		0, 0, 0, 0,
		1, 1, 1, 1,
		0, 1, 1, 0,
		1, 0, 1, 1,
	};
	bits_t in, out;
	bitarray_alloc(&in);
	bitarray_alloc(&out);
	for (int i = 0; i < 32; ++i) bitarray_push_back(&in, input_cases[i]);
	bitarray_push_back(&in, 0);
	assert(hamming_decode(&out, &in) == 0);
	assert(bitarray_size(&in) == 1);
	assert(bitarray_back(&in) == 0);
	assert(bitarray_size(&out) == 16);
	for (int i = 0; i < 16; ++i) assert(bitarray_next_front(&out) == output_cases[i]);
	bitarray_free(&in);
	bitarray_free(&out);
}

int main() {
	test_encoding();
	test_decoding();
	return EXIT_SUCCESS;
}
