#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "cmdopts.h"
#include "noise.h"

void help(char *program_name) {
	fprintf(stderr, "Usage: %s [OPTIONS] [INPUT] [OUTPUT]\n", program_name);
	fputs("INPUT - input file (stdin if \"-\" or omitted)\n", stderr);
	fputs("OUTPUT - output file (stdout if \"-\" or omitted)\n", stderr);
	fputs("OPTIONS - any of these:\n", stderr);
	fputs("\t--type <bitflip | linear> - defaults to bitflip\n", stderr);
	fputs("\t\tSets damage type either to random bit flips or more linear damage\n", stderr);
	fputs("\t--frequency <UINT> - defaults to 4 for bitflip and 20 for linear\n", stderr);
	fputs("\t\tSets number of defects (0, 1024] per 1 KiB of data\n", stderr);
	fputs("\t--help - print this message\n", stderr);
	fputs("Inputs with length less than 1 KiB have chance to remain unchanged\n", stderr);
}

int main(int argc, char *argv[]) {
	int status = EXIT_SUCCESS;
	opts_t opts;
	cmdopts_parse(&opts, argc, argv);
	if (cmdopts_exists(&opts, "--help")) {
		help(argv[0]);
		return EXIT_SUCCESS;
	}

	noise_t ntype;
	noise_cfg_t nconfig;
	unsigned frequency;
	if (cmdopts_exists(&opts, "--type")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--type")) == NULL) {
			help(argv[0]);
			return EXIT_FAILURE;
		}
		if (strcmp(val, "bitflip") == 0) {
			ntype = NOISE_BIT_FLIP;
		} else if (strcmp(val, "linear") == 0) {
			ntype = NOISE_LINEAR;
		} else {
			help(argv[0]);
			return EXIT_FAILURE;
		}
	} else {
		ntype = NOISE_BIT_FLIP;
	}
	if (cmdopts_exists(&opts, "--frequency")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--frequency")) == NULL) {
			help(argv[0]);
			return EXIT_FAILURE;
		}
		frequency = atoi(val);
		if (frequency == 0 || frequency > 1024) {
			help(argv[0]);
			return EXIT_FAILURE;
		}
	} else {
		switch (ntype) {
		case NOISE_BIT_FLIP:
			frequency = 4;
			break;
		case NOISE_LINEAR:
			frequency = 20;
			break;
		}
	}

	FILE *input = stdin;
	FILE *output = stdout;
	if (cmdopts_num_posopts(&opts) > 0) {
		if (strcmp(cmdopts_get_posopt(&opts, 0), "-") != 0) {
			if ((input = fopen(cmdopts_get_posopt(&opts, 0), "r")) == NULL) {
				fprintf(stderr, "Failed to open file %s: %s\n", cmdopts_get_posopt(&opts, 0), strerror(errno));
				status = EXIT_FAILURE;
				goto error_open_input;
			}
		}
	}
	if (cmdopts_num_posopts(&opts) > 1) {
		if (strcmp(cmdopts_get_posopt(&opts, 1), "-") != 0) {
			if ((output = fopen(cmdopts_get_posopt(&opts, 1), "w")) == NULL) {
				fprintf(stderr, "Failed to open file %s: %s\n", cmdopts_get_posopt(&opts, 1), strerror(errno));
				status = EXIT_FAILURE;
				goto error_open_output;
			}
		}
	}
	if (cmdopts_num_posopts(&opts) > 2) {
		help(argv[0]);
		return EXIT_FAILURE;
	}

	switch(ntype) {
	case NOISE_BIT_FLIP:
		nconfig.bit_flip.num_bit_flips = frequency;
		break;
	case NOISE_LINEAR:
		nconfig.linear.damage_length = frequency;
		break;
	}
	char buf[1024];
	size_t nread;
	while ((nread = fread(buf, sizeof(char), sizeof(buf)/sizeof(char), input)) > 0) {
		apply_noise(buf, sizeof(buf), ntype, nconfig);
		if (fwrite(buf, sizeof(char), nread, output) == 0) {
			break;
		}
		memset(buf, 0, sizeof(buf));
	}

	if (output != stdout) fclose(output);
error_open_output:
	if (input != stdin) fclose(input);
error_open_input:
	cmdopts_free(&opts);
	return status;
}
