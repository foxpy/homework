#include <iostream>
#include <cmath>
#include "18.hpp"

const double eps = 10e-9;

static double f(double x) {
    if (x - eps < 0.5) {
        return sin(M_PI/2);
    } else {
        return sin((x - 1) * M_PI_2);
    }
}

void lab18() {
    for (int i = -4; i < 14; ++i) {
        double x = i / 10.0;
        std::cout << x << ": " << f(x) << std::endl;
    }
}
