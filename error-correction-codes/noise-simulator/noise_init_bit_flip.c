#include <stdlib.h>
#include "util.h"
#include "noise_impl.h"
#include "random.h"

noise_t* noise_init_bit_flip(double frequency) {
	if (frequency < 0.0 || frequency > 1.0) return NULL;
	noise_t *generator = (noise_t*) emalloc(sizeof(noise_t));
	generator->type = NOISE_BIT_FLIP;
	generator->settings.bit_flip.frequency = frequency;
	rnd_init(&generator->rnd);
	return generator;
}
