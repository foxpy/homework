#include <string.h>
#include "crypto.h"
#include "qc.h"

void test2x2() {
    char* input = "АБВГДЕЁЖЗИЙК";
    char* encrypted = encryption_table_encrypt(input, 2, 2);
    qc_assert(strcmp(encrypted, "АВБГДЁЕЖЗЙИК") == 0, "Encryption table cipher encryption is broken");
    char* decrypted = encryption_table_decrypt(encrypted, 2, 2);
    qc_assert(strcmp(input, decrypted) == 0, "Encryption table cipher decryption is broken");
    free(encrypted);
    free(decrypted);
}

void test3x3() {
    char* input = "QWАБВГERT";
    char* encrypted = encryption_table_encrypt(input, 3, 3);
    qc_assert(strcmp(encrypted, "QБЕWБRАГT"), "Encryption table cipher encryption is broken");
    char* decrypted = encryption_table_decrypt(encrypted, 3, 3);
    qc_assert(strcmp(input, decrypted) == 0, "Encryption table cipher decryption is broken");
    free(encrypted);
    free(decrypted);
}

void iteration(size_t x, size_t y) {
    char* input = "ОЧЕНЬ ДЛИННОЕ СООБЩЕНИЕ, ДОСТАТОЧНО ДЛИННОЕ, ЧТОБЫ НЕ ВЛЕЗТЬ ВО МНОГИЕ МАТРИЦЫ";
    char* encrypted = encryption_table_encrypt(input, x, y);
    char* decrypted = encryption_table_decrypt(encrypted, x, y);
    qc_assert(strncmp(input, decrypted, x*y) == 0, "Encryption table cipher is unreliable");
    free(encrypted);
    free(decrypted);
}

int main() {
    test2x2();
    test3x3();
    for (size_t i = 1; i < 5; ++i) {
        for (size_t j = 1; j < 5; ++j) {
            iteration(i, j);
        }
    }
}
