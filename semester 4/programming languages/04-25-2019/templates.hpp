#include <vector>
#include <cstdlib>

template<class T>
void multiply_by_min(T& array, size_t len);

template<class T>
void replace_zeros_by_average(T& array, size_t len);

template<class T>
void show_array(T& array, size_t len);

template<class T>
class Stack
{
	private:
		std::vector<T> stack;

	public:
		void push(T const&);
		T pop();
};
