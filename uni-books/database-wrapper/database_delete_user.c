#include <stddef.h>
#include <stdbool.h>
#include "database-wrapper_impl/database-wrapper_impl.h"

bool database_delete_user(db* database, char const* username, char** err) {
    qc_err* qcerr = qc_err_new();
    struct user u;
    if (get_user(username, database->db_file, &u, qcerr) != QC_SUCCESS) {
        *err = qc_err_to_owned_c_str(qcerr);
        return false;
    }
    qc_err_free(qcerr);
    if (u.username == NULL) {
        *err = sprintf_alloc("User \"%s\" does not exist", username);
        return false;
    } else {
        char const* query = "DELETE FROM Users WHERE username LIKE ?1";
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(database->db_file, query, STMT_NULL_TERMINATED, &stmt, NULL);
        sqlite3_bind_text(stmt, 1, username, STMT_NULL_TERMINATED, SQLITE_STATIC);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        return true;
    }
}
