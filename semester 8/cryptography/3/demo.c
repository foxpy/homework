#include "gost.h"

static size_t round_size(size_t x, size_t m) {
	if (m == 0) return x;
	size_t r = x % m;
	if (r == 0) return x;
	return x + m - r;
}

static void print_data(char const* header, uint8_t* buf, size_t len) {
	printf("%s: 0x", header);
	for (size_t i = 0; i < len; ++i) {
		printf("%02" PRIx8, buf[i]);
	}
	printf("\n");
}

static size_t get_input(uint32_t** dst, int argc, char** argv) {
	if (argc != 2) {
		die("Invalid usage");
	} else {
		printf("Input string: %s\n", argv[1]);
		size_t len = round_size(strlen(argv[1]) + 1, 8);
		*dst = malloc(len);
		memset(*dst, 0, len);
		strcpy((char*) *dst, argv[1]);
		return len / 8;
	}
}

int main(int argc, char* argv[]) {
	uint32_t* data;
	size_t len = get_input(&data, argc, argv);
	uint32_t key[8];
	gost g;
	gost_init(&g);
	gost_key(&g, key);
	print_key(key);

	print_data("Input data", (uint8_t*) data, len * 8);
	gost_encrypt(&g, data, len);
	print_data("Ciphertext", (uint8_t*) data, len * 8);
	gost_decrypt(&g, data, len);
	print_data("Plaintext", (uint8_t*) data, len * 8);
	printf("Output data: %s\n", (char*) data);

	return EXIT_SUCCESS;
}
