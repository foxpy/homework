#include <string.h>
#include "noise.h"

#include <stdio.h>
#include "random.h"

// TODO: replace with actual implementation
static void apply_noise_bit_flip(void *ptr,
                                 size_t len,
                                 size_t num_bit_flips) {
	char *data = ptr;
	data[0] = rnd32();
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
