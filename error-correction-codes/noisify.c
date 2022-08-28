#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "cmdopts.h"
#include "noise.h"
#include "util.h"

static void help(char *program_name, int status) {
	fprintf(stderr, "Usage: %s [OPTIONS] [INPUT] [OUTPUT]\n", program_name);
	fputs("INPUT - input file (stdin if \"-\" or omitted)\n", stderr);
	fputs("OUTPUT - output file (stdout if \"-\" or omitted)\n", stderr);
	fputs("\nOPTIONS - any of these:\n", stderr);
	fputs("\t--help - print this message\n", stderr);
	fprintf(stderr, "\t--skip N [1, %ld) - skip first N bytes of data unchanged\n", LONG_MAX);
	fputs("\t--mode <shot | temporal | burst> - defaults to shot\n", stderr);
	fputs("\nShot noise is best described as random bit flips. Options:\n", stderr);
	fputs("\t--frequency <double> - probability of bit flip, defaults to 0.001\n", stderr);
	fputs("\nTemporal noise bit flips with a constant period. Options:\n", stderr);
	fprintf(stderr, "\t--interval N [1, %ld) - each N'th bit is flipped, defaults to 20\n", LONG_MAX);
	fputs("\nBurst noise damages a continious sequence of bits. Options:\n", stderr);
	fputs("\t--type <up | down> - damaged bits are set either up or down, defaults to up\n", stderr);
	fputs("\t--frequency <double> - each bit there is probability of damaged sequence to occur, defaults to 0.001\n", stderr);
	fprintf(stderr, "\t--mean-length N [1, %ld) - average length of damaged sequence, defaults to 5\n", LONG_MAX);
	fprintf(stderr, "\t--length-st-dev N [0, %ld) - standard deviation of damage length, defaults to 2\n", LONG_MAX);
	fputs("\nAfter completion, this program prints number of damaged bits to stderr\n", stderr);
	exit(status);
}

static size_t shot_loop(
	FILE *input,
	FILE *output,
	double frequency
) {
	size_t ret = 0;
	int buf;
	unsigned char *processed;
	size_t nbits, nbytes;
	noise_t *gen = noise_init_bit_flip(frequency);
	bits_t bit_input, bit_output;
	bitarray_alloc(&bit_input);
	bitarray_alloc(&bit_output);

	while ((buf = fgetc(input)) != EOF) {
		unsigned char c = buf;
		bitarray_fill_from_memory(&bit_input, &c, 8);
		ret += noise_apply(&bit_output, &bit_input, gen);
		processed = (unsigned char*) bitarray_to_memory(&bit_output, &nbits, &nbytes);
		fputc(*processed, output);
		free(processed);
	}

	bitarray_free(&bit_input);
	bitarray_free(&bit_output);
	noise_free(gen);
	return ret;
}

static size_t temporal_loop(
	FILE *input,
	FILE *output,
	size_t interval
) {
	size_t ret = 0;
	int buf;
	unsigned char *processed;
	size_t nbits, nbytes;
	noise_t *gen = noise_init_temporal(interval);
	bits_t bit_input, bit_output;
	bitarray_alloc(&bit_input);
	bitarray_alloc(&bit_output);

	while ((buf = fgetc(input)) != EOF) {
		unsigned char c = buf;
		bitarray_fill_from_memory(&bit_input, &c, 8);
		ret += noise_apply(&bit_output, &bit_input, gen);
		processed = (unsigned char*) bitarray_to_memory(&bit_output, &nbits, &nbytes);
		fputc(*processed, output);
		free(processed);
	}

	bitarray_free(&bit_input);
	bitarray_free(&bit_output);
	noise_free(gen);
	return ret;
}

static size_t burst_loop(
	FILE *input,
	FILE *output,
	int type,
	double frequency,
	size_t mean_length,
	size_t length_st_dev
) {
	size_t ret = 0;
	int buf;
	unsigned char *processed;
	size_t nbits, nbytes;
	noise_t *gen = noise_init_burst(type, frequency, mean_length, length_st_dev);
	bits_t bit_input, bit_output;
	bitarray_alloc(&bit_input);
	bitarray_alloc(&bit_output);

	while ((buf = fgetc(input)) != EOF) {
		unsigned char c = buf;
		bitarray_fill_from_memory(&bit_input, &c, 8);
		ret += noise_apply(&bit_output, &bit_input, gen);
		processed = (unsigned char*) bitarray_to_memory(&bit_output, &nbits, &nbytes);
		fputc(*processed, output);
		free(processed);
	}

	bitarray_free(&bit_input);
	bitarray_free(&bit_output);
	noise_free(gen);
	return ret;
}

