#include "database-wrapper_impl/database-wrapper_impl.h"

bool database_add_book(db* database, char const* isbn, char const* bookname,
                       char const* author, char const* catalog, char** err) {
    UNUSED(err);
    char const* query = "INSERT INTO Books(name, exists_flag, author, isbn, catalog) VALUES(?1, TRUE, ?2, ?3, ?4);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(database->db_file, query, STMT_NULL_TERMINATED, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, bookname, STMT_NULL_TERMINATED, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, author, STMT_NULL_TERMINATED, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, isbn, STMT_NULL_TERMINATED, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, catalog, STMT_NULL_TERMINATED, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return true;
}
