#ifdef NDEBUG
#undef NDEBUG
#endif

#include <stdlib.h>
#include <assert.h>
#include "bit-array.h"
#include "repetition-code.h"

void test_encode() {
	bits_t input;
	bits_t output;
	bitarray_alloc(&input);
	bitarray_alloc(&output);
	bitarray_push_back(&input, 1);
	bitarray_push_back(&input, 0);
	bitarray_push_back(&input, 1);
	repetition_encode(&output, &input);
	assert(bitarray_empty(&input));
	for (int i = 0; i < 3; ++i) {
		assert(bitarray_back(&output) == 1);
		bitarray_pop_back(&output);
	}
	for (int i = 0; i < 3; ++i) {
		assert(bitarray_back(&output) == 0);
		bitarray_pop_back(&output);
	}
	for (int i = 0; i < 3; ++i) {
		assert(bitarray_back(&output) == 1);
		bitarray_pop_back(&output);
	}
	assert(bitarray_empty(&output));
	bitarray_free(&input);
	bitarray_free(&output);
}

void test_decode() {
	bits_t encoded, decoded;
	bitarray_alloc(&encoded);
	bitarray_alloc(&decoded);
	bit input[24] = {
		0, 0, 0,
		0, 0, 1,
		0, 1, 0,
		0, 1, 1,
		1, 0, 0,
		1, 0, 1,
		1, 1, 0,
		1, 1, 1,
	};
	bit expected_output[8] = { 0, 0, 0, 1, 0, 1, 1, 1, };
	for (int i = 0; i < 24; ++i) bitarray_push_back(&encoded, input[i]);
	repetition_decode(&decoded, &encoded);
	for (int i = 0; i < 8; ++i) {
		assert(bitarray_front(&decoded) == expected_output[i]);
		bitarray_pop_front(&decoded);
	}
	bitarray_free(&encoded);
	bitarray_free(&decoded);
}

void test_encode_decode() {
	bits_t data, encoded, decoded;
	bitarray_alloc(&data);
	bitarray_alloc(&encoded);
	bitarray_alloc(&decoded);
	bitarray_push_back(&data, 0);
	bitarray_push_back(&data, 0);
	bitarray_push_back(&data, 1);
	repetition_encode(&encoded, &data);
	assert(bitarray_empty(&data));
	repetition_decode(&decoded, &encoded);
	assert(bitarray_empty(&encoded));
	assert(bitarray_front(&decoded) == 0);
	bitarray_pop_front(&decoded);
	assert(bitarray_front(&decoded) == 0);
	bitarray_pop_front(&decoded);
	assert(bitarray_front(&decoded) == 1);
	bitarray_pop_front(&decoded);
	bitarray_free(&data);
	bitarray_free(&encoded);
	bitarray_free(&decoded);
}

int main() {
	test_encode();
	test_decode();
	test_encode_decode();
	return EXIT_SUCCESS;
}
