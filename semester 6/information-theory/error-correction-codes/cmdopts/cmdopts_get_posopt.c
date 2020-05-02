#include "cmdopts.h"

char* cmdopts_get_posopt(opts_t *opts, int n) {
	return opts->posopts[n];
}
