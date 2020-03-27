#include <stdio.h>
#include <stdlib.h>
#include "receiver.h"

void receiver(FILE *file, FILE *fifo) {
	char buf[BUFSIZ];
	size_t read_cnt, write_cnt;

	do {
		if ((read_cnt = fread(buf, sizeof(char), BUFSIZ, fifo)) != 0)
			write_cnt = fwrite(buf, sizeof(char), read_cnt, file);
		else write_cnt = 0;
	} while (write_cnt != 0);
}
