#include <iostream>
#include <string>
#include <iomanip>
#include <locale.h>
#include <langinfo.h>
#include <string.h>

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

	int i = 0;
	while(i < input.length()) {
		unsigned char c = *((unsigned char*) &input[i]);
		if(c < 0x80) {
			output.append(1, input[i]);
			i += 1;
		} else if(c < 0xe0) {
			i += 2;
		} else if(c < 0xf0) {
			i += 3;
		} else if(c < 0xf8) {
			i += 4;
		} else if(c < 0xfc) {
			i += 5;
		} else {
			i += 6;
		}
	}

	std::cout << "Input:  " << input << std::endl <<
	             "Output: " << output << std::endl;

	return EXIT_SUCCESS;
}
