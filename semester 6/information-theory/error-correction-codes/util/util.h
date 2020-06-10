#pragma once
#include <stdlib.h>
#include <stdio.h>

#define MAX(a, b) ((a > b) ? (a) : (b))
#define MIN(a, b) ((a < b) ? (a) : (b))

void* emalloc(size_t size);
void* erealloc(void *ptr, size_t size);

void reopen_binary_read(FILE *stream);
void reopen_binary_write(FILE *stream);

unsigned gcd(unsigned a, unsigned b);
unsigned lcm(unsigned a, unsigned b);
