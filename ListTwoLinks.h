#pragma once
#include <cstdlib>
#include <stdexcept>

template <class T>
class ListTwoLinks {
private:
	struct Node {
		Node() {}
		Node(const T& value)
			:data(value) {}

		T data;
		Node* next = NULL;
		Node* prev = NULL;
	};

	Node* get_tail() {
		Node* temp = head;
		while (head != NULL && temp->next != NULL) temp = temp->next;
		return temp;
	}

	Node* head = NULL;
	size_t elements = 0;

public:
	~ListTwoLinks() {
		while (head != NULL) {
			auto next = head->next;
			delete head;
			head = next;
		}
	}

	size_t size() {
		return elements;
	}

	Node* insert(const T& value, Node* pos) { // insert value before Node
		Node* to_insert = new Node(value);
		if (pos != head) {
			Node* temp = pos->prev;
			pos->prev = to_insert; //-
			to_insert->next = pos; //-
			to_insert->prev = temp;
			temp->next = to_insert; //~
		}
		else {
			pos->prev = to_insert; //-
			to_insert->next = pos; //-
			head = to_insert;	//~
		}
		++elements;
		return to_insert;	
	}

	void erase(Node* pos) {
		Node* to_erase = pos;
		if (pos != head) {
			pos->prev->next = pos->next;
			if (pos->next != NULL) pos->next->prev = pos->prev;
		}
		else {
			head = head->next;
			head->prev = NULL;
		}
		--elements;
		delete pos;
	}

	Node* push_front(const T& value) {
		Node* new_head = new Node(value);
		if (head != NULL) head->prev = new_head;
		new_head->next = head;
		head = new_head;
		++elements;
		return head;
	}

	Node* push_back(const T& value) {
		Node* new_node = new Node(value);
		if (head == NULL) {
			head = new_node;
		}
		else {
			Node* tail = get_tail();
			new_node->prev = tail;
			tail->next = new_node;
		}
		++elements;
		return new_node;
	}

	void pop_back() {
		Node* tail = get_tail();
		tail == head ? head = NULL : tail->prev->next = NULL;
		--elements;
		delete tail;
	}

	void pop_front() {
		if (elements == 0) throw std::length_error("list is empty");
		Node* pop = head;
		head = head->next;
		if (head != NULL) head->prev = NULL;
		--elements;
		delete pop;
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
};