#include <iostream>
#include <string>
#include <iomanip>
#include <locale.h>
#include <langinfo.h>
#include <string.h>
#include <cstdint>
#include <vector>

std::string to_translit(std::uint16_t sequence)
{
	// "ё" and "Ё" are laughing on me!
	if (sequence == 0x0401) {
		return "E";
	} else if (sequence == 0x0451) {
		return "e";
	}
	std::vector<std::string> s = {"A", "B", "V", "G", "D", "E", "ZH", "Z", "I", "I",
	                              "K", "L", "M", "N", "O", "P", "R", "S", "T", "U", "F",
	                              "KH", "TS", "CH", "SH", "SHCH", "Y", "", "IE", "E", "IU", "IA",
	                              "a", "b", "v", "g", "d", "e", "zh", "z", "i", "i",
	                              "k", "l", "m", "n", "o", "p", "r", "s", "t", "u", "f",
	                              "kh", "ts", "ch", "sh", "shch", "y", "", "ie", "e", "iu", "ia"};
	sequence -= 0x0410;

	return s[sequence];
}

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
	unsigned char c, cc;
	while(i < input.length()) {
		c = *((unsigned char*) &input[i]);
		cc = *((unsigned char*) &input[i+1]);
		if(c < 0x80) {
			output.append(input, i, 1);
			i += 1;
		} else if(c < 0xe0) {
			sequence = ((c & 0b00011111) << 6) | (cc & 0b00111111);
			if (((sequence >= 0x0410) && (sequence <= 0x044f)) ||
			     (sequence == 0x0401) || (sequence == 0x0451)) {
				output.append(to_translit(sequence));
			} else {
				output.append(input, i, 2);
			}
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
