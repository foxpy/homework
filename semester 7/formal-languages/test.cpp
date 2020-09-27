#include "detecter.hpp"
#include <iostream>
#include <string>

static const char* valid[] = {
        "aaaabb",
        "qqv",
        "WWWWvv",
        "ppppppppppPPPPP",
};

static const char* invalid[] = {
        "aaabb",
        "qqvvv",
        "asdf",
        "ppppjq",
};

int main() {
    for (std::string str : valid) {
        if (!corresponds(str)) {
            std::cout << "Failed for valid: " << str << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    for (std::string str : invalid) {
        if (corresponds(str)) {
            std::cout << "Failed for invalid: " << str << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}
