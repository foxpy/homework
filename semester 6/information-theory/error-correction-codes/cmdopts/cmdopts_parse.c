#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "erealloc.h"
#include "cmdopts.h"

#define SAVE_OPT(opt) { \
	if ((size_t) opts->nopts == nopts_cap) { \
		nopts_cap *= 2; \
		opts->opts = (struct opt*) erealloc(opts->opts, sizeof(struct opt) * nopts_cap); \
	} \
	memcpy(&(opts->opts[opts->nopts++]), &opt, sizeof(opt)); \
}

typedef enum state {
	OUT_OPT,
	IN_OPT,
} state_t;

void cmdopts_parse(opts_t *opts, int argc, char *argv[]) {
	state_t state = OUT_OPT;
	struct opt opt;
	++argv; --argc;
	opts->nopts = 0;
	size_t nopts_cap = 2;
	opts->opts = (struct opt*) emalloc(sizeof(struct opt) * nopts_cap);

	while (argc--) {
		switch (state) {
		case OUT_OPT:
			if (strncmp(*argv, "--", 2) == 0) {
				state = IN_OPT;
				opt.flag = *argv;
			} else {
				goto exit;
			}
			break;
		case IN_OPT:
			if (strncmp(*argv, "--", 2) == 0) {
				state = IN_OPT;
				opt.value = NULL;
				SAVE_OPT(opt);
				opt.flag = *argv;
			} else {
				state = OUT_OPT;
				opt.value = *argv;
				SAVE_OPT(opt);
			}
			break;
		}
	++argv;
	}
	if (state == IN_OPT) {
		opt.value = NULL;
		SAVE_OPT(opt);
	}
exit:
	opts->nposopts = argc + 1;
	opts->posopts = argv;
	if (opts->nopts != 0)
		opts->opts = (struct opt*) erealloc(opts->opts, sizeof(struct opt) * opts->nopts);
}
