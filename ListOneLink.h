#pragma once
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <stack>

template <class T>
class ListOneLink {
private:
	struct Node {
		Node() {}
		Node(const T& value)
			:data(value) {}

		T data;
		Node* next = NULL;
	};

	void recursion_reverse_of_node(Node* n) {
		if (n->next == NULL) {
			head = n;
			return;
		}
		recursion_reverse_of_node(n->next);
		n->next->next = n;
		n->next = NULL;
	}

	Node* head = NULL;
	size_t elements = 0;

public:
	~ListOneLink() {
		while (head != NULL) {
			auto next = head->next;
			delete head;
			head = next;
		}
	}

	size_t size() {
		return elements;
	}

	Node* insert_after(const T& data, Node* pos) { // insert after Node
		Node* temp = new Node(data);
		Node* pos_next = pos->next;
		pos->next = temp;
		temp->next = pos_next;
		++elements;
		return temp;
	}

	Node* insert_before(const T& data, Node* pos) { // insert before Node
		Node* to_insert = new Node(data);
		Node* temp = head;
		while (temp != pos && temp->next != pos)
			temp = temp->next;
		temp == pos ? head = to_insert : temp->next = to_insert;
		to_insert->next = pos;
		++elements;
		return to_insert;
	}

	Node* push_front(const T& value) {
		Node* temp = new Node(value);
		temp->next = head;
		head = temp;
		++elements;
		return head;
	}

	void pop_front() {
		if (head == NULL) throw std::length_error("list is empty");
		Node* new_head = head->next;
		delete head;
		head = new_head;
		--elements;
	}

	void reverse() {
		Node* current = head;
		Node* prev = NULL;
		Node* adjacent;

		while (current != NULL) {
			adjacent = current->next;
			current->next = prev;
			prev = current;
			current = adjacent;
		}

		head = prev;
	}

	void stack_reverse() {
		std::stack<Node*> nodes;
		Node* temp = head;
		while (temp != NULL) {
			nodes.push(temp);
			temp = temp->next;
		}

		temp = nodes.top();
		head = temp;
		nodes.pop();
		while (!nodes.empty()) {
			temp->next = nodes.top();
			nodes.pop();
			temp = temp->next();
		}
		temp->next = NULL;
	}

	void print() {
		Node* temp = head;
		bool first = true;
		std::cout << "List contains " << elements << " elements: ";
		while (temp != NULL) {
			if (!first) std::cout << ", ";
			first = false;
			std::cout << temp->data;
			temp = temp->next;
		}
		std::cout << '\n';
	}

	bool empty() {
		return head == NULL;
	}

	T get_first() {
		if (empty()) throw std::underflow_error("no elements");
		return head->data;
	}

	void reverse_recursion() {
		recursion_reverse_of_node(head);
	}
};