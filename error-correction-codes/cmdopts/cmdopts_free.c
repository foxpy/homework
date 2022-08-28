#include <stdlib.h>
#include "cmdopts.h"

void cmdopts_free(opts_t *opts) {
	opts->nopts = 0;
	free(opts->opts);
	opts->opts = NULL;
	opts->nposopts = 0;
	opts->posopts = NULL;
}
