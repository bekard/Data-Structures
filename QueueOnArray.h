#pragma once
#include <stdexcept>
#include <algorithm>

constexpr int MinusOne = -1;

template <class T, size_t capacity>
class QueueOnArray {
private:
	int first = MinusOne;
	int last = MinusOne;
	size_t size = 0;
	T* data = new T[capacity];

public:
	~QueueOnArray() {
		delete[] data;
	}

	void push(const T& value) { // Pushes the given element value to the end of the queue
		if (full()) throw std::overflow_error("queue is full");
		if (empty() && first == last) {
			last = 0; first = 0;
			data[0] = value;
		}
		else {
			int index = ++last % int(capacity);
			data[index] = value;
		}
		++size;
	}

	T pop() { // Removes an element from the front of the queue.
		if (empty()) throw std::underflow_error("queue is empty");
		T poped = data[first % int(capacity)];
		--size;
		if (!empty()) ++first;
		return poped;
	}

	bool empty() const {
		return size == 0;
	}

	bool full() const {
		return size == capacity;
	}

	T front() const {
		return data[first];
	}

	size_t get_size() const {
		return size;
	}

	size_t get_capacity() const {
		return capacity;
	}
};