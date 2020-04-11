#include <string>
#include <fstream>
#include <cstddef>
#include "function-pointers.hpp"

Filesystem::Filesystem(const std::string &path) {
	open_and_create_if_not_exists(path);
	file.read(reinterpret_cast<char*>(&entries), sizeof(entries));
}

void Filesystem::open_and_create_if_not_exists(const std::string &path) {
	file.open(path, std::ios::binary | std::ios::out | std::ios::in);
	if (!file.is_open()) {
		file.open(path, std::ios::binary | std::ios::out);
		std::size_t cnt = 0;
		file.write(reinterpret_cast<char*>(&cnt), sizeof(cnt));
		file.close();
		file.open(path, std::ios::binary | std::ios::out | std::ios::in);
	}
}
