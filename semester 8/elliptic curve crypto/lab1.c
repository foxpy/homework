#include <stdio.h>
#include <math.h>

typedef struct point {
	double x;
	double y;
} point;

void add_diff(double x1, double y1, double x2, double y2, double* x3, double *y3) {
	*x3 = pow((y2 - y1) / (x2 - x1), 2) - x1 - x2;
	*y3 = (y2 - y1) / (x2 - x1) * (x1 - *x3) - y1;
}

void add_eq(double x1, double y1, double *x3, double* y3) {
	*x3 = pow((3*x1*x1 - 1) / 2 / y1, 2) - 2*x1;
	*y3 = ((3*x1*x1 - 1) / 2 / y1) * (x1 - *x3) - y1;
}

int main(void) {
	point twoP;
	add_eq(59, 386, &twoP.x, &twoP.y);
	point twoQ;
	add_eq(70, 195, &twoQ.x, &twoQ.y);
	point threeQ;
	add_diff(twoQ.x, twoQ.y, 70, 195, &threeQ.x, &threeQ.y);
	point twoP_threeQ;
	add_diff(twoP.x, twoP.y, threeQ.x, threeQ.y, &twoP_threeQ.x, &twoP_threeQ.y);
	point result;
	add_diff(twoP_threeQ.x, twoP_threeQ.y, 72, -254, &result.x, &result.y);
	printf("2P + 3Q - R = (%f; %f)\n", result.x, result.y);
}
