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

	void pop() {
		data[0] = data[length-1];
		--length;
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
