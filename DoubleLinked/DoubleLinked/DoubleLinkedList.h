#pragma once

template<typename T>
class DoubleLinkedList
{
public:
	struct Node {
		T deta;
		Node* prev;
		Node* next;
	};

	Node* head_ptr = nullptr;
	Node* tail_ptr = nullptr;

	struct Iterator {
		Node* pCurr = nullptr;

		Iterator(Node* p = nullptr) {
			pCurr = p;
		}

		Iterator& operator++() {
			pCurr = pCurr->next;
			return *this;
		}

		T& operator*() {
			return pCurr->deta;
		}

		bool operator==(const Iterator& ref) {
			return pCurr == ref.pCurr;
		}

		bool operator!=(const Iterator& ref) {
			return pCurr != ref.pCurr;
		}

	
	};


	bool Empty() {
		return (head_ptr == nullptr);
	}

	int Size() {
		Node* ptr = head_ptr;
		int count = 0;
		while (ptr!=nullptr)
		{
			ptr = ptr->next;
			count++;
		}
		return count;
	}

	void Clear() {
		Node* tail = tail_ptr;
		Node* prev_tail = nullptr;
		while (tail != nullptr)
		{
			prev_tail = tail->prev;
			delete tail;
			tail = prev_tail;
		}
		head_ptr = nullptr;
		tail_ptr = nullptr;
	}

	Node* Insert(Node* pPos, T deta) {
		Node* node = new Node;
		node->deta = deta;
		node->prev = pPos;
		Node* posNext = pPos->next;
		
		pPos->next = node;
		node->next = posNext;
		if (posNext==nullptr)
		{
			tail_ptr = node;
		}
		else {
			posNext->prev = node;
		}
		return node;
	}

	Node* PushBack(T deta) {
		Node* node = new Node;
		node->deta = deta;
		node->prev = tail_ptr;
		node->next = nullptr;
		Node* tail_node = tail_ptr;
		if (tail_node!=nullptr)
		{
			tail_node->next = node;
		}
		tail_ptr = node;
		if (node->prev==nullptr)
		{
			head_ptr = node;
		}
		return node;
	}

	Node* Delete(Node* pPos=nullptr) {
		if (pPos==nullptr)
		{
			Node* tail = tail_ptr;
			Node* prev_tail = tail->prev;

			delete tail;
			tail_ptr = prev_tail;
			if (prev_tail == nullptr)
			{
				head_ptr = nullptr;
			}
			else {
				prev_tail->next = nullptr;
			}
			return nullptr;
		}
		else {
			Node* pos = pPos;
			Node* prev_node = pPos->prev;
			Node* next_node = pPos->next;
			if (prev_node==nullptr)
			{
				head_ptr = next_node;
			}
			else {
				prev_node->next = next_node;
			}
			if (next_node==nullptr)
			{
				tail_ptr = prev_node;
			}
			else {
				next_node->prev = prev_node;
			}
			return next_node;
		}
	}

	Iterator Begin() {
		return Iterator(head_ptr);
	}

	Iterator End() {
		return Iterator(nullptr);
	}

};