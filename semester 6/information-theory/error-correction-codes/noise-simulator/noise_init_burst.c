#include <stdlib.h>
#include "util.h"
#include "noise_impl.h"
#include "random.h"

noise_t* noise_init_burst(int type, double frequency, size_t mean_length, size_t length_st_dev) {
	if ((type != NOISE_BURST_UP && type != NOISE_BURST_DOWN) ||
	    mean_length == 0 ||
	    frequency < 0.0 || frequency > 1.0 ) return NULL;

	noise_t *generator = (noise_t*) emalloc(sizeof(noise_t));
	generator->type = NOISE_BURST;
	generator->settings.burst.type = type;
	generator->settings.burst.frequency = frequency;
	generator->settings.burst.mean_length = mean_length;
	generator->settings.burst.length_st_dev = length_st_dev;
	generator->state.burst.length = 0;
	rnd_init(&generator->rnd);
	return generator;
}
