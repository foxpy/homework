#pragma once
#include "noise.h"
#include "random.h"

enum {
	NOISE_BIT_FLIP,
	NOISE_TEMPORAL,
	NOISE_BURST,
};

struct noise_bit_flip_settings {
	double frequency;
};
struct noise_temporal_settings {
	size_t interval;
};
struct noise_burst_settings {
	int type;
	double frequency;
	size_t mean_length;
	size_t length_st_dev;
};
union noise_settings {
	struct noise_bit_flip_settings bit_flip;
	struct noise_temporal_settings temporal;
	struct noise_burst_settings burst;
};

struct noise_bit_flip_state {
	int unused;
};
struct noise_temporal_state {
	size_t consumed;
};
struct noise_burst_state {
	size_t length;
};
union noise_state {
	struct noise_bit_flip_state bit_flip;
	struct noise_temporal_state temporal;
	struct noise_burst_state burst;
};

struct noise_generator {
	int type;
	union noise_settings settings;
	union noise_state state;
	rnd_state_t rnd;
};
