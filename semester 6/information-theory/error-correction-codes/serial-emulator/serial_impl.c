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
