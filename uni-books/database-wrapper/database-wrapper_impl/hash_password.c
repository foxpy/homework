#include <string.h>
#include <assert.h>
#include <qc.h>
#include <sodium/crypto_pwhash_argon2id.h>
#include "database-wrapper_impl.h"

#define ITERATIONS 2
#define USED_MEMORY 256 * 1024

void hash_password(char const *pwd, char hash[static HASH_STR_SIZE]) {
    int rc = crypto_pwhash_argon2id_str(hash, pwd, strlen(pwd), ITERATIONS, USED_MEMORY);
#   ifdef NDEBUG
        UNUSED(rc);
#   endif
    assert(rc == 0);
}
