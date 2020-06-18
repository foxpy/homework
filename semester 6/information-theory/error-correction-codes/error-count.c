#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "cmdopts.h"
#include "bit-array.h"

static void help(char *program_name, int status) {
	fprintf(stderr, "Usage: %s FILE1 FILE2\n", program_name);
	fputs("Prints number of bit differences between FILE1 and FILE2\n", stderr);
	exit(status);
}

int main(int argc, char *argv[]) {
	int status = EXIT_SUCCESS;
	opts_t opts;
	bits_t bfile1, bfile2;
	bitarray_alloc(&bfile1);
	bitarray_alloc(&bfile2);
	cmdopts_parse(&opts, argc, argv);

	if (cmdopts_exists(&opts, "--help"))
		help(argv[0], EXIT_SUCCESS);
	if (cmdopts_num_posopts(&opts) != 2)
		help(argv[0], EXIT_FAILURE);

	FILE *file1, *file2;
	if ((file1 = fopen(cmdopts_get_posopt(&opts, 0), "rb")) == NULL) {
		fprintf(stderr, "Failed to open file %s: %s\n", cmdopts_get_posopt(&opts, 0), strerror(errno));
		status = EXIT_FAILURE;
		goto error_open_file1;
	}
	if ((file2 = fopen(cmdopts_get_posopt(&opts, 1), "rb")) == NULL) {
		fprintf(stderr, "Failed to open file %s: %s\n", cmdopts_get_posopt(&opts, 1), strerror(errno));
		status = EXIT_FAILURE;
		goto error_open_file2;
	}

	size_t ndiff = 0;
	int c1, c2;
	while ((c1 = fgetc(file1)) != EOF && (c2 = fgetc(file2)) != EOF) {
		unsigned char buf1 = c1, buf2 = c2;
		bitarray_fill_from_memory(&bfile1, &buf1, 8);
		bitarray_fill_from_memory(&bfile2, &buf2, 8);
		for (int i = 0; i < 8; ++i) {
			bit b1 = bitarray_back(&bfile1);
			bit b2 = bitarray_back(&bfile2);
			if (b1 != b2) ++ ndiff;
			bitarray_pop_back(&bfile1);
			bitarray_pop_back(&bfile2);
		}
	}
	printf("%zu\n", ndiff);

	fclose(file2);
error_open_file2:
	fclose(file1);
error_open_file1:
	bitarray_free(&bfile1);
	bitarray_free(&bfile2);
	cmdopts_free(&opts);
	return status;
}
