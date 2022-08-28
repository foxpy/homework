#include <stdlib.h>
#include <sqlite3.h>
#include "database-wrapper.h"

void database_close(db* database) {
    sqlite3_close(database->db_file);
    free(database);
}
