#include <iostream>
using namespace std;

class Item
{
	int index;
	char name[40];
	int level;
	char grade;
public:
	Item(const char* _name, int _level, char _grade, int _index = 0) {
		index = _index;
		int namesize = strlen(_name) + 1;
		strcpy_s(name, namesize, _name);
		level = _level;
		grade = _grade;
	}
	Item* GetPoint() {
		return this;
	}
	void SetGrade(char _grade) {
		grade = _grade;
	}
	char GetGrade() {
		return grade;
	}
	void SetIndex(int _index) {
		index = _index;
	}
	char GetIndex() {
		return index;
	}
	char* GetName() {
		return name;
	}
	void GradeUp() {
		switch (grade)
		{
		case 'S':grade = 'S'; break;
		case 'A':grade = 'S'; break;
		case 'B':grade = 'A'; break;
		case 'C':grade = 'B'; break;
		default:
			break;
		}
	}
	void Show() {
		cout << index << "," << name << "," << level << ",'" << grade << "'" << endl;
	}
	bool operator==(Item& other) {
		return index == other.index;
	}
	bool CompareIndex(int i) {
		return index == i;
	}
};

class ItemManager
{
	Item* list[100];
	int index;
public:
	ItemManager();
	~ItemManager();
	void add(Item p);
	void remove(int index);
	void GradeUp();
	void print();
};

ItemManager::ItemManager()
{
	for (size_t i = 0; i < 100; i++) {
		list[i] = nullptr;
	}
	index = 1;
}

ItemManager::~ItemManager()
{
	for (size_t i = 0; i < 100; i++) {
		delete list[i];
	}
}

void ItemManager::add(Item p) {
	p.SetIndex(index);
	for (size_t i = 0; i < 100; i++)
	{
		if (list[i] == nullptr) {
			list[i] = new Item(p);
			index++;
			break;
		}
	}
}

void ItemManager::remove(int index) {
	for (size_t i = 0; i < 100; i++)
	{
		if (list[i] != nullptr) {
			if (list[i]->CompareIndex(index))
			{
				delete list[i];
				list[i] = nullptr;
				break;
			}
		}
	}
}

void ItemManager::GradeUp() {
	cout << "합성 재료를 입력하세요.(동일한 등급의 두 아이템의 번호)" << endl;
	int a;
	int b;
	Item* item1 = nullptr;
	Item* item2 = nullptr;
	while (true)
	{
		cin >> a;
		cin >> b;
		if (a == b) {
			cout << "잘 못 입력하셨습니다." << endl;
			continue;
		}

		for (size_t i = 0; i < 100; i++)
		{
			if (list[i] != nullptr)
			{
				if (list[i]->CompareIndex(a))
				{
					item1 = list[i]->GetPoint();
				}
				if (list[i]->CompareIndex(b))
				{
					item2 = list[i]->GetPoint();;
				}
			}
		}
		if (item1->GetGrade() == item2->GetGrade()) {
			break;
		}
		else {
			cout << "등급이 같지 않습니다." << endl;
		}
	}
	item1->GradeUp();
	cout << "합성결과 : " << index << "," << item1->GetName() << "," << 1 << "," << item1->GetGrade() << endl;
	add(Item(item1->GetName(), 1, item1->GetGrade()));
	remove(a);
	remove(b);
}

void ItemManager::print() {
	for (size_t i = 0; i < 100; i++)
	{
		if (list[i] == nullptr) {
			continue;
		}
		list[i]->Show();
	}
}



int main()
{
	ItemManager manager;
	manager.add(Item("단검", 1, 'A'));
	manager.add(Item("단검", 2, 'A'));
	manager.add(Item("갑옷", 3, 'B'));
	manager.add(Item("반지", 3, 'B'));
	manager.add(Item("반지", 3, 'S'));
	//manager.remove(2);
	manager.print();

	manager.GradeUp();

	manager.print();


	return 0;
}