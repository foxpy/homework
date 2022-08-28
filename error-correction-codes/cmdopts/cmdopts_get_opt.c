#include <stdlib.h>
#include <string.h>
#include "cmdopts.h"

char* cmdopts_get_opt(opts_t *opts, char *opt) {
	for (int i = 0; i < opts->nopts; ++i)
		if (strcmp(opts->opts[i].flag, opt) == 0)
			return opts->opts[i].value;
	return NULL;
}
