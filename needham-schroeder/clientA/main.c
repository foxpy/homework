#include <mqueue.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <qc.h>
#include <mq_setup.h>
#include <ciphers.h>

static struct parameters {
    mqd_t in;
    mqd_t out;
    uint8_t my_id[16];
    uint8_t target_id[16];
    uint8_t nonce[32];
    uint8_t cipher[1];
    uint8_t my_key[32];
    uint8_t session_key[32];
    uint8_t payload_for_target[48];
    uint8_t payload_for_target_chacha[60];
} param;

static qc_result parse_hex(char const* str, size_t len, uint8_t dst[static len], qc_err* err) {
    uint8_t* parsed;
    ptrdiff_t l;
    if ((l = qc_hexstr_to_bytes(str, &parsed)) == -1) {
        qc_err_set(err, "Supplied string is not a hexadecimal number");
        return QC_FAILURE;
    } else if (l != (ptrdiff_t) len) {
        free(parsed);
        qc_err_set(err, "Supplied hexadecimal number should represent %zu-bit number", len*8);
        return QC_FAILURE;
    } else {
        memmove(dst, parsed, len);
        free(parsed);
        return QC_SUCCESS;
    }
}

static void prepare_message(uint8_t buf[static BUFSIZ]) {
    memmove(&buf[0], param.my_id, 16);
    memmove(&buf[16], param.target_id, 16);
    memmove(&buf[32], param.nonce, 32);
    memmove(&buf[64], param.cipher, 1);
}

static void xorshift_decrypt_msg_in_place(uint8_t const key[static 32], size_t len, uint8_t buf[static len]) {
    uint8_t* tmp = qc_malloc(len);
    xorshift_decrypt(key, len, buf, tmp);
    memmove(buf, tmp, len);
    free(tmp);
}

static void xorshift_encrypt_msg_in_place(uint8_t const key[static 32], size_t len, uint8_t buf[static len]) {
    uint8_t* tmp = qc_malloc(len);
    xorshift_encrypt(key, len, buf, tmp);
    memmove(buf, tmp, len);
    free(tmp);
}

static void parse_server_reply(uint8_t msg[static 128]) {
    xorshift_decrypt_msg_in_place(param.my_key, 128, msg);
    if (memcmp(&msg[0], param.nonce, 32) == 0 && memcmp(&msg[64], param.target_id, 16) == 0) {
        memmove(param.session_key, &msg[32], 32);
        memmove(param.payload_for_target, &msg[80], 48);
    } else {
        fprintf(stderr, "Server is imposter");
        abort();
    }
}

static void parse_server_reply_chacha(uint8_t msg[static 152]) {
    chacha20_decrypt_in_place(param.my_key, 140, &msg[0], &msg[12]);
    if (memcmp(&msg[12], param.nonce, 32) == 0 && memcmp(&msg[64+12], param.target_id, 16) == 0) {
        memmove(param.session_key, &msg[32+12], 32);
        memmove(param.payload_for_target_chacha, &msg[80+12], 60);
    } else {
        fprintf(stderr, "Server is imposter");
        abort();
    }
}

static qc_result send_request_to_b(qc_err* err) {
    char msg[BUFSIZ] = {0};
    memmove(&msg[0], param.cipher, 1);
    if (param.cipher[0] == XORSHIFT_CIPHER) {
        memmove(&msg[1], param.payload_for_target, 48);
    } else {
        memmove(&msg[1], param.payload_for_target_chacha, 60);
    }
    errno = 0;
    if (mq_send(param.out, msg, BUFSIZ, 0) == -1) {
        qc_err_set(err, "Failed to send message to client B: %s", strerror(errno));
        return QC_FAILURE;
    } else {
        return QC_SUCCESS;
    }
}

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

