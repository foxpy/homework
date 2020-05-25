#include <stdlib.h>
#include <stdint.h>
#include "bit-array.h"
#include "serial.h"
#include "serial_impl.h"

size_t serial_decode(bits_t *dst, bits_t *src, serial_cfg_t *cfg) {
	size_t ret = 0;
	int dirty = 0;
	uint8_t sum;
	bits_t data;
	bit b;
	bitarray_alloc(&data);
	while (!bitarray_empty(src)) {
		sum = 0;
		dirty = 0;
		b = bitarray_next_front(src);
		if (b != START_BIT) dirty = 1;
		for (int i = 0; i < (int) cfg->data_bits; ++i) {
			b = bitarray_next_front(src);
			sum += b;
			bitarray_push_back(&data, b);
			bitarray_push_back(dst, b);
		}
		if (cfg->parity_bit != PARITY_NONE) {
			b = bitarray_next_front(src);
			if (b != parity(sum, cfg->parity_bit)) dirty = 1;
		}
		for (int i = 0; i < (int) cfg->stop_bits; ++i)
			if ((b = bitarray_next_front(src)) != STOP_BIT) dirty = 1;
		if (dirty > 0) ++ret;
	}
	bitarray_free(&data);
	return ret;
}
