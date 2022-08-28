#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <sqlite3.h>

typedef enum {
    DATABASE_USER,
    DATABASE_ADMIN,
    DATABASE_UNAUTHORIZED,
} db_user_type;

typedef struct database {
    sqlite3* db_file;
} db;

typedef struct user {
    bool is_admin;
    char* username;
    char* password_hash;
} user;

typedef struct book {
    char* isbn;
    char* name;
    char* author;
    char* catalog;
} book;

bool database_new(char const* path, char** err, char const* admin_password);
db* database_open(char const* path, char** err);
void database_close(db* database);

bool database_register(db* database, char const* username, char const* password, bool is_admin, char** err);
db_user_type database_check_credentials(db* database, char const* username, char const* password, char** err);
ptrdiff_t database_get_users(db* database, struct user** dst, char** err);
bool database_delete_user(db* database, char const* username, char** err);
ptrdiff_t database_get_books(db* database, bool deleted_books, struct book** dst, char** err);
bool database_delete_book(db* database, char const* bookname, char** err);
bool database_restore_book(db* database, char const* bookname, char** err);
bool database_add_book(db* database, char const* isbn, char const* bookname,
                       char const* author, char const* catalog, char** err);
