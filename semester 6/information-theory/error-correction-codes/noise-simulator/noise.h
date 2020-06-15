#pragma once
#include <stdlib.h>
#include "random.h"

enum noise_type {
	NOISE_BIT_FLIP,
	NOISE_LINEAR,
};

struct noise_bit_flip_config {
	size_t num_bit_flips;
};

struct noise_linear_config {
	size_t damage_length;
};

typedef union noise_config {
	struct noise_bit_flip_config bit_flip;
	struct noise_linear_config linear;
} noise_cfg_t;

void apply_noise(void *ptr,
                 size_t len,
                 int ntype,
                 noise_cfg_t nconfig,
                 rnd_state_t *rnd);
