#include <stdbool.h>
#include <stdint.h>
#include <sqlite3.h>
#include <qc.h>
#include <sodium/crypto_pwhash_argon2id.h>
#include "../database-wrapper.h"

#define HASH_STR_SIZE (crypto_pwhash_argon2id_STRBYTES)
#define STMT_NULL_TERMINATED (-1)

extern char const* schema;

void hash_password(char const *pwd, char hash[static HASH_STR_SIZE]);
bool check_password(char const* pwd, char hash[static HASH_STR_SIZE]);
qc_result get_user(char const* username, sqlite3* db, struct user* user, qc_err* err);
bool validate_username(char const* username, qc_err* err);
