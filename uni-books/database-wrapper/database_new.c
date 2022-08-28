#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <qc/error.h>
#include "database-wrapper_impl/database-wrapper_impl.h"

static qc_result touch_file(char const* path, qc_err* err) {
    errno = 0;
    FILE* f = fopen(path, "w+");
    if (f == NULL) {
        qc_err_set(err, "Failed to create file %s: %s", path, strerror(errno));
        return QC_FAILURE;
    } else {
        fclose(f);
        return QC_SUCCESS;
    }
}

bool database_new(char const* path, char** err, char const* admin_password) {
    qc_err* qcerr = qc_err_new();
    if (touch_file(path, qcerr) == QC_FAILURE) {
        qc_err_append_front(qcerr, "Failed to create database");
        *err = qc_err_to_owned_c_str(qcerr);
        return false;
    } else {
        sqlite3* conn;
        if (sqlite3_open(path, &conn) != SQLITE_OK) {
            qc_err_set(qcerr, "Failed to create database %s: %s", path, sqlite3_errmsg(conn));
            if (conn != NULL) {
                sqlite3_close(conn);
            }
            return false;
        }
        char* sqlite_error;
        if (sqlite3_exec(conn, schema, NULL, NULL, &sqlite_error) != SQLITE_OK) {
            qc_err_set(qcerr, "Failed to create schema: %s", sqlite_error);
            sqlite3_free(sqlite_error);
            *err = qc_err_to_owned_c_str(qcerr);
            return false;
        }
        sqlite3_close(conn);
        qc_err_free(qcerr);
        db* wrapper = database_open(path, err);
        if (wrapper == NULL) {
            return false;
        }
        if (database_register(wrapper, "admin", admin_password, true, err) == false) {
            return false;
        }
        database_close(wrapper);
        return true;
    }
}
