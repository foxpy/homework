#include <qc.h>
#include "database-wrapper_impl/database-wrapper_impl.h"

db_user_type database_check_credentials(db* database, char const* username, char const* password, char** err) {
    struct user user;
    qc_err* qcerr = qc_err_new();
    if (get_user(username, database->db_file, &user, qcerr) == QC_FAILURE) {
        *err = qc_err_to_owned_c_str(qcerr);
        return DATABASE_UNAUTHORIZED;
    } else if (user.username == NULL) {
        *err = sprintf_alloc("This user does not exist");
        return DATABASE_UNAUTHORIZED;
    } else if (!check_password(password, user.password_hash)) {
        *err = sprintf_alloc("Wrong password");
        return DATABASE_UNAUTHORIZED;
    } else {
        db_user_type ret;
        if (user.is_admin) {
            ret = DATABASE_ADMIN;
        } else {
            ret = DATABASE_USER;
        }
        qc_err_free(qcerr);
        return ret;
    }
}
