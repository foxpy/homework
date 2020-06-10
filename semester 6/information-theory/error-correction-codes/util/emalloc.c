#include <stdlib.h>
#include <stdio.h>
#include "util.h"

void* emalloc(size_t size) {
	void *p;
	if ((p = malloc(size)) == NULL) {
		fputs("Fatal: Out Of Memory\n", stderr);
		exit(EXIT_FAILURE);
	}
	return p;
}
