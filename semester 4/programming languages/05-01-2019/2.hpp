#include <array>
#include <cstdlib>

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
