#pragma once
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "QueueOnList.h"

template <class T>
class BinarySearchTreeL {
private:
	struct Node {
		Node() {}
		Node(const T& value)
			:data(value) {}

		T data;
		Node* left = NULL;
		Node* right = NULL;
	};

	Node* root = NULL;

	// Recursive methods =======================================================

	Node* recInsert(Node*& rootPtr, const T& value) {
		if (rootPtr == NULL) rootPtr = new Node(value);
		else if (value <= rootPtr->data) {
			rootPtr->left = recInsert(rootPtr->left, value);
		}
		else {
			rootPtr->right = recInsert(rootPtr->right, value);
		}
		return rootPtr;
	}

	bool recSearch(Node* rootPtr, const T& value) const {
		if (rootPtr == NULL) return false;
		else if (rootPtr->data == value) return true;
		else if (value <= rootPtr->data) return recSearch(rootPtr->left, value);
		else return recSearch(rootPtr->right, value);
	}

	T recGetMin(Node* rootPtr) const {
		if (root == NULL) throw std::underflow_error("tree is empty");
		else if (rootPtr->left != NULL) return recGetMin(rootPtr->left);
		else return rootPtr->data;
	}

	T recGetMax(Node* rootPtr) const {
		if (root == NULL) throw std::underflow_error("tree is empty");
		else if (rootPtr->right != NULL) return recGetMax(rootPtr->right);
		else return rootPtr->data;
	}

	int recGetHeight(Node* rootPtr) const {
		if (rootPtr == NULL) return -1;
		return std::max(recGetHeight(rootPtr->left), recGetHeight(rootPtr->right)) + 1;
	}

	void recPreorder(Node* rootPtr) const {
		if (rootPtr == NULL) return;
		std::cout << rootPtr->data << ' ';
		recPreorder(rootPtr->left);
		recPreorder(rootPtr->right);
	}

	void recInorder(Node* rootPtr) const {
		if (rootPtr == NULL) return;
		recInorder(rootPtr->left);
		std::cout << rootPtr->data << ' ';
		recInorder(rootPtr->right);
	}

	void recPastorder(Node* rootPtr) const {
		if (rootPtr == NULL) return;
		recPastorder(rootPtr->left);
		recPastorder(rootPtr->right);
		std::cout << rootPtr->data << ' ';
	}

	Node* GetNodeOfMin(Node* rootPtr) {
		if (root == NULL) throw std::underflow_error("tree is empty");
		else if (rootPtr->left != NULL) return GetNodeOfMin(rootPtr->left);
		else return rootPtr;
	}

	Node* recErase(Node* rootPtr, const T& value) {
		if (rootPtr == NULL) return rootPtr;
		else if (value < rootPtr->data)
			rootPtr->left = recErase(rootPtr->left, value);
		else if (value > rootPtr->data)
			rootPtr->right = recErase(rootPtr->right, value);
		else {
			// Case 1: no child
			if (rootPtr->left == NULL && rootPtr->right == NULL) {
				delete rootPtr;
				rootPtr = NULL;
			}
			// Case 2: one child
			else if (rootPtr->left == NULL) {
				Node* temp = rootPtr;
				rootPtr = rootPtr->right;
				delete temp;
			}
			else if (rootPtr->right == NULL) {
				Node* temp = rootPtr;
				rootPtr = rootPtr->left;
				delete temp;
			}
			// Case 3: two children
			else {
				Node* temp = GetNodeOfMin(rootPtr->right);
				rootPtr->data = temp->data;
				rootPtr->right = recErase(rootPtr->right, temp->data);
			}
		}
		return rootPtr;
	}

	// Friend private functions ================================================

	friend bool recIsBST(Node* rootPtr, int minValue, int maxValue) {
		if (rootPtr == NULL) return true;
		if (rootPtr->data > minValue &&
			rootPtr->data < maxValue &&
			recIsBST(rootPtr->left, minValue, rootPtr->data) &&
			recIsBST(rootPtr->right, rootPtr->data, maxValue))
			return true;

		return false;
	}

	friend bool checkInorder(Node* rootPtr, T& last) {
		if (rootPtr == NULL) return true;
		checkInorder(rootPtr->left, last);

		if (last > rootPtr->data) return false;
		else last = rootPtr->data;

		checkInorder(rootPtr->right, last);
	}

public:

	// Class methods ===========================================================

	Node* get_root() const {
		return root;
	}

	Node* insert(const T& value) {
		return recInsert(root, value);
	}

	void erase(const T& value) {
		recErase(root, value);
	}

	bool find(const T& value) const {
		return recSearch(root, value);
	}

	T get_min() const {
		return recGetMin(root);
	}

	T get_max() const {
		return recGetMax(root);
	}

	int height() const {
		return recGetHeight(root);
	}

	void preorder() const {
		recPreorder(root);
		std::cout << '\n';
	}

	void inorder() const {
		recInorder(root);
		std::cout << '\n';
	}

	void pastorder() const {
		recPastorder(root);
		std::cout << '\n';
	}

	void level_order() {
		if (root == NULL) return;
		QueueOnList<Node*> q;
		q.push(root);

		while (!q.empty()) {
			Node* poped = q.pop();
			if (poped->left != NULL) q.push(poped->left);
			if (poped->right != NULL) q.push(poped->right);
			std::cout << poped->data << ' ';
		}
	}

	// Friend functions ========================================================

	friend bool IsBinarySearchTree(Node* rootPtr) {
		return recIsBST(rootPtr, INT_MIN, INT_MAX);
	}

	friend bool IsBSTinorder(Node* rootPtr) {
		T last = NULL;
		return checkInorder(rootPtr, last);
	}
};