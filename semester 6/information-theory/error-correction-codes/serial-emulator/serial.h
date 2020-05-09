#pragma once
#include <stdlib.h>
#include "bit-array.h"

enum data_bits {
	DATA_BITS_5 = 5,
	DATA_BITS_6 = 6,
	DATA_BITS_7 = 7,
	DATA_BITS_8 = 8,
	DATA_BITS_9 = 9,
};

enum parity_bit {
	PARITY_NONE,
	PARITY_ODD,
	PARITY_EVEN,
};

enum stop_bits {
	STOP_BITS_1 = 1,
	STOP_BITS_2 = 2,
};

typedef struct serial_config {
	enum data_bits data_bits;
	enum parity_bit parity_bit;
	enum stop_bits stop_bits;
} serial_cfg_t;

void serial_encode(bits_t *dst, bits_t *src, serial_cfg_t *cfg);
size_t serial_decode(bits_t *dst, bits_t *src, serial_cfg_t *cfg);
