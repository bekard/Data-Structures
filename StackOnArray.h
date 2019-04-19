#pragma once

#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <array>

template <class T, size_t size>
class StackOnArray {
private:
	T* stack = new T[size];
	int upper = -1; 

public:
	~StackOnArray() {
		delete[] stack;
	}

	void push(const T& value) {
		if (upper == size - 1) throw std::overflow_error("stack is overflow");
		stack[++upper] = value;
	}

	T pop() {
		if (upper == -1) throw std::range_error("stack is empty");
		return stack[upper--];
	}

	T top() {
		return T[upper];
	}

	bool empty() {
		return upper == -1;
	}
};