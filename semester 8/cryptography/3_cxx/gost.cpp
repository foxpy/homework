#include <cstdint>
#include <random>
#include <iostream>
#include <iomanip>

std::uint32_t rotl32(std::uint32_t x, std::size_t n) {
	return x << n | x >> (32 - n);
}

struct Gost {
	Gost() {
		std::uint8_t k8[16] = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7};
		std::uint8_t k7[16] = {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10};
		std::uint8_t k6[16] = {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8};
		std::uint8_t k5[16] = {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15};
		std::uint8_t k4[16] = {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9};
		std::uint8_t k3[16] = {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11};
		std::uint8_t k2[16] = {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1};
		std::uint8_t k1[16] = {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7};
		for (std::size_t i = 0; i < 256; ++i) {
			k87[i] = k8[i >> 4] << 4 | k7[i & 15];
			k65[i] = k6[i >> 4] << 4 | k5[i & 15];
			k43[i] = k4[i >> 4] << 4 | k3[i & 15];
			k21[i] = k2[i >> 4] << 4 | k1[i & 15];
		}
		std::random_device rd;
		std::uniform_int_distribution<std::uint32_t> dist(0, UINT32_MAX);
		for (std::size_t i = 0; i < 8; ++i) {
			key[0] = dist(rd);
		}
	}
	void show_key() {
		std::cout << "Key: 0x";
		for (auto i : key)
			std::cout << std::hex << i;
		std::cout << std::endl;
	}
	std::uint32_t f(std::uint32_t x) {
		x = k87[x>>24 & 255] << 24
		  | k65[x>>16 & 255] << 16
		  | k43[x>>16 & 255] << 8
		  | k21[x & 255];
		return rotl32(x, 11);
	}
	void encrypt(std::uint32_t d[2]) {
		std::uint32_t n1 = d[0], n2 = d[1];
		for (std::size_t i = 0; i < 3; ++i) {
			n2 ^= f(n1 + key[0]); n1 ^= f(n2 + key[1]);
			n2 ^= f(n1 + key[2]); n1 ^= f(n2 + key[3]);
			n2 ^= f(n1 + key[4]); n1 ^= f(n2 + key[5]);
			n2 ^= f(n1 + key[6]); n1 ^= f(n2 + key[7]);
		}
		n2 ^= f(n1 + key[7]); n1 ^= f(n2 + key[6]);
		n2 ^= f(n1 + key[5]); n1 ^= f(n2 + key[4]);
		n2 ^= f(n1 + key[3]); n1 ^= f(n2 + key[2]);
		n2 ^= f(n1 + key[1]); n1 ^= f(n2 + key[0]);
		d[0] = n2; d[1] = n1;
	}
	void decrypt(std::uint32_t d[2]) {
		std::uint32_t n1 = d[0], n2 = d[1];
		n2 ^= f(n1 + key[0]); n1 ^= f(n2 + key[1]);
		n2 ^= f(n1 + key[2]); n1 ^= f(n2 + key[3]);
		n2 ^= f(n1 + key[4]); n1 ^= f(n2 + key[5]);
		n2 ^= f(n1 + key[6]); n1 ^= f(n2 + key[7]);
		for (std::size_t i = 0; i < 3; ++i) {
			n2 ^= f(n1 + key[7]); n1 ^= f(n2 + key[6]);
			n2 ^= f(n1 + key[5]); n1 ^= f(n2 + key[4]);
			n2 ^= f(n1 + key[3]); n1 ^= f(n2 + key[2]);
			n2 ^= f(n1 + key[1]); n1 ^= f(n2 + key[0]);
		}
		d[0] = n2; d[1] = n1;
	}
	std::uint32_t key[8];
	char k87[256];
	char k65[256];
	char k43[256];
	char k21[256];
};

void print(char const* msg, char c[8]) {
	std::cout << msg << ": ";
	for (std::size_t i = 0; i < 8; ++i) std::cout << std::setfill('0') << std::setw(2) << std::hex << static_cast<uint32_t>(static_cast<unsigned char>(c[i]));
	std::cout << std::endl;
}

int main() {
	Gost g;
	g.show_key();
	char input[8] = {'n', 'a', 'm', 'e'};
	std::cout << "Message: " << input << std::endl;
	print("Before encryption", input);
	g.encrypt(reinterpret_cast<uint32_t*>(input));
	print("After encryption", input);
	g.decrypt(reinterpret_cast<uint32_t*>(input));
	print("After decryption", input);
	std::cout << "Message: " << input << std::endl;
}
