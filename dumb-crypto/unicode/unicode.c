#include <string.h>
#include <stdint.h>
#include "unicode.h"

size_t unicode_symbol_len(char const str[static 1]) {
    uint8_t c = str[0];
    if ((c & 0x80u) == 0x00u) {
        return 1;
    } else if ((c & 0xe0u) == 0xc0u) {
        return 2;
    } else if ((c & 0xf0u) == 0xe0u) {
        return 3;
    } else if ((c & 0xf8u) == 0xf0u) {
        return 4;
    } else if ((c & 0xfcu) == 0xf8u) {
        return 5;
    } else {
        return 6;
    }
}

size_t unicode_characters(char const str[static 1]) {
    size_t i = 0, end = strlen(str);
    size_t ret = 0;
    while (i < end) {
        size_t symbol_length = unicode_symbol_len(&str[i]);
        ++ret;
        i += symbol_length;
    }
    return ret;
}
