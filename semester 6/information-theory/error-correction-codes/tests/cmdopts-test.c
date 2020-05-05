#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "cmdopts.h"

void all() {
	opts_t opts;
	int argc = 8;
	char *argv[] = {
		"./executable",
		"--flag1",
		"val1",
		"--flag2",
		"val2",
		"pos1",
		"pos2",
		"pos3",
		NULL,
	};
	cmdopts_parse(&opts, argc, argv);
	assert(cmdopts_num_posopts(&opts) == 3);
	assert(strcmp(cmdopts_get_posopt(&opts, 0), "pos1") == 0);
	assert(strcmp(cmdopts_get_posopt(&opts, 1), "pos2") == 0);
	assert(strcmp(cmdopts_get_posopt(&opts, 2), "pos3") == 0);
	assert(cmdopts_exists(&opts, "--flag1") == true);
	assert(cmdopts_exists(&opts, "--flag2") == true);
	assert(cmdopts_exists(&opts, "--flag3") == false);
	assert(strcmp(cmdopts_get_opt(&opts, "--flag1"), "val1") == 0);
	assert(strcmp(cmdopts_get_opt(&opts, "--flag2"), "val2") == 0);
	cmdopts_free(&opts);
}

void empty() {
	opts_t opts;
	int argc = 1;
	char *argv[] = {
		"./executable",
		NULL,
	};
	cmdopts_parse(&opts, argc, argv);
	assert(cmdopts_num_posopts(&opts) == 0);
	assert(cmdopts_exists(&opts, "--flag1") == false);
	cmdopts_free(&opts);
}

int main() {
	all();
	empty();
	return EXIT_SUCCESS;
}
