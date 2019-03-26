#include <array>
#include <cstdlib>
#include <exception>

#define STACK_SIZE 0xFF

template<class T>
class Stack
{
	private:
		std::array<T, STACK_SIZE> stack = {0};
		size_t sp = 0; // Stack Pointer

	public:
		void push(T const&);
		T pop();
};

struct stack_overflow : public std::exception {
	const char* what() const throw() {
		return "stack overflow";
	}
};

template<class T>
class MyStack
{
	private:
		std::array<T, STACK_SIZE> stack = {0};
		size_t sp = 0; // Stack Pointer

	public:
		void push(T const&);
		T pop();
};
