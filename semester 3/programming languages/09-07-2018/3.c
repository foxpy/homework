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
	char in_word = FALSE;
	while (scanf("%c", &c) != EOF) {
		bytes++;

		if ((is_letter(c)) && !(in_word)) {
			in_word = TRUE;
			words++;
		} else if (!(is_letter(c))) {
			in_word = FALSE;
		}

		if (c == '\n') {
			lines++;
		}
	}

	printf("Bytes: %d.\n", bytes-1);
	printf("Words: %d.\n", words);
	printf("Lines: %d.\n", lines);

	return 0;
}
