#include <iostream>
#include "15.hpp"

unsigned long long lab15() {
    unsigned long long input;
    std::cin >> input;
    unsigned long long sum = 0;
    while (input > 0) {
        sum += input % 10;
        input /= 10;
    }
    return sum;
}
