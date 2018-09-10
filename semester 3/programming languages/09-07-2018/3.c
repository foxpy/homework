#include <stdio.h>

#define TRUE	1
#define FALSE	0

char is_letter(char c) {
	if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))) {
		return TRUE;
	}
	return FALSE;
}

int main(int argc, char *argv[]) {
	int bytes = 0;
	int words = 0;
	int lines = 0;

	char c;
	while (scanf("%c", &c) != EOF) {
		bytes++;
		if (c == ' ') {
			words++;
		}
		if (c == '\n') {
			lines++;
		}
	}

	printf("Bytes: %d.\n", bytes-1);
	printf("Words: %d.\n", words+1);
	printf("Lines: %d.\n", lines);

	return 0;
}
