#include <stdlib.h>
#include "noise_impl.h"

void noise_free(noise_t *generator) {
	free(generator);
}
