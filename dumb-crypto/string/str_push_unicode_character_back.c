#include <string.h>
#include "str.h"
#include "unicode.h"

void str_push_unicode_character_back(str* dst, char const* src) {
    size_t len = unicode_symbol_len(src);
    char buf[8];
    strncpy(buf, src, len);
    buf[len] = '\0';
    str_push_back(dst, buf);
}
