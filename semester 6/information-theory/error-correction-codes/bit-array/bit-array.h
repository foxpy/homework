#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef bool bit;
typedef struct bit_array {
	uint8_t *data;
	size_t len, cap;
	uint8_t bit;
} bits_t;

void bitarray_alloc(bits_t *bits);
void bitarray_free(bits_t *bits);
void bitarray_copy(bits_t *dst, bits_t *src);
size_t bitarray_size(bits_t *bits);
bool bitarray_empty(bits_t *bits);

void bitarray_push_front(bits_t *bits, bit b);
void bitarray_push_back(bits_t *bits, bit b);
void bitarray_pop_front(bits_t *bits);
void bitarray_pop_back(bits_t *bits);
bit bitarray_front(bits_t *bits);
bit bitarray_back(bits_t *bits);
