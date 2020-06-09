#ifdef _WIN32
#	define _CRT_RAND_S
#endif

#if defined __linux__ || defined __ANDROID_API__
#	include <sys/random.h>
#endif

#include <stdlib.h>
#include <stdint.h>
#include "random.h"

void rnd_init(rnd_state_t *state) {
#	ifdef _WIN32
		rand_s(&state->s32[0]);
		rand_s(&state->s32[1]);
#	elif defined __ANDROID_API__
#		if __ANDROID_API__ < 28
			arc4random_buf(&state->s64, sizeof(uint64_t));
#		else
			getrandom(&state->s64, sizeof(uint64_t), 0);
#		endif
#	elif defined __linux__
		getrandom(&state->s64, sizeof(uint64_t), 0);
#	else
		state->s64 = 0;
#	endif
}
