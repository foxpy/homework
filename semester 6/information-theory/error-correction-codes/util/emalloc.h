#pragma once
#include <stdlib.h>
#include <stdio.h>

static void* emalloc(size_t size) {
	void *p;
	if ((p = malloc(size)) == NULL) {
		fputs("Fatal: Out Of Memory\n", stderr);
		exit(EXIT_FAILURE);
	}
	return p;
}

static void* erealloc(void *ptr, size_t size) {
	void *p;
	if ((p = realloc(ptr, size)) == NULL) {
		fputs("Fatal: Out Of Memory\n", stderr);
		exit(EXIT_FAILURE);
	}
	return p;
}
