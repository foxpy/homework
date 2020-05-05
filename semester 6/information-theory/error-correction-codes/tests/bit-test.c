#include <stdbool.h>
#include <assert.h>
#include "bit-array.h"

int main() {
	bits_t bits;
	bits_t bits_copy;
	bitarray_alloc(&bits);

	assert(bitarray_empty(&bits) == true);

	bitarray_push_back(&bits, 1);
	assert(bitarray_empty(&bits) == false);
	assert(bitarray_size(&bits) == 1);
	assert(bitarray_back(&bits) == 1);
	assert(bitarray_front(&bits) == 1);

	bitarray_push_front(&bits, 0);
	assert(bitarray_size(&bits) == 2);
	assert(bitarray_back(&bits) == 1);
	assert(bitarray_front(&bits) == 0);

	bitarray_push_front(&bits, 1);
	assert(bitarray_size(&bits) == 3);
	assert(bitarray_back(&bits) == 1);
	assert(bitarray_front(&bits) == 1);

	bitarray_push_back(&bits, 0);
	assert(bitarray_size(&bits) == 4);
	assert(bitarray_back(&bits) == 0);
	assert(bitarray_front(&bits) == 1);

	for (int i = 0; i < 6; ++i) {
		bitarray_push_front(&bits, i % 2);
	}
	assert(bitarray_size(&bits) == 10);

	for (int i = 0; i < 6; ++i) {
		bitarray_push_back(&bits, i % 2);
	}
	assert(bitarray_size(&bits) == 16);

	bitarray_push_front(&bits, 0);
	bitarray_push_back(&bits, 0);
	bitarray_copy(&bits_copy, &bits);
	assert(bitarray_size(&bits) == 18);
	assert(bitarray_back(&bits) == 0);
	assert(bitarray_front(&bits) == 0);
	assert(bitarray_size(&bits_copy) == 18);
	assert(bitarray_back(&bits_copy) == 0);
	assert(bitarray_front(&bits_copy) == 0);

	for (int i = 0; i < 9; ++i) {
		bitarray_pop_back(&bits);
	}
	assert(bitarray_empty(&bits) == false);
	assert(bitarray_size(&bits) == 9);

	for (int i = 0; i < 9; ++i) {
		bitarray_pop_front(&bits);
	}
	assert(bitarray_empty(&bits) == true);
	assert(bitarray_size(&bits) == 0);

	bitarray_free(&bits);
	bitarray_free(&bits_copy);
	return EXIT_SUCCESS;
}
