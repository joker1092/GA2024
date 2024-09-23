#include <iostream>

enum Color
{
	RED,
	BLACK
};

template <typename T>
struct Node {
	Node* parent;
	Node* left;
	Node* right;
	Color color;
	int key;
	T data;
};

template <typename T>
struct RBTree {
	Node<T>* root=nullptr;
	void insert(int key, T data) {
		Node<T>* newNode = new Node<T>;
		newNode->key = key;
		newNode->data = data;
		newNode->color = RED;
		newNode->left = nullptr;
		newNode->right = nullptr;
		newNode->parent = nullptr;
		if (root == nullptr) {
			root = newNode;
			root->color = BLACK;
		}
		else {
			Node<T>* temp = root;
			while (temp != nullptr) {
				if (temp->key < key) {

				}
			}
		}
	}
	void remove(int key);
	T find(int key);
};

int main()
{

}