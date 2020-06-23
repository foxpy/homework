#include "interleaver_impl.h"
#include "bit-array.h"
#include "util.h"

void interleaver_shuffle(interleaver_t *state) {
	bit *tmp = (bit*) emalloc(sizeof(bit) * state->width * state->length);
	for (size_t i = 0; i < state->width; ++i) for (size_t j = 0; j < state->length; ++j)
		tmp[state->width*j + i] = state->data[state->length*i + j];
	free(state->data);
	state->data = tmp;
}

void interleaver_deshuffle(interleaver_t *state) {
	bit *tmp = (bit*) emalloc(sizeof(bit) * state->width * state->length);
	for (size_t i = 0; i < state->width; ++i) for (size_t j = 0; j < state->length; ++j)
		tmp[state->length*i + j] = state->data[state->width*j + i];
	free(state->data);
	state->data = tmp;
}
