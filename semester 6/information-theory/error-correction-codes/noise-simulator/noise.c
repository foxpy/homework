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
                                 size_t num_bit_flips,
                                 rnd_state_t *rnd) {
	size_t nbyte;
	uint8_t nbit;
	while (num_bit_flips--) {
		nbyte = (len > UINT32_MAX) ? rnd64(rnd) : rnd32(rnd);
		nbyte %= len;
		nbit = rnd32(rnd) % 8;
		flip_specific_bit((uint8_t*)(ptr) + nbyte, nbit);
	}
}

static void apply_noise_linear(void *ptr,
                               size_t len,
                               size_t damage_length,
                               rnd_state_t *rnd) {
	size_t start_bit = (len * 8) - damage_length;
	start_bit = (len > UINT32_MAX) ? (rnd64(rnd) % start_bit) : (rnd32(rnd) % start_bit);
	while (damage_length--) {
		flip_specific_bit((uint8_t*)(ptr)+(start_bit/8), start_bit%8);
		++start_bit;
	}
}

void apply_noise(void *ptr,
                 size_t len,
                 int ntype,
                 noise_cfg_t nconfig,
                 rnd_state_t *rnd) {
	switch(ntype) {
	case NOISE_BIT_FLIP:
		apply_noise_bit_flip(ptr, len, nconfig.bit_flip.num_bit_flips, rnd);
		break;
	case NOISE_LINEAR:
		apply_noise_linear(ptr, len, nconfig.linear.damage_length, rnd);
		break;
	}
}
