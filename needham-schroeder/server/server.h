#pragma once
#include <stdio.h>
#include <stdint.h>
#include <qc.h>
#include <sqlite3.h>

#define SQLITE3_STMT_NULL_TERMINATED (-1)

typedef struct {
    sqlite3* conn;
} server_ctx;

typedef struct {
    char* name;
    char* id;
    char* key;
} user;

void user_free(user* user);

server_ctx* server_init(char const* database_path, qc_err* err);
void server_close(server_ctx* ctx);

qc_result server_register(server_ctx* ctx, char const* username, qc_err* err);
qc_result server_query(server_ctx* ctx, char const* username, user** dst, qc_err* err);
qc_result server_unregister(server_ctx* ctx, char const* username, qc_err* err);
qc_result server_dump_users(server_ctx* ctx, FILE* dst, qc_err* err);
void server_listen(server_ctx* ctx, char const* mqueue_in_name, char const* mqueue_out_name, qc_err* err);
qc_result server_get_key_by_id(server_ctx* ctx, uint8_t const id[static 16], uint8_t dst[static 32], qc_err* err);
