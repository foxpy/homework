#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "cmdopts.h"
#include "random.h"

#define MIN(a, b) ((a < b) ? (a) : (b))
void help(char *program_name) {
	fprintf(stderr, "Usage: %s [--size SIZE] [OUTPUT]\n", program_name);
	fputs("OUTPUT - output file (stdout if \"-\" or omitted)\n", stderr);
	fprintf(stderr, "SIZE - number [0, %lld] of bytes to output, 0 means infinity (default)\n", LLONG_MAX);
}

int main(int argc, char *argv[]) {
	long long rnd_len = 0;
	opts_t opts;
	FILE *output = stdout;
	cmdopts_parse(&opts, argc, argv);
	if (cmdopts_exists(&opts, "--help")) {
		help(argv[0]);
		return EXIT_SUCCESS;
	}
	if (cmdopts_exists(&opts, "--size")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--size")) == NULL) {
			help(argv[0]);
			return EXIT_FAILURE;
		}
		if ((rnd_len = atoll(val)) < 0) {
			help(argv[0]);
			return EXIT_FAILURE;
		}
	}
	if (cmdopts_num_posopts(&opts) > 0) {
		if (strcmp(cmdopts_get_posopt(&opts, 0), "-") != 0) {
			if ((output = fopen(cmdopts_get_posopt(&opts, 0), "w")) == NULL) {
				fprintf(stderr, "Failed to open file %s: %s\n", cmdopts_get_posopt(&opts, 0), strerror(errno));
				return EXIT_FAILURE;
			}
		}
	}
	if (cmdopts_num_posopts(&opts) > 1) {
		help(argv[0]);
		return EXIT_FAILURE;
	}

	uint64_t rnd;
	if (rnd_len == 0) {
		for (;;) {
			rnd = rnd64();
			if (fwrite(&rnd, sizeof(uint64_t), 1, output) != 1) return EXIT_FAILURE;
		}
	}
	while (rnd_len > 0) {
		rnd = rnd64();
		if (fwrite(&rnd, MIN(rnd_len, (long long) sizeof(uint64_t)), 1, output) != 1) return EXIT_FAILURE;
		rnd_len -= sizeof(uint64_t);
	}

	cmdopts_free(&opts);
	return EXIT_SUCCESS;
}
