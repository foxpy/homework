#pragma once
#include <stddef.h>

struct str {
    char* c_str;
    size_t size;
    size_t alloc;
};
typedef struct str str;

str* str_new();
void str_push_back(str* dst, char const* src);
void str_push_unicode_character_back(str* dst, char const* src);
char* str_to_c(str* str);
