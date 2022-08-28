#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <qc.h>
#include "needle.h"

int main(int argc, char *argv[]) {
    double l = 0.0;
    double t = 0.0;
    size_t n = 0;
    qc_args* args = qc_args_new();
    qc_args_double(args, "length", &l, "Length of needle");
    qc_args_double(args, "distance", &t, "Distance between lines");
    qc_args_unsigned(args, "iterations", &n, "Number of dropped needles");
    char* err;
    if (qc_args_parse(args, argc, argv, &err) == -1) {
        fprintf(stderr, "Failed to parse arguments: %s\n", err);
        free(err);
        exit(EXIT_FAILURE);
    } else if (l == 0.0 || t == 0.0 || n == 0) {
        qc_args_call_help(args);
        exit(EXIT_FAILURE);
    } else if (l <= DBL_EPSILON) {
        die("Fatal: length is too small");
    } else if (t <= DBL_EPSILON) {
        die("Fatal: distance is too small");
    } else if (n <= 0) {
        die("Fatal: number of iterations should be nonzero");
    } else if (l >= t) {
        die("Fatal: expected length < distance");
    }

    qc_rnd rnd;
    qc_rnd_init(&rnd);
    size_t crossed = 0;
    needle ndl;
    for (size_t i = 0; i < n; ++i) {
        drop_needle(&rnd, &ndl, t);
        if (needle_crosses(&ndl, l, t)) ++crossed;
    }

    if (crossed == 0) {
        printf("Any needle did not cross the line.\n");
    } else {
        double P = (double) crossed / n;
        double pi = (2 * l) / (t * P);
        printf("pi = %f\n", pi);
    }
    return EXIT_SUCCESS;
}