qc_result handle_reply_from_b(qc_err* err) {
    char msg[BUFSIZ] = {0};
    errno = 0;
    if (mq_receive(param.in, msg, BUFSIZ, 0) != BUFSIZ) {
        qc_err_set(err, "Failed to acquire reply from client B: %s", strerror(errno));
        return QC_FAILURE;
    } else {
        uint8_t nonce_b[32];
        if (param.cipher[0] == XORSHIFT_CIPHER) {
            xorshift_decrypt_msg_in_place(param.session_key, 32, (uint8_t*) msg);
            memmove(nonce_b, &msg[0], 32);
        } else {
            chacha20_decrypt_in_place(param.session_key, 32, (uint8_t*) &msg[0], (uint8_t*) &msg[12]);
            memmove(nonce_b, &msg[12], 32);
        }
        increment_nonce(nonce_b);
        if (param.cipher[0] == XORSHIFT_CIPHER) {
            memmove(msg, nonce_b, 32);
            xorshift_encrypt_msg_in_place(param.session_key, 32, (uint8_t*) msg);
        } else {
            uint8_t chacha_nonce[12];
            if (qc_rnd_os_buf(12, chacha_nonce, err) == QC_FAILURE) {
                qc_err_append_front(err, "Failed to generate ChaCha nonce for reply to client B");
                return QC_FAILURE;
            }
            memmove(&msg[0], chacha_nonce, 12);
            memmove(&msg[12], nonce_b, 32);
            chacha20_encrypt_in_place(param.session_key, 32, (uint8_t*) &msg[0], (uint8_t*) &msg[12]);
        }
        errno = 0;
        if (mq_send(param.out, msg, BUFSIZ, 0) == -1) {
            qc_err_set(err, "Failed to send reply to client B: %s", strerror(errno));
            return QC_FAILURE;
        } else {
            char* session_key;
            qc_bytes_to_hexstr(false, 32, param.session_key, &session_key);
            printf("A: Successfully exchanged session key with client B: %s\n", session_key);
            free(session_key);
            return QC_SUCCESS;
        }
    }
}

int main(int argc, char* argv[]) {
    qc_err* err = qc_err_new();
    qc_args* args = qc_args_new();
    char const* mqueue_server_in_path;
    char const* mqueue_server_out_path;
    char const* mqueue_client_in_path;
    char const* mqueue_client_out_path;
    char const* my_id;
    char const* target_id;
    char const* my_key;
    bool use_chacha;
    qc_args_string(args, "mqueue-server-in", &mqueue_server_in_path,
                   "Name of input message queue for communication with server");
    qc_args_string(args, "mqueue-server-out", &mqueue_server_out_path,
                   "Name of output message queue for communication with server");
    qc_args_string(args, "mqueue-client-in", &mqueue_client_in_path,
                   "Name of input message queue for communication with client B");
    qc_args_string(args, "mqueue-client-out", &mqueue_client_out_path,
                   "Name of output message queue for communication with client B");
    qc_args_string(args, "id", &my_id, "My user ID");
    qc_args_string(args, "target-id", &target_id, "Target user ID");
    qc_args_string(args, "my-key", &my_key, "My secret key");
    qc_args_flag(args, 'c', "use-chacha", &use_chacha, "Use ChaCha20 cipher instead of inferior xorshift");
    if (qc_args_parse(args, argc, argv, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to parse CLI arguments");
    }
    param.cipher[0] = use_chacha ? CHACHA20_CIPHER : XORSHIFT_CIPHER;
    if (connect_mq(mqueue_server_in_path, mqueue_server_out_path, &param.in, &param.out, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to open message queue");
    } else if (parse_hex(my_id, 16, param.my_id, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to parse My ID");
    } else if (parse_hex(target_id, 16, param.target_id, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to parse Target ID");
    } else if (parse_hex(my_key, 32, param.my_key, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to parse My key");
    } else if (qc_rnd_os_buf(32, param.nonce, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to obtain nonce from OS entropy pool");
    } else {
        char msg[BUFSIZ] = {0};
        prepare_message((uint8_t*) msg);
        errno = 0;
        ssize_t rc;
        if (mq_send(param.out, msg, BUFSIZ, 0) == -1) {
            qc_err_fatal(err, "Failed to send message: %s", strerror(errno));
        } else if ((rc = mq_receive(param.in, msg, BUFSIZ, 0)) == -1) {
            qc_err_fatal(err, "Failed to receive answer: %s", strerror(errno));
        } else {
            assert(rc == BUFSIZ);
            if (!use_chacha) {
                parse_server_reply((uint8_t*) msg);
            } else {
                parse_server_reply_chacha((uint8_t*) msg);
            }
            mq_close(param.in);
            mq_close(param.out);
        }
    }
    if (connect_mq(mqueue_client_in_path, mqueue_client_out_path, &param.in, &param.out, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to connect to client B message queues");
    } else if (send_request_to_b(err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to send request to client B");
    } else if (handle_reply_from_b(err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to send reply to client B");
    }
    mq_close(param.in);
    mq_close(param.out);
    qc_args_free(args);
    qc_err_free(err);
}
