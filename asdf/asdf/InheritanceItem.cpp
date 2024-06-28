#include <iostream>
using namespace std;
//---------------------------------------------------------------------------------------
//������ Ŭ���� ���� ( ����, ��, ����, �Ź� ) ( ��� Ȱ�� )
class Item {
	int index;
	char name[40];
	int level;
	char grade;
public:
	Item() { index = 0; level = 0; grade = 'D'; memset(name, '\0', 40); }
	Item(const char* _name, int _level, char _grade, int _index = 0) {
		index = _index;
		int namesize = strlen(_name) + 1;
		strcpy_s(name, namesize, _name);
		level = _level;
		grade = _grade;
	}
	~Item() {}
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
	void SetLevel(int lev) {
		level = lev;
	}
	int GetLevel() {
		return level;
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
	virtual void Show() {
		cout << index << "," << name << "," << level << ",'" << grade << "'";
	}
	bool operator==(Item& other) {
		return index == other.index;
	}
	bool CompareIndex(int i) {
		return index == i;
	}
};

class Weapon : public Item {
	int atk;
public:
	Weapon() :Item::Item() { atk = 10; }
	Weapon(const char* _name, int _level, char _grade, int _index = 0) :Item(_name, _level, _grade, _index)
	{
		switch (_grade)
		{
		case 'S':atk = 40; break;
		case 'A':atk = 30; break;
		case 'B':atk = 20; break;
		case 'C':atk = 15; break;
		default:
			atk = 10;
			break;
		}
	}
	void Show() {
		Item::Show();
		cout << "," << atk << endl;
	}
};

class Armor : public Item {
	int defend;
public:
	Armor() :Item::Item() { defend = 10; }
	Armor(const char* _name, int _level, char _grade, int _index = 0) :Item(_name, _level, _grade, _index)
	{
		switch (_grade)
		{
		case 'S':defend = 40; break;
		case 'A':defend = 30; break;
		case 'B':defend = 20; break;
		case 'C':defend = 15; break;
		default:
			defend = 10;
			break;
		}
	}
	void Show() {
		Item::Show();
		cout << "," << defend << endl;
	}
};

class Ring : public Item {
	int defend;
public:
	Ring() :Item::Item() { defend = 10; }
	Ring(const char* _name, int _level, char _grade, int _index = 0) :Item(_name, _level, _grade, _index)
	{
		switch (_grade)
		{
		case 'S':defend = 40; break;
		case 'A':defend = 30; break;
		case 'B':defend = 20; break;
		case 'C':defend = 15; break;
		default:
			defend = 10;
			break;
		}
	}
	void Show() {
		Item::Show();
		cout << "," << defend << endl;
	}
};

class Shoes : public Item {
	int defend;
public:
	Shoes() : Item::Item() { defend = 10; }
	Shoes(const char* _name, int _level, char _grade, int _index = 0) :Item(_name, _level, _grade, _index)
	{
		switch (_grade)
		{
		case 'S':defend = 40; break;
		case 'A':defend = 30; break;
		case 'B':defend = 20; break;
		case 'C':defend = 15; break;
		default:
			defend = 10;
			break;
		}
	}
	void Show() {
		Item::Show();
		cout << "," << defend << endl;
	}
};

//�������� �߰� �ϰ� ��� �����ֱ�. (�����Ҵ�)
class ItemManager
{
	int index;
	Item* list[100];
public:
	ItemManager() {
		for (size_t i = 0; i < 100; i++) {
			list[i] = nullptr;
		}
		index = 1;
	};
	~ItemManager() {
		for (size_t i = 0; i < 100; i++) {
			delete list[i];
		}
	};

