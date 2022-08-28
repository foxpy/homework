#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "cmdopts.h"
#include "util.h"
#include "interleaver.h"

void encode_loop(FILE *input, FILE *output);
void decode_loop(FILE *input, FILE *output);

void help(char *program_name, int status) {
	fprintf(stderr, "Usage: %s [OPTIONS] [INPUT] [OUTPUT]\n", program_name);
	fputs("INPUT - input file (stdin if \"-\" or omitted)\n", stderr);
	fputs("OUTPUT - output file (stdout if \"-\" or omitted)\n", stderr);
	fputs("OPTIONS - any of these:\n", stderr);
	fputs("\t--help - print this message\n", stderr);
	fputs("\t--mode <encode | decode> - defaults to encode\n", stderr);
	fputs("\t--length [1, 65536) - defaults to 1\n", stderr);
	fputs("\t--width [2, 65536) - defaults to 2\n", stderr);
	fputs("Program drops all tail bytes which do not fit into interleaver window\n", stderr);
	exit(status);
}

int main(int argc, char *argv[]) {
	reopen_binary_read(stdin);
	reopen_binary_write(stdout);
	int status = EXIT_SUCCESS;
	opts_t opts;
	FILE *input = stdin;
	FILE *output = stdout;
	size_t length = 1, width = 2;
	int mode = INTERLEAVER_ENCODE;
	cmdopts_parse(&opts, argc, argv);
	if (cmdopts_exists(&opts, "--help"))
		help(argv[0], EXIT_SUCCESS);
	if (cmdopts_exists(&opts, "--mode")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--mode")) == NULL) {
			help(argv[0], EXIT_FAILURE);
		}
		if (strcmp(val, "encode") == 0) {
			mode = INTERLEAVER_ENCODE;
		} else if (strcmp(val, "decode") == 0) {
			mode = INTERLEAVER_DECODE;
		} else {
			help(argv[0], EXIT_FAILURE);
		}
	}
	if (cmdopts_exists(&opts, "--length")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--length")) == NULL)
			help(argv[0], EXIT_FAILURE);
		long _length = atol(val);
		if (_length < 1 || _length > 0xFFFF)
			help(argv[0], EXIT_FAILURE);
		length = _length;
	}
	if (cmdopts_exists(&opts, "--width")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--width")) == NULL)
			help(argv[0], EXIT_FAILURE);
		long _width = atol(val);
		if (_width < 2 || _width > 0xFFFF)
			help(argv[0], EXIT_FAILURE);
		width = _width;
	}
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
	if (cmdopts_num_posopts(&opts) > 2) {
		help(argv[0], EXIT_FAILURE);
	}

	interleaver_t *state = interleaver_init(mode, length, width);
	bits_t bit_input, bit_output;
	char buf[BUFSIZ];
	char *processed;
	size_t nread, nbits, nbytes;
	bitarray_alloc(&bit_input);
	bitarray_alloc(&bit_output);
	while ((nread = fread(buf, sizeof(char), BUFSIZ, input)) != 0) {
		bitarray_fill_from_memory(&bit_input, buf, nread * 8);
		interleaver_process_data(&bit_output, &bit_input, state);
		processed = bitarray_to_memory(&bit_output, &nbits, &nbytes);
		if (fwrite(processed, sizeof(char), nbytes, output) != nbytes) {
			status = EXIT_FAILURE;
			goto exit;
		}
		free(processed);
	}
	interleaver_free(state);
	bitarray_free(&bit_input);
	bitarray_free(&bit_output);

exit:
	if (output != stdout) fclose(output);
error_open_output:
	if (input != stdin) fclose(input);
error_open_input:
	cmdopts_free(&opts);
	return status;
}
