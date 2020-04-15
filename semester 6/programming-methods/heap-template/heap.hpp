#pragma once
#include <cstddef>
#include <algorithm>

template<class T>
struct heap {
public:
	heap() {
		capacity = 1;
		length = 0;
		data = new T[capacity];
	}
	~heap() {
		delete[] data;
	}

	bool empty() {
		return length == 0;
	}

	std::size_t size() {
		return length;
	}

	void push(const T &t) {
		if (length >= capacity)
			grow();
		data[length] = t;
		++length;
		std::sort(&data[0], &data[length], [](T &t1, T &t2) { return t1 > t2; });
	}

	T& top() {
		return data[0];
	}

	void pop() {
		data[0] = data[length-1];
		--length;
		std::sort(&data[0], &data[length], [](T &t1, T &t2) { return t1 > t2; });
		if (capacity > 1 && length < capacity / 2)
			shrink();
	}
private:
	void grow() {
		resize(capacity * 2);
	}

	void shrink() {
		resize(capacity / 2);
	}

	void resize(std::size_t new_capacity) {
		T *old_data = data;
		T *new_data = new T[new_capacity];
		for (std::size_t i = 0; i < length; ++i) {
			new_data[i] = old_data[i];
		}
		delete[] data;
		data = new_data;
		capacity = new_capacity;
	}
	std::size_t capacity;
	std::size_t length;
	T *data;
};
