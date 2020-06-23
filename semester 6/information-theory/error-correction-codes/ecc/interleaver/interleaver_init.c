#include <stdlib.h>
#include "interleaver_impl.h"
#include "util.h"

interleaver_t* interleaver_init(int type, size_t length, size_t width) {
	if ((type != INTERLEAVER_ENCODE && type != INTERLEAVER_DECODE) ||
	     length < 1 || length > 0xFFFF || width < 2 || length > 0xFFFF)
		return NULL;
	interleaver_t *state = (interleaver_t*) emalloc(sizeof(interleaver_t));
	state->type = type;
	state->length = length * 8;
	state->width = width;
	state->fill = 0;
	state->data = (bit*) emalloc(sizeof(bit) * state->length * state->width);
	return state;
}
