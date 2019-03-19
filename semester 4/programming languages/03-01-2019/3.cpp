#include <iostream>
#include <string>
#include <iomanip>
#include <locale.h>
#include <langinfo.h>
#include <string.h>

#include <cstdint>
#include <stdio.h>
#include <bitset>

int main()
{
	// That's mostly C code.. in the C++ project. I don't really like it.
	setlocale(LC_CTYPE, "");
	if (strcmp(nl_langinfo(CODESET), "UTF-8") != 0) {
		std::cerr << "Fatal error: non UTF-8 system detected. Panicing!" << std::endl;
		return EXIT_FAILURE;
	}

	std::string input, output;
	std::getline(std::cin, input);

	std::uint16_t sequence = 0;

	int i = 0;
	while(i < input.length()) {
		unsigned char c = *((unsigned char*) &input[i]);
		unsigned char cc = *((unsigned char*) &input[i+1]);
		if(c < 0x80) {
			output.append(input, i, 1);
			i += 1;
		} else if(c < 0xe0) {
			sequence = ((c & 0b00011111) << 6) | (cc & 0b00111111);
			std::bitset<16> b(sequence);
			std::cout << b << " " << std::hex << "0x" << sequence << std::endl;
			output.append(input, i, 2);
			i += 2;
		} else if(c < 0xf0) {
			output.append(input, i, 3);
			i += 3;
		} else if(c < 0xf8) {
			output.append(input, i, 4);
			i += 4;
		} else if(c < 0xfc) {
			std::cerr << "Fatal error: invalid UTF-8 sequence. Panicing!" << std::endl;
			return EXIT_FAILURE;
		}
	}

	std::cout << "Input:  " << input << std::endl <<
	             "Output: " << output << std::endl;


	return EXIT_SUCCESS;
}
