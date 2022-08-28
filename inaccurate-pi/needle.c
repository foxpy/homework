#include <math.h>
#include <qc.h>
#include "needle.h"

void drop_needle(qc_rnd *rnd, needle *ndl, double t) {
    ndl->x = qc_rnd_range_fp64(rnd, 0.0, t);
    ndl->angle = qc_rnd_range_fp64(rnd, 0.0, 360.0);
}

int needle_crosses(needle *ndl, double l, double t) {
    double pi = acos(-1);
    double a = l * cos(ndl->angle * pi / 180);
    if (ndl->x + fabs(a) > t) return 1;
    else return 0;
}
