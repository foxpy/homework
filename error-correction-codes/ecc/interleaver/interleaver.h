#pragma once
#include <stdlib.h>
#include "bit-array.h"

enum {
	INTERLEAVER_ENCODE,
	INTERLEAVER_DECODE,
};
typedef struct interleaver_state interleaver_t;

interleaver_t* interleaver_init(int type, size_t length, size_t width);
void interleaver_process_data(bits_t *dst, bits_t *src, interleaver_t *state);
void interleaver_free(interleaver_t *state);
