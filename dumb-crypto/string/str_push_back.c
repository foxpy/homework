#include <string.h>
#include "str.h"
#include "qc.h"

void str_push_back(str* dst, char const* src) {
    size_t src_len = strlen(src);
    if (dst->size + src_len + 1 > dst->alloc) {
        dst->alloc *= 2;
        dst->c_str = erealloc(dst->c_str, dst->alloc);
    }
    strcat(dst->c_str, src);
    dst->size += src_len;
}
