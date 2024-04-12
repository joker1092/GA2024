#include <iostream>
#include "MyStack.h"
using namespace std;

#define MAX 10


enum EMAZETYPE
{
	PATH, WALL, VISIT, BACK
};

struct Position
{
	int x, y;
};

//struct MyStack
//{
//	struct Node
//	{
//		Position data;
//		Node* pNode;
//	};
//
//	Node* TopPointer = nullptr;
//
//	/*Position Array[1000];
//	int nTopIndex = -1;*/
//
//	bool Empty() {
//		if (TopPointer == nullptr)
//		{
//			return true;
//		}
//		else {
//			return false;
//		}
//	}
//
//	/*bool Empty() {
//		if (nTopIndex == -1)
//		{
//			return true;
//		}
//		else {
//			return false;
//		}
//	}*/
//	int Size() {
//		int count = 0;
//		if (TopPointer != nullptr) {
//			Node* t_ptr = TopPointer;
//			Node* prev = t_ptr->pNode;
//			while (prev!= nullptr) {
//				if (prev != nullptr)
//				{
//					t_ptr = prev;
//					prev = t_ptr->pNode;
//					count++;
//				}
//			}
//		}
//	}
//	/*int Size() {
//		if (nTopIndex != -1) {
//			return nTopIndex + 1;
//		}
//	}*/
//
//	void Push(Position pos) {
//		Node* node = new Node;
//		if (node==nullptr)
//		{
//			return;
//		}
//		node->data = pos;
//		node->pNode = TopPointer;
//		TopPointer = node;
//	}
//
//	/*void Push(Position pos) {
//		nTopIndex++;
//		Array[nTopIndex] = pos;
//	}*/
//
//	void Pop() {
//		if (TopPointer==nullptr)
//		{
//			return;
//		}
//		Node* node = TopPointer;
//		Node* pnode = node->pNode;
//		delete node;
//		TopPointer = pnode;
//	}
//	/*void Pop() {
//		Array[nTopIndex] = { -1,-1 };
//		nTopIndex--;
//	}*/
//
//	Position Top() {
//		if (TopPointer!=nullptr)
//		{
//			Node* node = TopPointer;
//			return node->data;
//		}
//	}
//	/*Position Top() {
//		return Array[nTopIndex];
//	}*/
//};

int Maze[MAX][MAX] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 1, 0, 1, 1, 0, 1},
{1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
{1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
{1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

Position g_Player = { 1,1 };

MyStack<Position> stack;

void Update();
void Rander();
bool g_bQuit = false;

int main()
{
	
	Update();
	Rander();
}



void Update() {
	while (true)
	{
		int x = g_Player.x;
		int y = g_Player.y;
		Position pos;

		pos = { x,y };
		Maze[y][x] = 2;

		if (x == 8 && y == 8)
		{
			break;
		}
		else {
			if (Maze[y - 1][x] == 0)
			{
				stack.push(pos);
				g_Player.x = x;
				g_Player.y = y - 1;
			}
			else if (Maze[y][x + 1] == 0) {
				stack.push(pos);
				g_Player.x = x + 1;
				g_Player.y = y;
			}
			else if (Maze[y + 1][x] == 0) {
				stack.push(pos);
				g_Player.x = x;
				g_Player.y = y + 1;
			}
			else if (Maze[y][x - 1] == 0) {
				stack.push(pos);
				g_Player.x = x - 1;
				g_Player.y = y;
			}
			else {
				Maze[y][x] = 3;
				Position tmppos = stack.top();
				g_Player.x = tmppos.x;
				g_Player.y = tmppos.y;
				stack.pop();
			}

		}
	}
	
}

void Rander() {
	for (int i = 0; i < MAX; ++i)
	{
		for (int j = 0; j < MAX; ++j)
		{
			char ch = '\0';
			if (Maze[i][j] == EMAZETYPE::PATH)
			{
				ch = ' ';
			}
			else if (Maze[i][j] == EMAZETYPE::WALL)
			{
				ch = '#';
			}
			else if (Maze[i][j] == EMAZETYPE::VISIT)
			{
				ch = 'V';
			}
			else if (Maze[i][j] == EMAZETYPE::BACK)
			{
				ch = 'B';
			}
			cout << ch;
		}
		cout << '\n';
	}
}
