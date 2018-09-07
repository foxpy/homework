#include <stdio.h>

int main(int argc, char *argv[]) {
	int bytes = 0;
	int words = 0;
	int sentences = 0;

	char c;
	while (scanf("%c", &c) != EOF) {
		bytes++;
		if (c == ' ') {
			words++;
		}
		if (c == '.') {
			sentences++;
		}
	}

	printf("Bytes: %d.\n", bytes-1);
	printf("Words: %d.\n", words+1);
	printf("Sentences: %d.\n", sentences);

	return 0;
}
