#include <string.h>
#include "qc.h"
#include "crypto.h"

void test3x3() {
    size_t const square[] = {2, 7, 6, 9, 5, 1, 4, 3, 8};
    char const* input = "ШЛА САША ПО ШОССЕ.";
    char* encrypted = magic_square_encrypt(input, 9, square);
    qc_assert(strcmp(encrypted, "ЛША СШ ААОСС.ОПШ Е") == 0, "Magic square cipher encryption is broken");
    char* decrypted = magic_square_decrypt(encrypted, 9, square);
    qc_assert(strcmp(decrypted, input) == 0, "Magic square cipher decryption is broken");
    free(encrypted);
    free(decrypted);
}

void test4x4() {
    size_t const square[] = {16, 3, 2, 13, 5, 10, 11, 8, 9, 6, 7, 12, 4, 15, 14, 1};
    char const* input = "QWERTYUI1234АБВГ";
    char* encrypted = magic_square_encrypt(input, 16, square);
    qc_assert(strcmp(encrypted, "ГEWАT23I1YU4RВБQ") == 0, "Magic square cipher encryption is broken");
    char* decrypted = magic_square_decrypt(encrypted, 16, square);
    qc_assert(strcmp(decrypted, input) == 0, "Magic square cipher decryption is broken");
    free(encrypted);
    free(decrypted);
}

int main() {
    test3x3();
    test4x4();
}
