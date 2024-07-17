#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <algorithm>

using namespace std;

class Item {
private:
	string name;
	int level;
public:
	Item(string _name, int _level) :name(_name), level(_level) {}
	~Item() {  }
	void print() { cout << name << " " << level << endl; }
	bool operator<(const Item& item) const {
		return level < item.level;
	}
	bool operator>(const Item& item) const {
		return level > item.level;
	}
	bool operator==(const Item& item) const {
		return level == item.level;
	}
	
	friend struct nameDecrease;
	friend struct nameIncrease;
};

struct nameDecrease {
	bool operator()(const Item& item1, const Item& item2) {
		return item1.name > item2.name;
	}
};

struct nameIncrease {
	bool operator()(const Item& item1, const Item& item2) {
		return item1.name < item2.name;
	}
};


bool ItemIncrease(const Item& item1, const Item& item2) {
	return item1 < item2;
}

bool ItemDecrease(const Item& item1, const Item& item2) {
	return item1 > item2;
}

int main() {
	vector<Item> vec;
	
	vec.emplace_back("단검", 1);
	vec.emplace_back("장검", 2);
	vec.emplace_back("갑옷", 5);
	vec.emplace_back("반지", 3);

	sort(vec.begin(), vec.end(), nameDecrease());
	//sort(vec.begin(), vec.end(), greater<Item>());

	for (auto& item : vec) {
		item.print();
	}
	
	return 0;
}