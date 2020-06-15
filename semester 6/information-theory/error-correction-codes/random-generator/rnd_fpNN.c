#include <string.h>
#include "random.h"
#include "random_impl.h"

enum {
	DOUBLE_ONE_EXPONENT  = 0x3ff0000000000000,
	DOUBLE_FRACTION_MASK = 0x000fffffffffffff,
	FLOAT_ONE_EXPONENT   = 0x3f800000,
	FLOAT_FRACTION_MASK  = 0x007fffff,
};

double rnd_fp64(rnd_state_t *state) {
	xorshift64(&state->s64);
	rnd_state_t tmp;
	memcpy(&tmp, state, sizeof(rnd_state_t));
	tmp.s64 &= DOUBLE_FRACTION_MASK;
	tmp.s64 |= DOUBLE_ONE_EXPONENT;
	tmp.fp64 -= 1.0;
	return tmp.fp64;
}

float rnd_fp32(rnd_state_t *state) {
	xorshift64(&state->s64);
	rnd_state_t tmp;
	memcpy(&tmp, state, sizeof(rnd_state_t));
	tmp.s32[1] &= FLOAT_FRACTION_MASK;
	tmp.s32[1] |= FLOAT_ONE_EXPONENT;
	tmp.fp32[1] -= 1.0f;
	return tmp.fp32[1];
}
