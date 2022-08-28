#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <qc.h>
#include "server.h"
#include "schema.h"

server_ctx* server_init(char const* database_path, qc_err* err) {
    server_ctx* server = qc_malloc(sizeof(server_ctx));
    memset(server, 0, sizeof(server_ctx));
    int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX;
    char* zErr;
    if (sqlite3_open_v2(database_path, &server->conn, flags, NULL) != SQLITE_OK) {
        char const* err_msg = (server->conn == NULL) ? "not enough memory" : sqlite3_errmsg(server->conn);
        qc_err_set(err, "Unable to open \"%s\": %s", database_path, err_msg);
        goto fail;
    } else if (sqlite3_exec(server->conn, schema, NULL, NULL, &zErr) != SQLITE_OK) {
        qc_err_set(err, "Failed to apply database schema: %s", zErr);
        sqlite3_free(zErr);
        goto fail;
    }
    return server;
fail:
    sqlite3_close_v2(server->conn);
    free(server);
    return NULL;
}

void server_close(server_ctx* ctx) {
    sqlite3_close_v2(ctx->conn);
    free(ctx);
}

void user_free(user* user) {
    free(user->name);
    free(user->id);
    free(user->key);
    free(user);
}

qc_result user_write(sqlite3* conn, char const* username, const uint8_t* id, const uint8_t* key, qc_err* err) {
    char const* query = "insert into users(name, id, key) values(?1, ?2, ?3);";
    sqlite3_stmt* stmt;
    int rc;
    if ((rc = sqlite3_prepare_v2(conn, query, SQLITE3_STMT_NULL_TERMINATED, &stmt, NULL)) != SQLITE_OK ||
        (rc = sqlite3_bind_text(stmt, 1, username, SQLITE3_STMT_NULL_TERMINATED, SQLITE_STATIC)) != SQLITE_OK ||
        (rc = sqlite3_bind_blob(stmt, 2, id, 16, SQLITE_STATIC)) != SQLITE_OK ||
        (rc = sqlite3_bind_blob(stmt, 3, key, 32, SQLITE_STATIC)) != SQLITE_OK ||
        (rc = sqlite3_step(stmt)) != SQLITE_DONE) {
        goto fail;
    }
    sqlite3_finalize(stmt);
    return QC_SUCCESS;
fail:
    qc_err_set(err, "Failed to insert user into database: %s (%s)", sqlite3_errstr(rc), sqlite3_errmsg(conn));
    sqlite3_finalize(stmt);
    return QC_FAILURE;
}

qc_result server_register(server_ctx* ctx, char const* username, qc_err* err) {
    uint8_t id[16];
    uint8_t key[32];
    qc_result result;
    if (qc_rnd_os_buf(16, id, err) == QC_FAILURE) {
        qc_err_set(err, "Failed to generate ID");
        result = QC_FAILURE;
    } else if (qc_rnd_os_buf(32, key, err) == QC_FAILURE) {
        qc_err_set(err, "Failed to generate cryptographic key");
        result = QC_FAILURE;
    } else {
        result = user_write(ctx->conn, username, id, key, err);
    }
    if (result == QC_FAILURE) {
        qc_err_append_front(err, "Failed to register user \"%s\"", username);
        return QC_FAILURE;
    } else {
        return QC_SUCCESS;
    }
}

qc_result server_query(server_ctx* ctx, char const* username, user** dst, qc_err* err) {
    char const* query = "select name, lower(hex(id)), lower(hex(key)) from users where name = ?";
    sqlite3_stmt* stmt;
    int rc;
    if ((rc = sqlite3_prepare_v2(ctx->conn, query, SQLITE3_STMT_NULL_TERMINATED, &stmt, NULL)) != SQLITE_OK ||
        (rc = sqlite3_bind_text(stmt, 1, username, SQLITE3_STMT_NULL_TERMINATED, SQLITE_STATIC)) != SQLITE_OK) {
        goto fail;
    }
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *dst = qc_malloc(sizeof(user));
        user* u = *dst;
        u->name = strdup((char const*) sqlite3_column_text(stmt, 0));
        u->id = strdup((char const*) sqlite3_column_text(stmt, 1));
        u->key = strdup((char const*) sqlite3_column_text(stmt, 2));
    } else {
        *dst = NULL;
        return QC_SUCCESS;
    }
    sqlite3_finalize(stmt);
    return QC_SUCCESS;
fail:
    *dst = NULL;
    qc_err_set(err, "Failed to get user data from database: %s (%s)", sqlite3_errstr(rc), sqlite3_errmsg(ctx->conn));
    sqlite3_finalize(stmt);
    return QC_FAILURE;
}

qc_result server_unregister(server_ctx* ctx, char const* username, qc_err* err) {
    char const* query = "delete from users where name = ?;";
    sqlite3_stmt* stmt;
    int rc;
    if ((rc = sqlite3_prepare_v2(ctx->conn, query, SQLITE3_STMT_NULL_TERMINATED, &stmt, NULL)) != SQLITE_OK ||
        (rc = sqlite3_bind_text(stmt, 1, username, SQLITE3_STMT_NULL_TERMINATED, SQLITE_STATIC)) != SQLITE_OK ||
        (rc = sqlite3_step(stmt)) != SQLITE_DONE) {
        goto fail;
    }
    sqlite3_finalize(stmt);
    return QC_SUCCESS;
fail:
    qc_err_set(err, "Failed to remove user data from database: %s (%s)", sqlite3_errstr(rc), sqlite3_errmsg(ctx->conn));
    sqlite3_finalize(stmt);
    return QC_FAILURE;
}

qc_result server_dump_users(server_ctx* ctx, FILE* dst, qc_err* err) {
    char const* query = "select name from users;";
    sqlite3_stmt* stmt;
    int rc;
    if ((rc = sqlite3_prepare_v2(ctx->conn, query, SQLITE3_STMT_NULL_TERMINATED, &stmt, NULL)) != SQLITE_OK) {
        goto fail;
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        fprintf(dst, "%s\n", (char const*) sqlite3_column_text(stmt, 0));
    }
    if (rc != SQLITE_DONE) {
        goto fail;
    }
    sqlite3_finalize(stmt);
    return QC_SUCCESS;
fail:
    qc_err_set(err, "Failed to obtain user list from database: %s (%s)", sqlite3_errstr(rc), sqlite3_errmsg(ctx->conn));
    sqlite3_finalize(stmt);
    return QC_FAILURE;
}

qc_result server_get_key_by_id(server_ctx* ctx, uint8_t const id[static 16], uint8_t key[static 32], qc_err* err) {
    char const* query = "select key from users where id = ?1;";
    sqlite3_stmt* stmt;
    int rc;
    qc_result result;
    if ((rc = sqlite3_prepare_v2(ctx->conn, query, SQLITE3_STMT_NULL_TERMINATED, &stmt, NULL)) != SQLITE_OK ||
        (rc = sqlite3_bind_blob(stmt, 1, id, 16, SQLITE_STATIC)) != SQLITE_OK) {
        goto fail;
    }
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        memmove(key, sqlite3_column_blob(stmt, 0), 32);
        result = QC_SUCCESS;
    } else {
        qc_err_set(err, "No user exists with such ID");
        result = QC_FAILURE;
    }
    sqlite3_finalize(stmt);
    return result;
fail:
    qc_err_set(err, "Failed to obtain user data from database: %s (%s)", sqlite3_errstr(rc), sqlite3_errmsg(ctx->conn));
    sqlite3_finalize(stmt);
    return QC_FAILURE;
}
