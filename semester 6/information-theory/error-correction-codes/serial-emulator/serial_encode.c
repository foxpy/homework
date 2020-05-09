#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "bit-array.h"
#include "serial.h"
#include "serial_impl.h"

void serial_encode(bits_t *dst, bits_t *src, serial_cfg_t *cfg) {
	uint8_t sum = 0;
	bit b;
	while (!bitarray_empty(src)) {
		bitarray_push_back(dst, START_BIT);
		for (int i = 0; i < cfg->data_bits; ++i) {
			b = next_bit(src);
			bitarray_push_back(dst, b);
			sum += b;
		}
		if (cfg->parity_bit != PARITY_NONE) {
			bitarray_push_back(dst, parity(sum, cfg->parity_bit));
		}
		sum = 0;
		for (int i = 0; i < cfg->stop_bits; ++i) {
			bitarray_push_back(dst, STOP_BIT);
		}
	}
}
