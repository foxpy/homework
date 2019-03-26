#include <vector>
#include <map>
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

template<class index_t, class value_t>
class Dictionary {
	private:
		std::map<index_t, value_t> dictionary;

	public:
		void add(index_t const&, value_t const&);
		const value_t get(index_t const&);
		void del(index_t const&);
};
