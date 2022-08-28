#include <stdbool.h>
#include <string.h>
#include <qc.h>
#include "database-wrapper_impl/database-wrapper_impl.h"

#define MIN_PASSWORD_LEN 8
#define MAX_PASSWORD_LEN 40

bool database_register(db* database, char const* username, char const* password, bool is_admin, char** err) {
    struct user user;
    char hash[HASH_STR_SIZE];
    qc_err* qcerr = qc_err_new();
    if (!validate_username(username, qcerr)) {
        qc_err_append_front(qcerr, "Invalid username");
        *err = qc_err_to_owned_c_str(qcerr);
        return false;
    } else if (get_user(username, database->db_file, &user, qcerr) == QC_SUCCESS && user.username != NULL) {
        qc_err_set(qcerr, "Username %s is already taken", username);
        *err = qc_err_to_owned_c_str(qcerr);
        return false;
    } else if (strlen(password) < MIN_PASSWORD_LEN) {
        qc_err_set(qcerr, "Password too short, minimum password length: %d", MIN_PASSWORD_LEN);
        *err = qc_err_to_owned_c_str(qcerr);
        return false;
    } else if (strlen(password) > MAX_PASSWORD_LEN) {
        qc_err_set(qcerr, "Password too long, maximum password length: %d", MAX_PASSWORD_LEN);
        *err = qc_err_to_owned_c_str(qcerr);
        return false;
    }
    qc_err_free(qcerr);
    hash_password(password, hash);
    sqlite3_stmt* stmt;
    char const* query = "INSERT INTO Users(is_admin, username, password_hash) VALUES(?1, ?2, ?3);";
    sqlite3_prepare_v2(database->db_file, query, STMT_NULL_TERMINATED, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, is_admin);
    sqlite3_bind_text(stmt, 2, username, STMT_NULL_TERMINATED, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, hash, STMT_NULL_TERMINATED, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return true;
}
