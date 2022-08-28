#pragma once
#include "interleaver.h"

struct interleaver_state {
	int type;
	size_t fill, length, width;
	bit *data;
};

void interleaver_shuffle(interleaver_t *state);
void interleaver_deshuffle(interleaver_t *state);
