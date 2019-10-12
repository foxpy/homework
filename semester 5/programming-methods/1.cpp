#include <iostream>
#include <stack>

int main(void) {
	char c;
	std::stack<char> s;

	while(std::cin >> c) {
		if (c == '(' || c == '[' || c == '{') {
			s.push(c);
			continue;
		}

		if (s.empty()) {
			std::cout << "no" << std::endl;
			exit(0);
		}

		if ((s.top() == '(' && c == ')') ||
		    (s.top() == '[' && c == ']') ||
		    (s.top() == '{' && c == '}')) {
			s.pop();
		} else {
			std::cout << "no" << std::endl;
			exit(0);
		}
	}

	if (!s.empty()) {
		std::cout << "no" << std::endl;
		exit(0);
	} else {
		std::cout << "yes" << std::endl;
	}
}
