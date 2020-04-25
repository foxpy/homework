#pragma once
#define RW_RW_RW_ 0666
typedef struct message {
	long mtype;
	char mtext[64];
} msg_t;
