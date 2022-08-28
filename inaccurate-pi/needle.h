#ifndef __INACCURATE_PI_NEEDLE_H
#define __INACCURATE_PI_NEEDLE_H

#include <qc.h>

struct needle {
    double x;
    double angle; /* deg */
};
typedef struct needle needle;

void drop_needle(qc_rnd *rnd, needle *ndl, double t);
int needle_crosses(needle *ndl, double l, double t);

#endif
