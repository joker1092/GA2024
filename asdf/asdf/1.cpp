#include <iostream>
using namespace std;

class Point
{
	int x, y;
public:

	Point(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
		//cout << x << "," << y << endl;
	}
	void print() {
		cout << x << "," << y << endl;
	}
	bool operator==(Point& other) {
		return other.x == x && other.y == y;
	}
};

class PointManager
{
	Point* list[100];
public:
	PointManager();
	~PointManager();
	void add(Point p);
	void remove(Point p);
	void print();
};

PointManager::PointManager()
{
	for (size_t i = 0; i < 100; i++) {
		list[i] = nullptr;
	}
}

PointManager::~PointManager()
{
	for (size_t i = 0; i < 100; i++) {
		delete list[i];
	}
}

void PointManager::add(Point p) {
	for (size_t i = 0; i < 100; i++)
	{
		if (list[i] == nullptr) {
			list[i] = new Point(p);
			break;
		}
	}
}

void PointManager::remove(Point p) {
	for (size_t i = 0; i < 100; i++)
	{
		if (*list[i] == p)
		{
			delete list[i];
			list[i] = nullptr;
			break;
		}
	}
}

void PointManager::print() {
	for (size_t i = 0; i < 100; i++)
	{
		if (list[i] == nullptr) {
			continue;
		}
		list[i]->print();
	}
}



int main()
{
	PointManager manager;
	manager.add(Point(1, 1));
	manager.add(Point(2, 2));
	manager.add(Point(3, 3));

	manager.remove(Point(2, 2));
	manager.print();

	return 0;
}