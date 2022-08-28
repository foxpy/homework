#include <qc.h>
#include <stdint.h>
#include "chacha20.h"

qc_result chacha20_gen_nonce(uint8_t dst[static 12], qc_err* err) {
    if (qc_rnd_os_buf(12, dst, err) == QC_FAILURE) {
        qc_err_append_front(err, "Failed to generate ChaCha20 key");
        return QC_FAILURE;
    } else {
        return QC_SUCCESS;
    }
}
