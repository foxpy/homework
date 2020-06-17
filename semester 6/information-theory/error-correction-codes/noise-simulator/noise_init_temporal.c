#include "util.h"
#include "noise_impl.h"

noise_t* noise_init_temporal(size_t interval) {
	if (interval == 0) return NULL;
	noise_t *generator = (noise_t*) emalloc(sizeof(noise_t));
	generator->type = NOISE_TEMPORAL;
	generator->settings.temporal.interval = interval;
	generator->state.temporal.consumed = 0;
	return generator;
}
