#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
	size_t n;
	double x;
	double y;
} point;

point* pool;
size_t pool_alloc;
size_t pool_used;

void add_diff(double x1, double y1, double x2, double y2, double* x3, double *y3) {
	*x3 = pow((y2 - y1) / (x2 - x1), 2) - x1 - x2;
	*y3 = (y2 - y1) / (x2 - x1) * (x1 - *x3) - y1;
}

void add_eq(double x1, double y1, double *x3, double* y3) {
	*x3 = pow((3*x1*x1 - 1) / 2 / y1, 2) - 2*x1;
	*y3 = ((3*x1*x1 - 1) / 2 / y1) * (x1 - *x3) - y1;
}

void init_pool() {
	pool = malloc(sizeof(point) * 4);
	pool_alloc = 4;
	pool_used = 0;
}

void pool_grow() {
	if (pool_used == pool_alloc) {
		pool_alloc *= 2;
		pool = realloc(pool, sizeof(point) * pool_alloc);
	}
}

point* find_pool(size_t n) {
	for (size_t i = 0; i < pool_used; ++i) {
		if (pool[i].n == n) return &pool[i];
	}
	return NULL;
}

void add_pool(point p) {
	point* pp = find_pool(p.n);
	if (pp != NULL) {
		memmove(pp, &p, sizeof(p));
	} else {
		pool_grow();
		memmove(&pool[pool_used], &p, sizeof(p));
		++pool_used;
	}
}

size_t pow_size(size_t x, size_t n) {
	if (n == 0) {
		return 1;
	} else {
		return x * pow_size(x, n-1);
	}
}

void gen_point(size_t n) {
	point* p = find_pool(n);
	if (p == NULL) {
		gen_point(n/2);
		point* p_half = find_pool(n/2);
		double x, y;
		add_eq(p_half->x, p_half->y, &x, &y);
		point new = { .n = n, .x = x, .y = y };
		add_pool(new);
	}
}

void debug_pool() {
	puts("Points used for calculations:");
	for (size_t i = 0; i < pool_used; ++i) {
		point p = pool[i];
		printf("Point n=%zu x=%f y=%f\n", p.n, p.x, p.y);
	}
}

int main() {
	init_pool();
	point P = { .n = 1, .x = 36.0, .y = 87.0 };
	add_pool(P);
	size_t N = 111;
	printf("Task: N=%zu, P(%f; %f)\n", N, P.x, P.y);
	for (size_t i = 0; i < sizeof(N) * 8; ++i) {
		if (N & (((size_t) 1) << i)) {
			size_t n = pow_size(2, i);
			gen_point(n);
		}
	}
	double x = P.x, y = P.y;
	for (size_t i = 1; i < sizeof(N) * 8; ++i) {
		if (N & (((size_t) 1) << i)) {
			size_t n = pow_size(2, i);
			point* p = find_pool(n);
			double new_x, new_y;
			add_diff(x, y, p->x, p->y, &new_x, &new_y);
			x = new_x;
			y = new_y;
		}
	}
	debug_pool();
	printf("Answer: n=%zu, (%f; %f)\n", N, x, y);
}
