// 벡터 컨테이너로 
// Weapon, Armor 객체의 포인터를 관리하려고 합니다.
// 아래 코드를 스마트 포인터(shared_ptr)로 변경하세요.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Item {
public:
    string name;
    Item(string s) : name(s) { }
    virtual ~Item() {}
};

class Weapon : public Item {
public:
    Weapon(string s) : Item(s) { }
};

class Armor : public Item {
public:
    Armor(string s) : Item(s) { }
};

int main()
{
    vector<std::shared_ptr<Item>> items;
    items.push_back(shared_ptr<Item>(new Weapon{ "Weapon1" }));
    items.push_back(shared_ptr<Item>(new Weapon{ "Weapon2" }));
    items.push_back(shared_ptr<Item>(new Armor{ "Armor1" }));

    for (auto& e : items) std::cout << e->name << " ";

    items.clear();

	return 0;
}