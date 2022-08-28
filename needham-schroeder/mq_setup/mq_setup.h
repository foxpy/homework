#pragma once
#include <mqueue.h>
#include <qc.h>

qc_result setup_mq(char const* qin, char const* qout, mqd_t* qin_dst, mqd_t* qout_dst, qc_err* err);
qc_result connect_mq(char const* qin, char const* qout, mqd_t* qin_dst, mqd_t* qout_dst, qc_err* err);
