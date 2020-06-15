#include <stdint.h>
#include "random.h"
#include "random_impl.h"

uint8_t rnd8(rnd_state_t *state) {
	xorshift64(&state->s64);
	return state->s8[0];
}

uint16_t rnd16(rnd_state_t *state) {
	xorshift64(&state->s64);
	return state->s16[0];
}

uint32_t rnd32(rnd_state_t *state) {
	xorshift64(&state->s64);
	return state->s32[0];
}

uint64_t rnd64(rnd_state_t *state) {
	xorshift64(&state->s64);
	return state->s64;
}
