#pragma once
#include <cstddef>

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

	void push(const T &t) {
		if (length < capacity) {
			data[length] = t;
		} else {
			grow();
			data[length] = t;
		}
		++length;
	}

	T& top() {
		return data[0];
	}
private:
	void grow() {
		std::size_t old_capacity = capacity;
		capacity *= 2;
		T *old_data = data;
		T *new_data = new T[capacity];
		for (std::size_t i = 0; i < old_capacity; ++i) {
			new_data[i] = old_data[i];
		}
		delete[] data;
		data = new_data;
	}
	std::size_t capacity;
	std::size_t length;
	T *data;
};
