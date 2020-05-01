#include <string.h>
#include <stdint.h>
#include "noise.h"
#include "random.h"

static void flip_specific_bit(uint8_t *byte, uint8_t nbit) {
	uint8_t mask = 1;
	mask <<= nbit;
	*byte ^= mask;
}

static void apply_noise_bit_flip(void *ptr,
                                 size_t len,
                                 size_t num_bit_flips) {
	size_t nbyte;
	uint8_t nbit;
	while (num_bit_flips--) {
		nbyte = (len > UINT32_MAX) ? rnd64() : rnd32();
		nbyte %= len;
		nbit = rnd32() % 8;
		flip_specific_bit((uint8_t*)(ptr) + nbyte, nbit);
	}
}

// TODO: replace with actual implementation
static void apply_noise_linear(void *ptr,
                               size_t len,
                               size_t damage_length) {
	char *data = ptr;
	data[0] = rnd32();
}

void apply_noise(void *ptr,
                 size_t len,
                 noise_t ntype,
                 noise_cfg_t nconfig) {
	switch(ntype) {
	case NOISE_BIT_FLIP:
		apply_noise_bit_flip(ptr, len, nconfig.bit_flip.num_bit_flips);
		break;
	case NOISE_LINEAR:
		apply_noise_linear(ptr, len, nconfig.linear.damage_length);
		break;
	}
}
