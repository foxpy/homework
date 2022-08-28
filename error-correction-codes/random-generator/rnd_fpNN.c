#include <string.h>
#include <stdint.h>
#include "random.h"
#include "random_impl.h"

#define DOUBLE_ONE_EXPONENT  UINT64_C(0x3ff0000000000000)
#define DOUBLE_FRACTION_MASK UINT64_C(0x000fffffffffffff)
#define FLOAT_ONE_EXPONENT   UINT32_C(0x3f800000)
#define FLOAT_FRACTION_MASK  UINT32_C(0x007fffff)

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
