#include <sqlite3.h>
#include <qc.h>
#include "database-wrapper.h"

db* database_open(char const* path, char** err) {
    db* ret = emalloc(sizeof(db));
    if (sqlite3_open(path, &ret->db_file) != 0) {
        *err = sprintf_alloc("Can't open database: %s", sqlite3_errmsg(ret->db_file));
        sqlite3_close(ret->db_file);
        return NULL;
    }
    return ret;
}
