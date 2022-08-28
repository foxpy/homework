#include <stdbool.h>
#include <string.h>
#include <sodium/crypto_pwhash_argon2id.h>
#include "database-wrapper_impl.h"

bool check_password(char const* pwd, char hash[static HASH_STR_SIZE]) {
    return crypto_pwhash_argon2id_str_verify(hash, pwd, strlen(pwd)) == 0;
}
