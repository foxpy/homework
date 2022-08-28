#include <string.h>
#include "str.h"
#include "qc.h"

void basic_test() {
    str* str = str_new();
    for (size_t i = 0; i < 200; ++i) {
        str_push_back(str, "test");
        str_push_back(str, "тест");
    }
    char* result = str_to_c(str);
    char* s = result;
    for (size_t i = 0; i < 200; ++i) {
        qc_assert(strncmp(s, "test", strlen("test")) == 0, "String corrupts data");
        s += strlen("test");
        qc_assert(strncmp(s, "тест", strlen("тест")) == 0, "String corrupts data");
        s += strlen("тест");
    }
    free(result);
}

void unicode_test() {
    str* str = str_new();
    str_push_unicode_character_back(str, "ВОЛГА");
    str_push_unicode_character_back(str, "ЕНИСЕЙ");
    char* result = str_to_c(str);
    qc_assert(strcmp(result, "ВЕ") == 0, "str_push_unicode_character_back inserts garbage");
    free(result);
}

int main() {
    basic_test();
    unicode_test();
}
