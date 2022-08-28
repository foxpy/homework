#include "str.h"
#include "qc.h"

char* str_to_c(str* str) {
    str->c_str = erealloc(str->c_str, str->size + 1);
    char* ret = str->c_str;
    free(str);
    return ret;
}
