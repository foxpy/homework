#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "qc.h"
#include "crypto.h"

int main(int argc, char *argv[]) {
    bool decrypt;
    qc_args* args = qc_args_new();
    qc_args_flag(args, 'd', "decrypt", &decrypt, "decrypt instead of encrypting");
    char* err;
    if (qc_args_parse(args, argc, argv, &err) == -1) {
        fprintf(stderr, "Failed to parse arguments: %s\n", err);
        free(err);
        exit(EXIT_FAILURE);
    }
    qc_args_free(args);
    char buf[BUFSIZ];
    while (fgets(buf, BUFSIZ, stdin) == buf) {
        char* output;
        if (decrypt) {
            output = polybius_square_decrypt(buf);
        } else {
            output = polybius_square_encrypt(buf);
        }
        fputs(output, stdout);
        free(output);
    }
    putchar('\n');
}
