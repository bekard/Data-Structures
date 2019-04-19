#pragma once
#include <cstdlib>
#include <stdexcept>

template <class T>
class QueueOnList {
private:
	struct Node {
		Node() {}
		Node(const T& value)
			:data(value) {}

		T data;
		Node* next = NULL;
	};

	Node* first = NULL;
	Node* last = NULL;
	size_t size = 0;

public:
	void push(const T& value) {
		Node* n = new Node(value);
		if (size == 0) { // first push
			first = last = n;
		}
		else {
			last->next = n;
			last = n;
		}
		++size;
	}

	T pop() {
		if (empty()) throw std::underflow_error("queue is empty");
		T poped = first->data;
		--size;
		if (first->next != NULL) {
			Node* n = first;
			first = first->next;
			delete n;
		}
		else {
			delete first;
			first = last = NULL;
		}
		return poped;
	}

	bool empty() const {
		return size == 0;
	}

	T front() const {
		return first->data;
	}

	size_t get_size() const {
		return size;
	}

};