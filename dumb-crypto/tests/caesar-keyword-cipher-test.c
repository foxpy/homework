#include <string.h>
#include "qc.h"
#include "crypto.h"

void simple_test() {
    char const* input = "РАЗУМАЛИШАЕТНЕСОМНЕНИЕАУВЕРЕННОСТЬ";
    char* encrypted = caesar_keyword_cipher_encrypt(input, 5, "ВЕСНА");
    char* decrypted = caesar_keyword_cipher_decrypt(encrypted, 5, "ВЕСНА");
    qc_assert(strcmp(encrypted, "ЙЫНМЁЫДАУЫВЛЖВКЗЁЖВЖАВЫМЭВЙВЖЖЗКЛЧ") == 0, "Caesar keyword cipher encryption is broken");
    qc_assert(strcmp(decrypted, input) == 0, "Caesar keyword cipher decryption is broken");
    free(encrypted);
}

void iteration(size_t k, char const* key) {
    char const* input = "ПРОВЕРОЧНАЯСТРОКА";
    char* encrypted = caesar_keyword_cipher_encrypt(input, k, key);
    char* decrypted = caesar_keyword_cipher_decrypt(encrypted, k, key);
    qc_assert(strcmp(input, decrypted) == 0, "Caesar keyword cipher is unreliable");
    free(encrypted);
    free(decrypted);
}

void iteration_over_key(char const* key) {
    for (size_t i = 0; i < 32; ++i) {
        iteration(i, key);
    }
}

int main() {
    simple_test();
    iteration_over_key("ОСЕНЬ");
    iteration_over_key("КЛЮЧ");
    iteration_over_key("КЛЮЮЮЧ");
    iteration_over_key("КЛЮЧКЛЮЧКЛЮЧКЛЮЧ");
    iteration_over_key("КЛЮЧКЛЮЧКЛЮЧКЛЮЧЁ");
}
