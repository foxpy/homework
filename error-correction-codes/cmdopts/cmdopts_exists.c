#include <stdbool.h>
#include <string.h>
#include "cmdopts.h"

bool cmdopts_exists(opts_t *opts, char *opt) {
	for (int i = 0; i < opts->nopts; ++i) {
		if (strcmp(opts->opts[i].flag, opt) == 0) {
			return true;
		}
	}
	return false;
}
