#include <iostream>
#include <string>
#include <iomanip>
#include <locale.h>
#include <langinfo.h>
#include <string.h>

#include <stdio.h>

// This function is ridiculous.
// Also I really don't like that I don't match the Unicode table.
// Looks like I'm doing something wrong.
std::string from_russian(char byte1, char byte2) {
	unsigned char c1 = *((unsigned char*) &byte1);
	unsigned char c2 = *((unsigned char*) &byte2);
	switch(c1) {
	case 0xd1:
		switch(c2) {
		case 0xb0: return(std::string("a")); // а
		case 0xb1: return(std::string("b")); // б
		case 0xb2: return(std::string("v")); // в
		case 0xb3: return(std::string("g")); // г
		case 0xb4: return(std::string("d")); // д
		case 0xb5: return(std::string("e")); // е
		case 0x91: return(std::string("e")); // ё
		case 0xb6: return(std::string("zh")); // ж
		case 0xb7: return(std::string("z")); // з
		case 0xb8: return(std::string("i")); // и
		case 0xb9: return(std::string("i")); // й
		case 0xba: return(std::string("k")); // к
		case 0xbb: return(std::string("l")); // л
		case 0xbc: return(std::string("m")); // м
		case 0xbd: return(std::string("n")); // н
		case 0xbe: return(std::string("o")); // о
		case 0xbf: return(std::string("p")); // п
		case 0x80: return(std::string("r")); // р
		case 0x81: return(std::string("s")); // с
		case 0x82: return(std::string("t")); // т
		case 0x83: return(std::string("u")); // у
		case 0x84: return(std::string("f")); // ф
		case 0x85: return(std::string("kh")); // х
		case 0x86: return(std::string("ts")); // ц
		case 0x87: return(std::string("ch")); // ч
		case 0x88: return(std::string("sh")); // ш
		case 0x89: return(std::string("shch")); // щ
		case 0x8b: return(std::string("y")); // ы
		case 0x8c: return(std::string("")); // ь
		case 0x8a: return(std::string("ie")); // ъ
		case 0x8d: return(std::string("e")); // э
		case 0x8e: return(std::string("iu")); // ю
		case 0x8f: return(std::string("ia")); // я
		case 0x90: return(std::string("A")); // А
		case 0x92: return(std::string("V")); // В
		default: printf("0x%02hhx, 0x%02hhx: WTF?\n", c1, c2);
		}
		break;
	case 0xd0:
		switch(c2) {
		case 0x91: return(std::string("B")); // Б
		default: printf("0x%02hhx, 0x%02hhx: WTF?\n", c1, c2);
		}
		break;
	default: printf("0x%02hhx, 0x%02hhx: WTF?\n", c1, c2);
	}
	return("");
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

	int i = 0;
	while(i < input.length()) {
		unsigned char c = *((unsigned char*) &input[i]);
		if(c < 0x80) {
			output.append(1, input[i]);
			i += 1;
		} else if(c < 0xe0) {
			output.append(from_russian(input[i], input[i+1]));
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
