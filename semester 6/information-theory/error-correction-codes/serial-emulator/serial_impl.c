#include <stdint.h>
#include "bit-array.h"
#include "serial_impl.h"

bit parity(uint8_t sum, enum parity_bit ptype) {
	if (ptype == PARITY_EVEN) {
		return (sum % 2) == 0;
	} else {
		return (sum % 2) == 1;
	}
}

bit next_bit(bits_t *bits) {
	bit b;
	if (bitarray_empty(bits)) {
		return 0;
	} else {
		b = bitarray_front(bits);
		bitarray_pop_front(bits);
		return b;
	}
}

uint8_t packet_length(serial_cfg_t *cfg) {
	uint8_t len = 1; // start bit
	len += cfg->data_bits;
	len += (cfg->parity_bit == PARITY_NONE) ? 0 : 1;
	len += cfg->stop_bits;
	return len;
}
