#include <stdio.h>
#include <string.h>
#include <math.h>
#include "qc.h"
#include "crypto.h"

static size_t* parse_square(char const* square_str, size_t* len) {
    size_t commas = 0;
    for (size_t i = 0, end = strlen(square_str); i < end; ++i) {
        if (square_str[i] == ',') {
            ++commas;
        }
    }
    *len = commas + 1;
    if ((size_t) pow(sqrt((double)(commas + 1)), 2) == commas + 1) {
        size_t* square = emalloc((commas + 1) * sizeof(size_t));
        char const* input = square_str;
        char* comma;
        for (size_t i = 0; i < commas + 1; ++i) {
            unsigned long long parsed = strtoull(input, &comma, 10);
            input = &comma[1];
            square[i] = parsed;
        }
        return square;
    } else {
        fprintf(stderr, "Wrong magic square size, must be either 3x3, 4x4, 5x5 and so on\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]) {
    char* mode;
    char* square;
    qc_args* args = qc_args_new();
    qc_args_string_default(args, "mode", "encrypt", &mode, "encrypt | decrypt (default: encrypt)");
    qc_args_string(args, "square", &square, "magic square, example: \"2,7,6,9,5,1,4,3,8\"");
    char* err;
    if (qc_args_parse(args, argc, argv, &err) == -1) {
        fprintf(stderr, "Failed to parse command line: %s\n", err);
        exit(EXIT_FAILURE);
    }
    if (qc_args_positionals_count(args) != 1) {
        fprintf(stderr, "Failed to parse command line: provide input message as last argument\n");
    } else {
        size_t len;
        size_t* square_table = parse_square(square, &len);
        char* cipher_output;
        if (strcmp(mode, "encrypt") == 0) {
            cipher_output = magic_square_encrypt(argv[qc_args_positionals_index(args)], len, square_table);
        } else {
            cipher_output = magic_square_decrypt(argv[qc_args_positionals_index(args)], len, square_table);
        }
        printf("%s\n", cipher_output);
        free(square_table);
        free(cipher_output);
    }
    free(mode);
    qc_args_free(args);
}
