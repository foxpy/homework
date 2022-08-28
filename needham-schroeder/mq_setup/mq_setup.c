#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <mqueue.h>
#include <qc.h>
#include "mq_setup.h"

static char* qin_path = NULL;
static char* qout_path = NULL;
static mqd_t qin_queue = -1;
static mqd_t qout_queue = -1;

static void cleanup_input() {
    if (qin_queue != -1) {
        mq_close(qin_queue);
    }
    if (qin_path != NULL) {
        mq_unlink(qin_path);
    }
}

static void cleanup_output() {
    if (qout_queue != -1) {
        mq_close(qout_queue);
    }
    if (qout_path != NULL) {
        mq_unlink(qout_path);
    }
}

static qc_noreturn void sig_handler(int signo) {
    QC_UNUSED(signo);
    cleanup_input();
    cleanup_output();
    exit(0);
}

static qc_result setup_in(char const* qin, mqd_t* qin_dst, bool create, qc_err* err) {
    qc_asprintf(&qin_path, "/%s", qin);
    errno = 0;
    mqd_t q;
    int oflag = create ? (O_RDONLY | O_CREAT) : O_RDONLY;
    if ((q = mq_open(qin_path, oflag, 0700, NULL)) == -1) {
        qc_err_set(err, "Failed to setup input mqueue \"%s\": %s", qin_path, strerror(errno));
        free(qin_path);
        return QC_FAILURE;
    } else {
        *qin_dst = q;
        if (create) {
            qin_queue = q;
        }
        return QC_SUCCESS;
    }
}

static qc_result setup_out(char const* qout, mqd_t* qout_dst, bool create, qc_err* err) {
    qc_asprintf(&qout_path, "/%s", qout);
    errno = 0;
    mqd_t q;
    int oflag = create ? (O_WRONLY | O_CREAT) : O_WRONLY;
    if ((q = mq_open(qout_path, oflag, 0700, NULL)) == -1) {
        qc_err_set(err, "Failed to setup output mqueue \"%s\": %s", qout_path, strerror(errno));
        free(qout_path);
        return QC_FAILURE;
    } else {
        *qout_dst = q;
        if (create) {
            qout_queue = q;
        }
        return QC_SUCCESS;
    }
}

qc_result setup_mq(char const* qin, char const* qout, mqd_t* qin_dst, mqd_t* qout_dst, qc_err* err) {
    if (setup_in(qin, qin_dst, true, err) == QC_FAILURE) {
        return QC_FAILURE;
    } else if (setup_out(qout, qout_dst, true, err) == QC_FAILURE) {
        cleanup_input();
        return QC_FAILURE;
    } else {
        int signums[] = { SIGINT, SIGTERM, SIGABRT, SIGQUIT, SIGFPE };
        for (size_t i = 0; i < sizeof(signums)/sizeof(*signums); ++i) {
            signal(signums[i], sig_handler);
        }
        return QC_SUCCESS;
    }
}

qc_result connect_mq(char const* qin, char const* qout, mqd_t* qin_dst, mqd_t* qout_dst, qc_err* err) {
    if (setup_in(qin, qin_dst, false, err) == QC_FAILURE) {
        return QC_FAILURE;
    } else if (setup_out(qout, qout_dst, false, err) == QC_FAILURE) {
        mq_close(*qin_dst);
        return QC_FAILURE;
    } else {
        return QC_SUCCESS;
    }
}
