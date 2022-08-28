#pragma once
#include <stdbool.h>

struct opt {
	char *flag;
	char *value;
};

typedef struct cmdopts {
	int nopts;
	struct opt *opts;
	int nposopts;
	char **posopts;
} opts_t;

void cmdopts_parse(opts_t *opts, int argc, char *argv[]);
void cmdopts_free(opts_t *opts);
int cmdopts_num_posopts(opts_t *opts);
char* cmdopts_get_posopt(opts_t *opts, int n);
bool cmdopts_exists(opts_t *opts, char *opt);
char* cmdopts_get_opt(opts_t *opts, char *opt);
