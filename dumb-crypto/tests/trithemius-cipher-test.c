#include <string.h>
#include "qc.h"
#include "crypto.h"

void simple_test() {
    char const* input = "ПРИЛЕТАЮЗАВТРА";
    char* encrypted = trithemius_cipher_encrypt(input, 8, 4, "РАБОТА");
    qc_assert(strcmp(encrypted, "ЩЕУЦНЙЖГСЖКЙЕЖ") == 0, "Trithemius cipher encryption is broken");
    char* decrypted = trithemius_cipher_decrypt(encrypted, 8, 4, "РАБОТА");
    qc_assert(strcmp(decrypted, input) == 0, "Trithemius cipher decryption is broken");
    free(encrypted);
    free(decrypted);
}

void iteration(char const* key) {
    char const* input = "ВЕСЬМАДЛИННОЕПРЕДЛОЖЕНИЕ";
    char* encrypted = trithemius_cipher_encrypt(input, 8, 4, key);
    char* decrypted = trithemius_cipher_decrypt(encrypted, 8, 4, key);
    qc_assert_format(strcmp(input, decrypted) == 0, "Trithemius cipher fails with key %s", key);
    free(encrypted);
    free(decrypted);
}

int main() {
    simple_test();
    iteration("ПРОВЕРКА");
    iteration("НУСЛИШКОМДЛИННЫЙКЛЮЧ");
    iteration("ЭТОСАМАЯГЛУПАЯДОМАШНЯЯРАБОТАВМОЕЙЖИЗНИ");
}
