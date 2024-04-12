#pragma once

template<typename T>
class MyStack
{
	struct Node {
		T data;
		Node* pNode;
	};
private:
	Node* TopNode = nullptr;
	int count = 0;
public:
	MyStack() {

	}
	~MyStack() {
		while (MyStack<T>::isEmpty())
		{
			pop();
		}
	}
	bool isEmpty() {
		if (MyStack<T>::TopNode == nullptr)
			return true;
		else
			return false;
	}
	int size() {
		if (MyStack<T>::TopNode == nullptr) {
			return 0;
		}
		else {
			return count;
		}
	}
	void push(T data) {
		Node* node = new Node;
		if (node == nullptr)
		{
			return;
		}
		node->data = data;
		node->pNode =TopNode;
		TopNode = node;
		count++;
	}
	void  pop() {
		if (MyStack<T>::isEmpty())
		{
			return;
		}
		Node* node = TopNode;
		Node* p_node = node->pNode;

		delete node;
		TopNode = p_node;
		count--;
	}
	T top() {
		/*if (MyStack<T>::isEmpty())
		{
			return NULL;
		}*/
		Node* node = MyStack<T>::TopNode;
		return node->data;
	}
};