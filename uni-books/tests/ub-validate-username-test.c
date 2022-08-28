#include <stdlib.h>
#include <string.h>
#include <qc.h>
#include "database-wrapper_impl/database-wrapper_impl.h"

static void check_valid(char const* username, qc_err* err) {
    qc_assert_format(validate_username(username, err) == true,
                     "Username \"%s\" erroneously considered as invalid", username);
}

static void check_invalid(char const* username, qc_err* err) {
    qc_assert_format(validate_username(username, err) == false,
                     "Username \"%s\" erroneously considered as valid", username);
}

int main() {
    qc_err* err = qc_err_new();
    check_valid("hunter2", err);
    check_valid("xxX_proGamer_Xxx", err);
    check_invalid("';DROP TABLE students;", err);
    check_invalid("русскей никнейм", err);
    qc_err_free(err);
}
