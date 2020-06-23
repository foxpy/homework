#include "interleaver_impl.h"
#include "bit-array.h"

void interleaver_process_data(bits_t *dst, bits_t *src, interleaver_t *state) {
	while (!bitarray_empty(src)) {
		state->data[state->fill++] = bitarray_next_front(src);
		if (state->fill == (state->length * state->width)) {
			switch (state->type) {
				case INTERLEAVER_ENCODE: interleaver_shuffle(state); break;
				case INTERLEAVER_DECODE: interleaver_deshuffle(state); break;
			}
			for (size_t i = 0; i < state->length * state->width; ++i)
				bitarray_push_back(dst, state->data[i]);
			state->fill = 0;
		}
	}
}
