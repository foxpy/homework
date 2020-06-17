#pragma once
#include <stdlib.h>
#include "bit-array.h"

enum {
	NOISE_BURST_UP,
	NOISE_BURST_DOWN,
};
typedef struct noise_generator noise_t;

noise_t* noise_init_bit_flip(double frequency);
noise_t* noise_init_temporal(size_t interval);
noise_t* noise_init_burst(int type, double frequency, size_t mean_length, size_t length_st_dev);
void noise_free(noise_t *generator);
size_t noise_apply(bits_t *dst, bits_t *src, noise_t *generator);
