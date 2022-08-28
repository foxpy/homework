#include <stddef.h>
#include <sodium/crypto_pwhash_argon2id.h>
#include <qc.h>
#include "database-wrapper_impl/database-wrapper_impl.h"

static char const* passwords[] = {
        "p@55w01d",
        "qwerty12345",
        "hunter2",
        "bash.org+244321"
};
#define PASSWORDS_SIZE (sizeof(passwords)/sizeof(passwords[0]))

int main() {
    char hash[HASH_STR_SIZE];
    for (size_t i = 0; i < PASSWORDS_SIZE; ++i) {
        for (size_t j = 0; j < PASSWORDS_SIZE; ++j) {
            hash_password(passwords[i], hash);
            if (i == j) {
                qc_assert(check_password(passwords[j], hash),
                          "Hash is expected to match");
            } else {
                qc_assert(!check_password(passwords[j], hash),
                          "Hash is not expected to match");
            }
        }
    }
}
