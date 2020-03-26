#include <stdio.h>
#include <stdlib.h>
#include "sender.h"

void sender(FILE *file, FILE *fifo) {
	char buf[BUFSIZ];
	size_t read_cnt, write_cnt;

	do {
		if ((read_cnt = fread(buf, sizeof(char), BUFSIZ, file)) != 0)
			write_cnt = fwrite(buf, sizeof(char), read_cnt, fifo);
		else write_cnt = 0;
	} while(write_cnt != 0);
}
