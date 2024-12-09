// items 벡터 컨테이너에 담겨있는 객체들 중에서 
// Weapon 객체만 weapons 벡터로 옮기려고 합니다.
// 아래 코드를 완성해서 출력하세요.

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    string name;
    Item(string s) : name(s) { }
    virtual ~Item() {}
};

struct Weapon : public Item { Weapon(string s) : Item(s) { } };
struct Armor : public Item { Armor(string s) : Item(s) { } };

int main()
{
    vector< unique_ptr<Item> > items;
    items.push_back(unique_ptr<Weapon>(new Weapon{ "Weapon1" }));
    items.push_back(unique_ptr<Weapon>(new Weapon{ "Weapon2" }));
    items.push_back(unique_ptr<Armor>(new Armor{ "Armor1" }));
    items.push_back(unique_ptr<Armor>(new Armor{ "Armor2" }));

    vector< shared_ptr<Item> > weapons;

    // weapons 벡터로 무기만 이동시키는 코드 작성
    for (auto& i : items) {
        if (dynamic_cast<Weapon*>(i.get())) {
            weapons.push_back(move(i));
        }
    }
        
    for (auto& e : weapons) std::cout << e->name << " ";  //출력 : Weapon1 Weapon2      
}
