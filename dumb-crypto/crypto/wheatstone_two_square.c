#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stddef.h>
#include "crypto.h"
#include "str.h"
#include "unicode.h"

#define TABLE_X 5
#define TABLE_Y 7

static char const* table1[] = {
        "Ж", "Щ", "Н", "Ю", "Р",
        "И", "Т", "Ь", "Ц", "Б",
        "Я", "М", "Е", ".", "С",
        "В", "Ы", "П", "Ч", " ",
        ":", "Д", "У", "О", "К",
        "З", "Э", "Ф", "Г", "Ш",
        "Х", "А", ",", "Л", "Ъ",
};
#define TABLE1_LENGTH (sizeof(table1)/sizeof(table1[0]))
static_assert(TABLE_X * TABLE_Y == TABLE1_LENGTH, "Table 1 dimensions are wrong");

static char const* table2[] = {
        "И", "Ч", "Г", "Я", "Т",
        ",", "Ж", "Ь", "М", "О",
        "З", "Ю", "Р", "В", "Щ",
        "Ц", ":", "П", "Е", "Л",
        "Ъ", "А", "Н", ".", "Х",
        "Э", "К", "С", "Ш", "Д",
        "Б", "Ф", "У", "Ы", " ",
};
#define TABLE2_LENGTH (sizeof(table2)/sizeof(table2[0]))
static_assert(TABLE_X * TABLE_Y == TABLE2_LENGTH, "Table 2 dimensions are wrong");

static_assert(TABLE1_LENGTH == TABLE2_LENGTH, "Table sizes should be equal");

static ptrdiff_t table_lookup(size_t len, char const* table[static len], char const* symbol) {
    for (size_t i = 0; i < len; ++i) {
        if (strncmp(table[i], symbol, unicode_symbol_len(symbol)) == 0) {
            return i;
        }
    }
    return -1;
}

static void symbol_coordinates(size_t *x, size_t *y, char const** table, char const* symbol) {
    ptrdiff_t coord = table_lookup(TABLE_X * TABLE_Y, table, symbol);
    assert(coord >= 0);
    *x = coord % TABLE_X;
    *y = coord / TABLE_X;
}

static void permute(char const** out1, char const** out2,
                    char const* in1, char const* in2) {
    size_t in1_x, in1_y, in2_x, in2_y;
    symbol_coordinates(&in1_x, &in1_y, table1, in1);
    symbol_coordinates(&in2_x, &in2_y, table2, in2);
    size_t out1_x = in2_x, out1_y = in1_y;
    size_t out2_x = in1_x, out2_y = in2_y;
    *out1 = table2[out1_y * TABLE_X + out1_x];
    *out2 = table1[out2_y * TABLE_X + out2_x];
}

static void depermute(char const** out1, char const** out2,
                      char const* in1, char const* in2) {
    size_t in1_x, in1_y, in2_x, in2_y;
    symbol_coordinates(&in1_x, &in1_y, table2, in1);
    symbol_coordinates(&in2_x, &in2_y, table1, in2);
    size_t out1_x = in2_x, out1_y = in1_y;
    size_t out2_x = in1_x, out2_y = in2_y;
    *out1 = table1[out1_y * TABLE_X + out1_x];
    *out2 = table2[out2_y * TABLE_X + out2_x];
}

static char* wheatstone_two_square_impl(char const* input_str, bool encrypt) {
    str* encrypted = str_new();
    size_t i = 0;
    while (unicode_characters(&input_str[i]) >= 2) {
        size_t symbol1_length = unicode_symbol_len(&input_str[i]);
        char const* input_symbol1 = &input_str[i];
        i += symbol1_length;
        size_t symbol2_length = unicode_symbol_len(&input_str[i]);
        char const* input_symbol2 = &input_str[i];
        i += symbol2_length;
        char const* output_symbol1;
        char const* output_symbol2;
        if (encrypt) {
            permute(&output_symbol1, &output_symbol2, input_symbol1, input_symbol2);
        } else {
            depermute(&output_symbol1, &output_symbol2, input_symbol1, input_symbol2);
        }
        str_push_unicode_character_back(encrypted, output_symbol1);
        str_push_unicode_character_back(encrypted, output_symbol2);
    }
    return str_to_c(encrypted);
}

char* wheatstone_two_square_encrypt(char const* input_str) {
    return wheatstone_two_square_impl(input_str, true);
}

char* wheatstone_two_square_decrypt(char const* input_str) {
    return wheatstone_two_square_impl(input_str, false);
}
