#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <qc.h>
#include "ecc-exists.h"

enum estimation ecc_exists(size_t q, size_t n, size_t k, size_t d, bool verbose) {
    if ( q < 2) {
        verbose_print(verbose, "Ill-formed code: q < 2 is not meaningful\n");
        return CODE_DOES_NOT_EXIST;
    } else if (k >= n) {
        verbose_print(verbose, "Ill-formed code: no space to fit check bits\n");
        return CODE_DOES_NOT_EXIST;
    } else if (d == 0) {
        verbose_print(verbose, "Ill-formed code: it does not fix or even detect any errors by design\n");
        return CODE_DOES_NOT_EXIST;
    }

    bound_function bound_functions[] = {
        singleton_bound, hamming_bound, gilbert_bound, gilbert_varshamov_bound,
    };
    for (size_t i = 0; i < sizeof(bound_functions)/sizeof(bound_functions[0]); ++i) {
        enum estimation ret = bound_functions[i](q, n, k, d, verbose);
        switch (ret) {
            case CODE_PROBABLY_EXISTS:
                continue;
            case CODE_EXISTS:
                return CODE_EXISTS;
            case CODE_DOES_NOT_EXIST:
                return CODE_DOES_NOT_EXIST;
            default:
                UNREACHABLE_CODE();
        }
    }
    return CODE_PROBABLY_EXISTS;
}

int main(int argc, char* argv[]) {
    size_t q, n, k, d;
    bool verbose = false;
    qc_args* args = qc_args_new();
    qc_args_unsigned(args, "q", &q, "Code bitness");
    qc_args_unsigned(args, "n", &n, "Code block length");
    qc_args_unsigned(args, "k", &k, "Information bits");
    qc_args_unsigned(args, "d", &d, "Hamming distance");
    qc_args_flag(args, 'v', "verbose", &verbose, "Spam terminal with thoughts");
    char* err;
    if (qc_args_parse(args, argc, argv, &err) == -1) {
        fprintf(stderr, "Failed to parse command line arguments: %s\n", err);
        free(err);
        qc_args_free(args);
        exit(EXIT_FAILURE);
    }

    enum estimation code_exists = ecc_exists(q, n, k, d, verbose);
    int status;
    char* verdict;
    switch (code_exists) {
        case CODE_EXISTS:
            verdict = "exists!";
            status = EXIT_SUCCESS;
            break;
        case CODE_DOES_NOT_EXIST:
            verdict = "does not exist!";
            status = EXIT_FAILURE;
            break;
        case CODE_PROBABLY_EXISTS:
            verdict = "probably exists?";
            status = EXIT_SUCCESS;
            break;
        default:
            UNREACHABLE_CODE();
    }
    printf("Code with provided parameters %s\n", verdict);
    qc_args_free(args);
    exit(status);
}
