#include <stdlib.h>
#include <stdio.h>
#include "util.h"

void* erealloc(void *ptr, size_t size) {
	void *p;
	if ((p = realloc(ptr, size)) == NULL) {
		fputs("Fatal: Out Of Memory\n", stderr);
		exit(EXIT_FAILURE);
	}
	return p;
}
