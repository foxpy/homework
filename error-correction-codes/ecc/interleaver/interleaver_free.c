#include <stdlib.h>
#include "interleaver_impl.h"

void interleaver_free(interleaver_t *state) {
	free(state->data);
	free(state);
}
