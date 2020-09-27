#include "detecter.hpp"

bool corresponds(const std::string &str) {
    if (str.empty()) {
        return false;
    }
    size_t a_cnt = 0, b_cnt = 0;
    char a = str.front();
    char b = str.back();
    for (char c : str) {
        if (c == a) {
            ++a_cnt;
        } else if (c == b) {
            ++b_cnt;
        } else {
            return false;
        }
    }
    if (b_cnt * 2 == a_cnt) {
        return true;
    } else {
        return false;
    }
}
