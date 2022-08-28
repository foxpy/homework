#include <qc.h>
#include <string.h>
#include <sqlite3.h>
#include "database-wrapper_impl/database-wrapper_impl.h"

static void add_test_user(sqlite3* db, char const* username, char const* password_hash) {
    static char const* query = "INSERT INTO Users(is_admin, username, password_hash) VALUES(TRUE, ?1, ?2);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query, STMT_NULL_TERMINATED, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, STMT_NULL_TERMINATED, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password_hash, STMT_NULL_TERMINATED, SQLITE_STATIC);
    int rc = sqlite3_step(stmt);
    qc_assert(rc == SQLITE_DONE, sqlite3_errstr(rc));
    sqlite3_finalize(stmt);
}

void get_user_impl_test() {
    char const* username = "admin";
    char const* password_hash = "Some long n scary hash string";
    struct user user = {0};
    sqlite3* conn;
    int rc;
    char* err;
    bool result;
    rc = sqlite3_open_v2("test", &conn, SQLITE_OPEN_MEMORY | SQLITE_OPEN_READWRITE, NULL);
    qc_assert(rc == SQLITE_OK, sqlite3_errstr(rc));
    rc = sqlite3_exec(conn, schema, NULL, NULL, &err);
    qc_assert(rc == SQLITE_OK, err);
    add_test_user(conn, username, password_hash);
    qc_err* qcerr = qc_err_new();
    result = get_user("admin", conn, &user, qcerr);
    qc_assert_format(result == QC_SUCCESS, "Failed to get user which sure exists in a database: %s", qc_err_get(qcerr));
    qc_assert(strcmp(user.username, username) == 0, "Username does not match");
    qc_assert(strcmp(user.password_hash, password_hash) == 0, "Password hash does not match");
    free(user.username);
    free(user.password_hash);
    result = get_user("manager", conn, &user, qcerr);
    qc_assert_format(result == QC_SUCCESS, "get_user subroutine has failed: %s", qc_err_get(qcerr));
    qc_assert(user.username == NULL, "Got username for user which sure does not exist");
    qc_assert(user.password_hash == NULL, "Got password hash for user which sure does not exist");
    sqlite3_close(conn);
    qc_err_free(qcerr);
}

void get_users_public_api_test() {
    sqlite3* conn;
    int rc;
    char* err;
    rc = sqlite3_open_v2("test", &conn, SQLITE_OPEN_MEMORY | SQLITE_OPEN_READWRITE, NULL);
    qc_assert(rc == SQLITE_OK, sqlite3_errstr(rc));
    rc = sqlite3_exec(conn, schema, NULL, NULL, &err);
    qc_assert(rc == SQLITE_OK, err);
    add_test_user(conn, "petya", "petya_hash");
    add_test_user(conn, "vasya", "vasya_hash");
    add_test_user(conn, "maria", "maria_hash");
    user* users;
    db database = { conn };
    ptrdiff_t result = database_get_users(&database, &users, &err);
    qc_assert_format(result == 3, "Expected 3 users, got: %zi", result);
    qc_assert(users[0].is_admin, "petya is expected to be admin");
    qc_assert(users[1].is_admin, "vasya is expected to be admin");
    qc_assert(users[2].is_admin, "maria is expected to be admin");
    qc_assert_format(strcmp(users[0].username, "petya") == 0, "petya's username does not match: %s", users[0].username);
    qc_assert_format(strcmp(users[1].username, "vasya") == 0, "vasya's username does not match: %s", users[1].username);
    qc_assert_format(strcmp(users[2].username, "maria") == 0, "maria's username does not match: %s", users[2].username);
    qc_assert_format(strcmp(users[0].password_hash, "petya_hash") == 0,
                     "petya's hash does not match: %s", users[0].password_hash);
    qc_assert_format(strcmp(users[1].password_hash, "vasya_hash") == 0,
                     "vasya's hash does not match: %s", users[1].password_hash);
    qc_assert_format(strcmp(users[2].password_hash, "maria_hash") == 0,
                     "maria's hash does not match: %s", users[2].password_hash);
    for (size_t i = 0; i < 3; ++i) {
        free(users[i].username);
        free(users[i].password_hash);
    }
    free(users);
    users = NULL;
    sqlite3_close(conn);
    rc = sqlite3_open_v2("test", &conn, SQLITE_OPEN_MEMORY | SQLITE_OPEN_READWRITE, NULL);
    qc_assert(rc == SQLITE_OK, sqlite3_errstr(rc));
    rc = sqlite3_exec(conn, schema, NULL, NULL, &err);
    qc_assert(rc == SQLITE_OK, err);
    database.db_file = conn;
    result = database_get_users(&database, &users, &err);
    qc_assert_format(result == 0, "Expected 0 users, got: %zi", result);
    qc_assert(users == NULL, "users array is initialized but it should not be");
    sqlite3_close(conn);
}

int main() {
    get_user_impl_test();
    get_users_public_api_test();
}
