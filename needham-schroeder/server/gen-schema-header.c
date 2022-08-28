#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include <qc.h>

static void help(void* help_data) {
    char* program_name = help_data;
    fprintf(stderr, "Usage: %s SCHEMA.sql HEADER.h\n", program_name);
}


static qc_result check_num_arguments(qc_args* args, qc_err* err) {
    if (qc_args_positionals_count(args) == 2) {
        return QC_SUCCESS;
    } else {
        qc_err_set(err, "Expected two positional arguments, see --help");
        return QC_FAILURE;
    }
}

static qc_result open_files(char const* schema_str, char const* header_str, FILE** schema_file, FILE** header_file,
                            qc_err* err) {
    if (!(errno = 0) && (*schema_file = fopen(schema_str, "r")) == NULL) {
        qc_err_set(err, "Failed to open schema file \"%s\" for reading: %s", schema_str, strerror(errno));
        return QC_FAILURE;
    } else if (!(errno = 0) && (*header_file = fopen(header_str, "w")) == NULL) {
        qc_err_set(err, "Failed to open header file \"%s\" for writing: %s", header_str, strerror(errno));
        fclose(*schema_file);
        return QC_FAILURE;
    } else {
        return QC_SUCCESS;
    }
}


static void main_loop(FILE* schema, FILE* header) {
    fputs("#pragma once\nchar const* schema =\n", header);
    char* line = NULL;
    size_t n = 0;
    for (;;) {
        ssize_t num_read = getline(&line, &n, schema);
        if (num_read < 0) {
            break;
        } else {
            fputc('"', header);
            for (ssize_t i = 0; i < num_read; ++i) {
                if (line[i] != '\n') {
                    fputc(line[i], header);
                }
            }
            fputs("\\n\"\n", header);
        }
    }
    fputs(";\n", header);
}

int main(int argc, char* argv[]) {
    qc_err* err = qc_err_new();
    qc_args* args = qc_args_new();
    qc_args_set_help(args, help, argv[0]);
    if (qc_args_parse(args, argc, argv, err) == QC_FAILURE || check_num_arguments(args, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to parse CLI arguments");
    } else {
        int idx = qc_args_positionals_index(args);
        char const* schema_path = argv[idx+0];
        char const* header_path = argv[idx+1];
        FILE* schema;
        FILE* header;
        if (open_files(schema_path, header_path, &schema, &header, err) == QC_FAILURE) {
            qc_err_fatal(err, "Failed to open requested files");
        } else {
            main_loop(schema, header);
        }
        fclose(schema);
        fclose(header);
    }
    qc_args_free(args);
    qc_err_free(err);
}
