#pragma once
#include <cstddef>

template<class T>
struct heap {
public:
	heap() {
		capacity = 1;
		length = 0;
		offset = 0;
		data = new T[capacity];
	}
	~heap() {
		delete[] data;
	}

	bool empty() {
		return length-offset == 0;
	}

	std::size_t size() {
		return length-offset;
	}

	void push(const T &t) {
		if (length >= capacity)
			grow();
		data[length] = t;
		++length;
	}

	T& front() {
		return data[offset];
	}

	void pop() {
		++offset;
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
	std::size_t offset;
	T *data;
};
