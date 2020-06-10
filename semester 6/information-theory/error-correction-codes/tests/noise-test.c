#ifdef NDEBUG
#undef NDEBUG
#endif

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "random.h"
#include "noise.h"
#include "util.h"

char original_message[] = "The quick brown fox jumps over the lazy dog";

int main() {
	rnd_state_t rnd;
	rnd_init(&rnd);
	noise_t ntype ;
	noise_cfg_t nconfig;
	char *message = (char*) emalloc(strlen(original_message)+1);

	ntype = NOISE_BIT_FLIP;
	nconfig.bit_flip.num_bit_flips = 0;
	strcpy(message, original_message);
	apply_noise(message, strlen(message), ntype, nconfig, &rnd);
	assert(memcmp(message, original_message, strlen(original_message)) == 0);

	ntype = NOISE_BIT_FLIP;
	nconfig.bit_flip.num_bit_flips = 1;
	strcpy(message, original_message);
	apply_noise(message, strlen(message), ntype, nconfig, &rnd);
	assert(memcmp(message, original_message, strlen(original_message)) != 0);

	ntype = NOISE_LINEAR;
	nconfig.linear.damage_length = 0;
	strcpy(message, original_message);
	apply_noise(message, strlen(message), ntype, nconfig, &rnd);
	assert(memcmp(message, original_message, strlen(original_message)) == 0);

	ntype = NOISE_LINEAR;
	nconfig.linear.damage_length = 4;
	strcpy(message, original_message);
	apply_noise(message, strlen(message), ntype, nconfig, &rnd);
	assert(memcmp(message, original_message, strlen(original_message)) != 0);

	free(message);
	return EXIT_SUCCESS;
}
