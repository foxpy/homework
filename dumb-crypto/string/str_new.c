#include "str.h"
#include "qc.h"

#define DEFAULT_STRING_SIZE 256

str* str_new() {
    str* ret = emalloc(sizeof(str));
    ret->c_str = emalloc(DEFAULT_STRING_SIZE);
    ret->c_str[0] = '\0';
    ret->size = 0;
    ret->alloc = DEFAULT_STRING_SIZE;
    return ret;
}
