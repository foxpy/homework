#include <stdio.h>
#include "help.h"

void help(const char *program_name) {
	fprintf(stderr, "Usage: %s PATH PROJECT\n", program_name);
	fputs("\tPATH: path to any file relevant to program (consult ftok(3) for more info)\n", stderr);
	fputs("\tPROJECT: single ASCII alphabetic character, use any of [A-Z][a-z]\n", stderr);
}
