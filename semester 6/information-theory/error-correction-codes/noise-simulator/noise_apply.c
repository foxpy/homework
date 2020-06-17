#include <math.h>
#include "noise_impl.h"
#include "bit-array.h"
#include "random.h"

static size_t bit_flip_loop(
	bits_t *dst,
	bits_t *src,
	double frequency,
	rnd_state_t *rnd
) {
	size_t ret = 0;
	bit b;
	while (!bitarray_empty(src)) {
		b = bitarray_next_front(src);
		if (rnd_fp64(rnd) < frequency) {
			FLIP_BIT(b);
			++ret;
		}
		bitarray_push_back(dst, b);
	}
	return ret;
}

static size_t temporal_loop(
	bits_t *dst,
	bits_t *src,
	size_t interval,
	size_t *consumed
) {
	size_t ret = 0;
	bit b;
	while (!bitarray_empty(src)) {
		b = bitarray_next_front(src);
		++*consumed;
		if (*consumed == interval) {
			*consumed = 0;
			FLIP_BIT(b);
			++ret;
		}
		bitarray_push_back(dst, b);
	}
	return ret;
}

static size_t burst_loop(
	bits_t *dst,
	bits_t *src,
	int type,
	double frequency,
	size_t mean_length,
	size_t length_st_dev,
	size_t *state_length,
	rnd_state_t *rnd
) {
	size_t ret = 0;
	bit b;
	while (!bitarray_empty(src)) {
		b = bitarray_next_front(src);
		if (*state_length == 0) {
			if (rnd_fp64(rnd) < frequency)
				*state_length = (size_t) (fabs(normal_distribution(mean_length, length_st_dev, rnd) + 0.5));
		} else {
			b = (type == NOISE_BURST_UP) ? 1 : 0;
			--*state_length;
			++ret;
		}
		bitarray_push_back(dst, b);
	}
	return ret;
}

size_t noise_apply(bits_t *dst, bits_t *src, noise_t *generator) {
	switch (generator->type) {
	case NOISE_BIT_FLIP: return bit_flip_loop(dst,
	                                          src,
	                                          generator->settings.bit_flip.frequency,
	                                          &generator->rnd);
	case NOISE_TEMPORAL: return temporal_loop(dst,
	                                          src,
	                                          generator->settings.temporal.interval,
	                                          &generator->state.temporal.consumed);
	case NOISE_BURST: return burst_loop(dst,
	                                    src,
	                                    generator->settings.burst.type,
	                                    generator->settings.burst.frequency,
	                                    generator->settings.burst.mean_length,
	                                    generator->settings.burst.length_st_dev,
	                                    &generator->state.burst.length,
	                                    &generator->rnd);
	}
	return 0; // suppress warning
}