int main(int argc, char *argv[]) {
	reopen_binary_read(stdin);
	reopen_binary_write(stdout);
	opts_t opts;
	enum {
		SHOT,
		TEMPORAL,
		BURST
	} mode = SHOT;
	int type = NOISE_BURST_UP;
	int status = EXIT_SUCCESS;
	cmdopts_parse(&opts, argc, argv);
	if (cmdopts_exists(&opts, "--help"))
		help(argv[0], EXIT_SUCCESS);

	long skip = 0;
	if (cmdopts_exists(&opts, "--skip")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--skip")) == NULL)
			help(argv[0], EXIT_FAILURE);
		skip = atol(val);
		if (skip < 0)
			help(argv[0], EXIT_FAILURE);
	}

	if (cmdopts_exists(&opts, "--mode")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--mode")) == NULL)
			help(argv[0], EXIT_FAILURE);
		for (unsigned long i = 0; i < strlen(val); ++i) val[i] = tolower(val[i]);
		if (strcmp(val, "shot") == 0)
			mode = SHOT;
		else if (strcmp(val, "temporal") == 0)
			mode = TEMPORAL;
		else if (strcmp(val, "burst") == 0)
			mode = BURST;
		else
			help(argv[0], EXIT_FAILURE);
	}

	double frequency = 0.001;
	if (cmdopts_exists(&opts, "--frequency")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--frequency")) == NULL)
			help(argv[0], EXIT_FAILURE);
		frequency = atof(val);
		if (frequency < 0.0 || frequency > 1.0)
			help(argv[0], EXIT_FAILURE);
	}

	size_t interval = 20;
	if (cmdopts_exists(&opts, "--interval")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--interval")) == NULL)
			help(argv[0], EXIT_FAILURE);
		long _interval = atol(val);
		if (_interval <= 0)
			help(argv[0], EXIT_FAILURE);
		interval = _interval;
	}

	if (cmdopts_exists(&opts, "--type")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--type")) == NULL)
			help(argv[0], EXIT_FAILURE);
		for (unsigned long i = 0; i < strlen(val); ++i) val[i] = tolower(val[i]);
		if (strcmp(val, "up") == 0)
			type = NOISE_BURST_UP;
		else if (strcmp(val, "down") == 0)
			type = NOISE_BURST_DOWN;
		else
			help(argv[0], EXIT_FAILURE);
	}

	size_t mean_length = 5;
	if (cmdopts_exists(&opts, "--mean-length")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--mean-length")) == NULL)
			help(argv[0], EXIT_FAILURE);
		long _mean_length = atol(val);
		if (_mean_length <= 0)
			help(argv[0], EXIT_FAILURE);
		mean_length = _mean_length;
	}

	size_t length_st_dev = 2;
	if (cmdopts_exists(&opts, "--length-st-dev")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--length-st-dev")) == NULL)
			help(argv[0], EXIT_FAILURE);
		long _length_st_dev = atol(val);
		if (_length_st_dev < 0)
			help(argv[0], EXIT_FAILURE);
		length_st_dev = _length_st_dev;
	}

	FILE *input = stdin;
	FILE *output = stdout;
	if (cmdopts_num_posopts(&opts) > 0) {
		if (strcmp(cmdopts_get_posopt(&opts, 0), "-") != 0) {
			if ((input = fopen(cmdopts_get_posopt(&opts, 0), "rb")) == NULL) {
				fprintf(stderr, "Failed to open file %s: %s\n", cmdopts_get_posopt(&opts, 0), strerror(errno));
				status = EXIT_FAILURE;
				goto error_open_input;
			}
		}
	}
	if (cmdopts_num_posopts(&opts) > 1) {
		if (strcmp(cmdopts_get_posopt(&opts, 1), "-") != 0) {
			if ((output = fopen(cmdopts_get_posopt(&opts, 1), "wb")) == NULL) {
				fprintf(stderr, "Failed to open file %s: %s\n", cmdopts_get_posopt(&opts, 1), strerror(errno));
				status = EXIT_FAILURE;
				goto error_open_output;
			}
		}
	}
	if (cmdopts_num_posopts(&opts) > 2)
		help(argv[0], EXIT_FAILURE);

	size_t damaged_bits;
	while (skip-- != 0) {
		int c;
		if ((c = fgetc(input)) == EOF || fputc(c, output) == EOF) goto exit;
	}
	switch (mode) {
	case SHOT:
		damaged_bits = shot_loop(input, output, frequency);
		break;
	case TEMPORAL:
		damaged_bits = temporal_loop(input, output, interval);
		break;
	case BURST:
		damaged_bits = burst_loop(input, output, type, frequency, mean_length, length_st_dev);
		break;
	}
	fprintf(stderr, "%zu\n", damaged_bits);

exit:
	if (output != stdout) fclose(output);
error_open_output:
	if (input != stdin) fclose(input);
error_open_input:
	cmdopts_free(&opts);
	return status;
}
