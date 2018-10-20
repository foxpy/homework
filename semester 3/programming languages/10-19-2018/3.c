#include <stdio.h>
#include <string.h>
#include <time.h>

long find_substr(char *str, char *substr){
	for (int i = 0; str[i] != '\0'; i++) {
		if (substr[0] == str[i]) {
			long len = strlen(substr);
			long count = 1;
			for (long j = 1; j <= len; j++) {
				if (substr[j] == str[i+j]) {
					count++;
				}
				else{
					break;
				}
				if (count == len) {
					return i;
				}
			}
		}
	}
	return -1;
}

int main(int argc, char *argv[]) {
	char str[] = "qwertyuiop";
	char substr[] ="tyui";

	clock_t start_time = clock();
	long start_sub = find_substr(str, substr);
	double elapsed_time = (clock() - start_time);

	if (start_sub == -1) {
		puts("Substring is not in string!");
		return 1;
	}

	printf("Index = %ld.\n", start_sub);
	printf("Time: %.0f microseconds.\n",
			elapsed_time / CLOCKS_PER_SEC*1000000);
	return 0;
}
