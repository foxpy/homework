#include <string>
#include <cstdlib>
#include "4.hpp"

std::string octal_to_decimal(std::string const& str) {
    std::string decimal;
    unsigned long long ull = std::strtoull(str.c_str(), nullptr, 8);
    decimal = std::to_string(ull);
    return decimal;
}
