#include <stddef.h>
#include "database-wrapper_impl/database-wrapper_impl.h"

static ptrdiff_t get_users_count(sqlite3* conn, char** err) {
    int rc;
    char const* query = "SELECT count(user_id) FROM Users;";
    sqlite3_stmt* stmt;
    if ((rc = sqlite3_prepare_v2(conn, query, STMT_NULL_TERMINATED, &stmt, NULL)) != SQLITE_OK) {
        *err = sprintf_alloc("Failed to get number of users: %s", sqlite3_errstr(rc));
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_step(stmt);
    sqlite3_uint64 ret = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    return ret;
}

ptrdiff_t database_get_users(db* database, struct user** dst, char** err) {
    sqlite3_stmt* stmt;
    {
        int rc;
        char const* query = "SELECT is_admin, username, password_hash FROM Users;";
        if ((rc = sqlite3_prepare_v2(database->db_file, query, STMT_NULL_TERMINATED, &stmt, NULL)) != SQLITE_OK) {
            *err = sprintf_alloc("Failed to get list of users: %s", sqlite3_errstr(rc));
            sqlite3_finalize(stmt);
            return -1;
        }
    }
    ptrdiff_t num_users = get_users_count(database->db_file, err);
    if (num_users < 0) {
        sqlite3_finalize(stmt);
        return -1;
    } else if (num_users == 0) {
        *dst = NULL;
        sqlite3_finalize(stmt);
        return 0;
    } else {
        struct user* users = emalloc(sizeof(struct user) * num_users);
        *dst = users;
        for (size_t i = 0, end = num_users; i < end; ++i) {
            sqlite3_step(stmt);
            users[i].is_admin = sqlite3_column_int(stmt, 0);
            unsigned char const* username = sqlite3_column_text(stmt, 1);
            unsigned char const* password_hash = sqlite3_column_text(stmt, 2);
            users[i].username = sprintf_alloc("%s", username);
            users[i].password_hash = sprintf_alloc("%s", password_hash);
        }
        sqlite3_finalize(stmt);
        return num_users;
    }
}
