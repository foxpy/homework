#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <qc.h>
#include <mq_setup.h>
#include <ciphers.h>

struct {
    mqd_t in;
    mqd_t out;
    uint8_t my_key[32];
    uint8_t session_key[32];
    uint8_t id_b[16];
    uint8_t nonce[32];
    uint8_t cipher[1];
} param;

static void increment_nonce(uint8_t nonce[static 32]) {
    uint8_t carry = 1;
    for (size_t i = 0; i < 32; ++i) {
        if (carry) {
            if ((nonce[i] += carry) != 0) {
                carry = 0;
            }
        } else {
            break;
        }
    }
}

static qc_result parse_hex(char const* str, uint8_t dst[static 32], qc_err* err) {
    uint8_t* parsed;
    ptrdiff_t l;
    if ((l = qc_hexstr_to_bytes(str, &parsed)) == -1) {
        qc_err_set(err, "Supplied string is not a hexadecimal number");
        return QC_FAILURE;
    } else if (l != (ptrdiff_t) 32) {
        free(parsed);
        qc_err_set(err, "Supplied hexadecimal number should represent %zu-bit number", 32*8);
        return QC_FAILURE;
    } else {
        memmove(dst, parsed, 32);
        free(parsed);
        return QC_SUCCESS;
    }
}

static void xorshift_decrypt_in_place(uint8_t const key[static 32], size_t len, uint8_t buf[static len]) {
    uint8_t* tmp = qc_malloc(len);
    xorshift_decrypt(key, len, buf, tmp);
    memmove(buf, tmp, len);
    free(tmp);
}

static void xorshift_encrypt_in_place(uint8_t const key[static 32], size_t len, uint8_t buf[static len]) {
    uint8_t* tmp = qc_malloc(len);
    xorshift_encrypt(key, len, buf, tmp);
    memmove(buf, tmp, len);
    free(tmp);
}

static qc_result send_reply(qc_err* err) {
    if (qc_rnd_os_buf(32, param.nonce, err) == QC_FAILURE) {
        qc_err_append_front(err, "Failed to generate nonce for client A");
        return QC_FAILURE;
    } else {
        char msg[BUFSIZ];
        if (param.cipher[0] == XORSHIFT_CIPHER) {
            memmove(&msg[0], param.nonce, 32);
            xorshift_encrypt_in_place(param.session_key, 32, (uint8_t*) msg);
        } else {
            uint8_t chacha_nonce[12];
            if (qc_rnd_os_buf(12, chacha_nonce, err) == QC_FAILURE) {
                qc_err_append_front(err, "Failed to generate ChaCha nonce for reply to A");
                return QC_FAILURE;
            }
            memmove(&msg[0], chacha_nonce, 12);
            memmove(&msg[12], param.nonce, 32);
            chacha20_encrypt_in_place(param.session_key, 32, (uint8_t*) &msg[0], (uint8_t*) &msg[12]);
        }
        errno = 0;
        if (mq_send(param.out, msg, BUFSIZ, 0) == -1) {
            qc_err_set(err, "Failed to send reply to client A: %s", strerror(errno));
            return QC_FAILURE;
        } else {
            return QC_SUCCESS;
        }
    }
}

static qc_result handle_reply(qc_err* err) {
    char msg[BUFSIZ];
    errno = 0;
    if (mq_receive(param.in, msg, BUFSIZ, 0) != BUFSIZ) {
        qc_err_set(err, "Failed to accept client A reply: %s", strerror(errno));
        return QC_FAILURE;
    } else {
        uint8_t received_nonce[32];
        if (param.cipher[0] == XORSHIFT_CIPHER) {
            xorshift_decrypt_in_place(param.session_key, 32, (uint8_t*) msg);
            memmove(received_nonce, &msg[0], 32);
        } else {
            chacha20_decrypt_in_place(param.session_key, 32, (uint8_t*) &msg[0], (uint8_t*) &msg[12]);
            memmove(received_nonce, &msg[12], 32);
        }
        increment_nonce(param.nonce);
        if (memcmp(param.nonce, received_nonce, 32) == 0) {
            char* key;
            qc_bytes_to_hexstr(false, 32, param.session_key, &key);
            printf("B: Successfully exchanged session key with client A: %s\n", key);
            free(key);
            return QC_SUCCESS;
        } else {
            qc_err_set(err, "Client A is imposter");
            return QC_FAILURE;
        }
    }
}

static qc_result handle_request(qc_err* err) {
    char msg[BUFSIZ];
    errno = 0;
    if (mq_receive(param.in, msg, BUFSIZ, 0) != BUFSIZ) {
        qc_err_set(err, "Failed to accept client A request: %s", strerror(errno));
        return QC_FAILURE;
    } else {
        memmove(param.cipher, &msg[0], 1);
        if (param.cipher[0] == XORSHIFT_CIPHER) {
            xorshift_decrypt_in_place(param.my_key, 48, (uint8_t*) &msg[1]);
            memmove(param.session_key, &msg[1], 32);
            memmove(param.id_b, &msg[33], 16);
        } else {
            chacha20_decrypt_in_place(param.my_key, 48, (uint8_t*) &msg[1], (uint8_t*) &msg[1+12]);
            memmove(param.session_key, &msg[1+12], 32);
            memmove(param.id_b, &msg[33+12], 16);
        }
        char* id_str;
        qc_bytes_to_hexstr(false, 16, param.id_b, &id_str);
        printf("B: Received session key from suspicious user %s\n", id_str);
        free(id_str);
        return send_reply(err);
    }
}

int main(int argc, char* argv[]) {
    qc_err* err = qc_err_new();
    qc_args* args = qc_args_new();
    char const* qin;
    char const* qout;
    char const* my_key;
    qc_args_string(args, "my-key", &my_key, "My secret key");
    qc_args_string(args, "mqueue-in", &qin, "Input queue for communication with client A");
    qc_args_string(args, "mqueue-out", &qout, "Output queue for communication with client A");
    if (qc_args_parse(args, argc, argv, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to parse CLI arguments");
    } else if (parse_hex(my_key, param.my_key, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to parse My key");
    } else if (setup_mq(qin, qout, &param.in, &param.out, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to prepare message queues for communication with client A");
    } else if (handle_request(err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to handle client A request");
    } else if (handle_reply(err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to handle reply from client A");
    }
    qc_args_free(args);
    qc_err_free(err);
    abort();
}
