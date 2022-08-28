#include <stdint.h>
#include "bit-array.h"
#include "serial_impl.h"

bit parity(uint8_t sum, int ptype) {
	if (ptype == PARITY_EVEN) {
		return (sum % 2) == 0;
	} else {
		return (sum % 2) == 1;
	}
}
