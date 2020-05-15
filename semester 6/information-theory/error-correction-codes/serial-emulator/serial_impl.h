#pragma once
#include <stdint.h>
#include "bit-array.h"
#include "serial.h"

#define START_BIT 0
#define STOP_BIT 1

bit parity(uint8_t sum, enum parity_bit ptype);
bit next_bit(bits_t *bits);
