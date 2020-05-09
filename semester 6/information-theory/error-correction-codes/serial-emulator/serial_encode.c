#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "bit-array.h"
#include "serial.h"

#define START_BIT 0
#define STOP_BIT 1

static bit next_bit(bits_t *bits) {
	bit b;
	if (bitarray_empty(bits)) {
		return 0;
	} else {
		b = bitarray_front(bits);
		bitarray_pop_front(bits);
		return b;
	}
}

static bit parity(uint8_t sum, enum parity_bit ptype) {
	if (ptype == PARITY_EVEN) {
		return (sum % 2) == 0;
	} else {
		return (sum % 2) == 1;
	}
}

void serial_encode(bits_t *dst, bits_t *src, serial_cfg_t *cfg) {
	uint8_t sum = 0;
	bit b;
	while (!bitarray_empty(src)) {
		bitarray_push_back(dst, START_BIT);
		for (unsigned char i = 0; i < cfg->data_bits; ++i) {
			b = next_bit(src);
			bitarray_push_back(dst, b);
			sum += b;
		}
		if (cfg->parity_bit != PARITY_NONE) {
			bitarray_push_back(dst, parity(sum, cfg->parity_bit));
		}
		sum = 0;
		for (unsigned char i = 0; i < cfg->stop_bits; ++i) {
			bitarray_push_back(dst, STOP_BIT);
		}
	}
}
