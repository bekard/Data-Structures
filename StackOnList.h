#pragma once
#include "ListOneLink.h"
#include <string>
#include <utility>

template <class T>
class StackOnList {
private:
	struct Node {
		Node() {}
		Node(const T& value)
			:data(value) {}

		T data;
		Node* next = NULL;
	};

	Node* top = NULL;
	size_t elements = 0;

public:
	size_t size() {
		return elements;
	}

	void push(const T& value) {
		Node* temp = new Node(value);
		temp->next = top;
		top = temp;
		++elements;
	}

	T pop() {
		if (top == NULL) throw std::length_error("list is empty");
		T poped = get_top();
		Node* new_top = top->next;
		delete top;
		top = new_top;
		--elements;
		return poped;
	}

	T get_top() {
		if (top == NULL) throw std::underflow_error("no elements");
		return top->data;
	}

	bool empty() {
		return top == NULL;
	}
};

// check for balanced Parentheses ------------------------------------------------------------------

bool IsOpenBracket(char ch) {
	switch (ch) {
	case '(': case '[': case '{':
		return true;
	default:
		return false;
	}
}

bool IsCloseBracket(char ch) {
	switch (ch) {
	case ')': case ']': case '}':
		return true;
	default:
		return false;
	}
}

bool IsBracketsPair(char open, char close) {
	std::string brackets;
	brackets += open; brackets += close;
	if (brackets == "{}" || brackets == "[]" || brackets == "()") return true;
	return false;
}

bool CheckBalancedParentheses(const std::string& s) {
	StackOnList<char> brackets;
	for (auto ch : s) {
		if (IsOpenBracket(ch)) brackets.push(ch);
		else if (IsCloseBracket(ch)) {
			if (IsBracketsPair(brackets.get_top(), ch)) brackets.pop();
			else break;
		}
	}
	return brackets.empty();
}

//--------------------------------------------------------------------------------------------------