	Item* ItemIdentity(int identity, const char* name, int level, char grade, int index) {
		switch (identity)
		{
		case 1:
			return new Weapon(name, level, grade, index);
		case 2:
			return new Armor(name, level, grade, index);
		case 3:
			return new Ring(name, level, grade, index);
		case 4:
			return new Shoes(name, level, grade, index);
		default:
			return new Item(name, level, grade, index);
		}

	}
	void Add() {
		bool isAdd = false;
		for (size_t i = 0; i < 100; i++)
		{
			if (list[i] == nullptr) {
				isAdd = true;
			}
		}
		if (!isAdd)
		{
			cout << "�������� �ʹ� �����ϴ�. ���� ���ּ���" << endl;
			return;
		}
		cout << "�������� �Է��ϼ���. (����(1:���� 2:��: 3:���� 4:�Ź�), �̸�, ����, ��� ) ex)1 �ܰ�  1   A" << endl;
		int identity;
		char name[40];
		int level;
		char grade;
		const char* pcchar = name;

		cin >> identity >> name >> level >> grade;

		Item* item = ItemIdentity(identity, pcchar, level, grade, index);
		if (item != nullptr)
		{
			for (size_t i = 0; i < 100; i++)
			{
				if (list[i] == nullptr) {

					list[i] = item;
					index++;
					break;
				}
			}
		}
		else {
			cout << "�߸� �Է� �ϼ̽��ϴ�." << endl;
		}
	};
	void remove() {
		bool isRemove = false;
		for (size_t i = 0; i < 100; i++)
		{
			if (list[i] != nullptr) {
				isRemove = true;
			}
		}
		if (!isRemove)
		{
			cout << "�������� �����ϴ�. �߰� ���ּ���" << endl;
			return;
		}
		int input;
		cout << "���� �� ������ �Է�: ";
		cin >> input;
		for (size_t i = 0; i < 100; i++)
		{
			if (list[i] != nullptr) {
				if (list[i]->CompareIndex(input))
				{
					delete list[i];
					list[i] = nullptr;
					break;
				}
			}
		}
	}
	void remove(int index) {
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
	void GradeUp() {
		cout << "�ռ� ��Ḧ �Է��ϼ���.(������ ����� �� �������� ��ȣ)" << endl;
		int a;
		int b;
		Item* item1 = nullptr;
		Item* item2 = nullptr;
		cin >> a;
		cin >> b;
		if (a == b) {
			cout << "�� �� �Է��ϼ̽��ϴ�." << endl;
			return;
		}

		for (size_t i = 0; i < 100; i++)
		{
			if (list[i] != nullptr)
			{
				if (list[i]->CompareIndex(a))
				{
					item1 = list[i];
					if (item1->GetGrade() == 'S')
					{
						cout << "�ְ� ����� �������Դϴ�." << endl;
						return;
					}
				}
				if (list[i]->CompareIndex(b))
				{
					item2 = list[i];
					if (item2->GetGrade() == 'S')
					{
						cout << "�ְ� ����� �������Դϴ�." << endl;
						return;
					}
				}
			}
		}
		if (item1->GetGrade() != item2->GetGrade()) {
			cout << "����� ���� �ʽ��ϴ�." << endl;
			return;
		}

		int identity;
		if (typeid(*item1) == typeid(Weapon))
			identity = 1;
		else if (typeid(*item1) == typeid(Armor))
			identity = 2;
		else if (typeid(*item1) == typeid(Ring))
			identity = 3;
		else if (typeid(*item1) == typeid(Shoes))
			identity = 4;
		else
			identity = 0;

		item1->GradeUp();
		cout << "�ռ���� : " << index << "," << item1->GetName() << "," << 1 << "," << item1->GetGrade() << endl;
		const char* p = item1->GetName();
		//Item* item = new Item(p, 1, item1->GetGrade(), index);
		Item* item = ItemIdentity(identity, p, 1, item1->GetGrade(), index);
		for (size_t i = 0; i < 100; i++)
		{
			if (list[i] == nullptr) {

				list[i] = item;
				index++;
				break;
			}
		}
		remove(a);
		remove(b);
	}
	void LevelUp() {
		print();
		int input;
		Item* item1 = nullptr;
		cout << "������(������ �ִ뷹���� 10)" << endl;
		cout << "������ �� ������ �Է�: ";
		cin >> input;

		for (size_t i = 0; i < 100; i++)
		{
			if (list[i] != nullptr)
			{
				if (list[i]->CompareIndex(input))
				{
					item1 = list[i];
					if (item1->GetLevel() == 10)
					{
						cout << "�������� �ִ뷡���Դϴ�." << endl;
						return;
					}
					else {
						int lev = item1->GetLevel();
						item1->SetLevel(++lev);
					}
				}

			}
		}
	}
	void print() {
		cout << "���: " << endl;
		for (size_t i = 0; i < 100; i++)
		{
			if (list[i] == nullptr) {
				continue;
			}
			list[i]->Show();
		}
	}
};
//�⺻ �������̽�
//1. ������ �߰�  2, ����  3. ������  4 �ռ�  5 ��Ϻ��� (0, ������)
int main(void) {
	int input = -1;
	ItemManager g_im;
	while (input != 0)
	{
		cout << "1. ������ �߰�  2, ����  3. ������  4 �ռ�  5 ��Ϻ��� (0, ������)" << endl;
		cin >> input;
		switch (input)
		{
		case 1:
			g_im.Add();
			break;
		case 2:
			g_im.remove();
			break;
		case 3:
			g_im.LevelUp();
			break;
		case 4:
			g_im.GradeUp();
			break;
		case 5:
			g_im.print();
			break;
		default:
			break;
		}
	}
	return 0;
}


//EX)
//�������� �Է��ϼ���. (�������̵�, �̸�, ����, ��� )
//
//������ �߰�: �ܰ�, 1, 'A'
//
//���: 
//1, �ܰ�, 1, 'A'
//
//������ �߰�: ����, 1, 'B'
//
//���: 
//1, �ܰ�, 1, 'A'
//2, ����, 1, 'B'
//
//������ �߰�: ����, 1, 'B'
//
//���: 
//1, �ܰ�, 1, 'A'
//2, ����, 1, 'B'
//3, ����, 1, 'B'

//Ư�� ������ ������ �ϱ� ( �ִ뷹���� 10)
//
//������ �� ������ �Է�: 1
//
//���: 
//1, �ܰ�, 2, 'A'
//2, ����, 1, 'B'
//3, ����, 1, 'B'

//������ �ռ� �ϱ�  ( ������ 2�� �Է� - ��� ���� ������ �ϳ�)  (S, A, B, C ���)
//
//���: 2 3
//
//���: 
//1, �ܰ�, 2, 'A'
//4, ����, 1, 'A'        


	