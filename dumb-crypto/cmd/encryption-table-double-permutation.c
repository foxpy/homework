#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "qc.h"
#include "crypto.h"

static bool check_permutation(size_t const permutation[static 4]) {
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            if (i != j && permutation[i] == permutation[j]) {
                return false;
            }
        }
    }
    return true;
}

static size_t* parse_permutation(char const permutation_str[static 1]) {
    size_t commas = 0;
    for (size_t i = 0, end = strlen(permutation_str); i < end; ++i) {
        if (permutation_str[i] == ',') {
            ++commas;
        }
    }
    if (commas == 3) {
        size_t* table = emalloc(4 * sizeof(size_t));
        char const* input = permutation_str;
        char* comma;
        for (size_t i = 0; i < commas + 1; ++i) {
            unsigned long long parsed = strtoull(input, &comma, 10);
            input = &comma[1];
            table[i] = parsed;
        }
        if (check_permutation(table)) {
            return table;
        } else {
            fprintf(stderr, "\"%zu,%zu,%zu,%zu\" is not a valid permutation\n",
                    table[0], table[1], table[2], table[3]);
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Wrong permutation size, must be 4\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]) {
    char* mode;
    char* permutation_x;
    char* permutation_y;
    qc_args* args = qc_args_new();
    qc_args_string_default(args, "mode", "encrypt", &mode, "encrypt | decrypt (default: encrypt)");
    qc_args_string(args, "permutation-x", &permutation_x, "permutation X, example: \"0,2,1,3\"");
    qc_args_string(args, "permutation-y", &permutation_y, "permutation Y, example: \"0,2,1,3\"");
    char* err;
    if (qc_args_parse(args, argc, argv, &err) == -1) {
        fprintf(stderr, "Failed to parse command line: %s\n", err);
        exit(EXIT_FAILURE);
    }
    if (qc_args_positionals_count(args) != 1) {
        fprintf(stderr, "Failed to parse command line: provide input message as last argument\n");
    } else {
        size_t* horizontal_permutation = parse_permutation(permutation_x);
        size_t* vertical_permutation = parse_permutation(permutation_y);
        char* cipher_output;
        if (strcmp(mode, "encrypt") == 0) {
            cipher_output = encryption_table_double_permutation_encrypt(
                    argv[qc_args_positionals_index(args)],
                    4, horizontal_permutation,
                    4, vertical_permutation
            );
        } else {
            cipher_output = encryption_table_double_permutation_decrypt(
                    argv[qc_args_positionals_index(args)],
                    4, horizontal_permutation,
                    4, vertical_permutation
            );
        }
        printf("%s\n", cipher_output);
        free(permutation_x);
        free(permutation_y);
        free(horizontal_permutation);
        free(vertical_permutation);
        free(cipher_output);
    }
    free(mode);
    qc_args_free(args);
}
