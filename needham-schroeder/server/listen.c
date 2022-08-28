#include <mqueue.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <qc.h>
#include <mq_setup.h>
#include <ciphers.h>
#include "server.h"

typedef struct user_request {
    uint8_t id_a[16];
    uint8_t id_b[16];
    uint8_t nonce[32];
    uint8_t key_a[32];
    uint8_t key_b[32];
    uint8_t cipher[1];
    uint8_t session_key[32];
    uint8_t chacha_nonce_a[12];
    uint8_t chacha_nonce_b[12];
} user_request;

static qc_result parse_message(server_ctx* ctx, const uint8_t msg[static BUFSIZ], user_request* dst, qc_err* err) {
    memmove(dst->id_a, &msg[0], 16);
    memmove(dst->id_b, &msg[16], 16);
    memmove(dst->nonce, &msg[32], 32);
    memmove(dst->cipher, &msg[64], 1);
    if (server_get_key_by_id(ctx, dst->id_a, dst->key_a, err) == QC_FAILURE) {
        qc_err_append_front(err, "Failed to obtain key for user A");
        return QC_FAILURE;
    } else if (server_get_key_by_id(ctx, dst->id_b, dst->key_b, err) == QC_FAILURE) {
        qc_err_append_front(err, "Failed to obtain key for user B");
        return QC_FAILURE;
    } else if (qc_rnd_os_buf(32, dst->session_key, err) == QC_FAILURE) {
        qc_err_append_front(err, "Failed to generate session key");
        return QC_FAILURE;
    } else if (qc_rnd_os_buf(12, dst->chacha_nonce_a, err) == QC_FAILURE) {
        qc_err_append_front(err, "Failed to generate nonce for ChaCha key A");
        return QC_FAILURE;
    } else if (qc_rnd_os_buf(12, dst->chacha_nonce_b, err) == QC_FAILURE) {
        qc_err_append_front(err, "Failed to generate nonce for ChaCha key B");
        return QC_FAILURE;
    } else {
        return QC_SUCCESS;
    }
}

static void xorshift_encrypt_in_place(uint8_t const key[static 32], size_t len, uint8_t buf[static len]) {
    uint8_t* tmp = qc_malloc(len);
    xorshift_encrypt(key, len, buf, tmp);
    memmove(buf, tmp, len);
    free(tmp);
}

static void prepare_reply_chacha(user_request const* request, uint8_t reply[static 152]) {
    memmove(&reply[0], request->chacha_nonce_a, 12);
    memmove(&reply[0+12], request->nonce, 32);
    memmove(&reply[32+12], request->session_key, 32);
    memmove(&reply[64+12], request->id_b, 16);
    memmove(&reply[80+12], request->chacha_nonce_b, 12);
    memmove(&reply[80+12+12], request->session_key, 32);
    memmove(&reply[112+12+12], request->id_a, 16);
    chacha20_encrypt_in_place(request->key_b, 32+16, &reply[80+12], &reply[80+12+12]);
    chacha20_encrypt_in_place(request->key_a, 32+32+16+32+16+12, &reply[0], &reply[12]);
}

static void prepare_reply(user_request const* request, uint8_t reply[static 128]) {
    memmove(&reply[0], request->nonce, 32);
    memmove(&reply[32], request->session_key, 32);
    memmove(&reply[64], request->id_b, 16);
    memmove(&reply[80], request->session_key, 32);
    memmove(&reply[112], request->id_a, 16);
    xorshift_encrypt_in_place(request->key_b, 32+16, &reply[80]);
    xorshift_encrypt_in_place(request->key_a, 32+32+16+32+16, &reply[0]);
}

static void listen_loop(server_ctx* ctx, mqd_t in, mqd_t out, qc_err* err) {
    ssize_t rc;
    char msg[BUFSIZ] = {0};
    for (;;) {
        errno = 0;
        rc = mq_receive(in, msg, BUFSIZ, NULL);
        if (rc == -1) {
            qc_err_set(err, "Failed to obtain message from queue: %s", strerror(errno));
            return;
        } else {
            assert(rc == BUFSIZ);
            user_request p;
            if (parse_message(ctx, (uint8_t*) msg, &p, err) == QC_FAILURE) {
                fprintf(stderr, "Invalid request: %s", qc_err_get(err));
                qc_err_set(err, "");
            } else {
                memset(msg, 0, BUFSIZ);
                if (p.cipher[0] == XORSHIFT_CIPHER) {
                    prepare_reply(&p, (uint8_t*) msg);
                } else {
                    prepare_reply_chacha(&p, (uint8_t*) msg);
                }
                errno = 0;
                if (mq_send(out, msg, BUFSIZ, 0)) {
                    fprintf(stderr, "Failed to send reply: %s", strerror(errno));
                }
            }
        }
    }
}

void server_listen(server_ctx* ctx, char const* mqueue_in_name, char const* mqueue_out_name, qc_err* err) {
    QC_UNUSED(ctx);
    mqd_t in, out;
    if (setup_mq(mqueue_in_name, mqueue_out_name, &in, &out, err) == QC_FAILURE) {
        qc_err_append_front(err, "Failed to setup message queues for IPC");
    } else {
        listen_loop(ctx, in, out, err);
    }
}
