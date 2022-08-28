#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <qc.h>
#include "database-wrapper_impl.h"

bool validate_username(char const* username, qc_err* err) {
    for (size_t i = 0, end = strlen(username); i < end; ++i) {
        char c = username[i];
        if (c != '_' && !isalnum(c)) {
            qc_err_set(err, "Indalid character: \"%c\"", c);
            return false;
        }
    }
    return true;
}
