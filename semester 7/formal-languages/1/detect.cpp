#include <iostream>
#include <string>
#include "detecter.hpp"

int main() {
    std::string input;
    std::getline(std::cin, input);
    if (corresponds(input)) {
        std::cout << "YES" << std::endl;
        std::exit(EXIT_SUCCESS);
    } else {
        std::cout << "NO" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
