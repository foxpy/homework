#include <stdio.h>
#include <time.h>

void slowmemcpy(char* from, char* to, int size) {
	char *src = from;
	char *dst = to;
	if (from + size > to) {
		for (int i = size; i > 0; i--) {
			dst[i] = src[i];
		}
	} else {
		for (int i = 0; i < size; i++) {
			dst[i] = src[i];
		}
	}
}

int main(int argc, char *argv[]) {
	char str[10000] = "123456789";
	printf("It was %s at the beginning.\n", str);

	clock_t start_time = clock();
	slowmemcpy(str+5, str+2, 2);
	double elapsed_time = (clock() - start_time);

	printf("Now it is %s.\n", str);
	printf("Copying took %.0f microseconds.\n",
			elapsed_time / CLOCKS_PER_SEC*1000000);
	return 0;
}
