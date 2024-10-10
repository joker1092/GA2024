#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

class Item {
public:
    int id = 0;
    string name = "";
    int level = 0;
    Item(int _id,string _name,int _level):id(_id),name(_name),level(_level) {}
    virtual ~Item()
    {
        cout << "Item 소멸자" << endl;
    }
    virtual void print() {
        cout << "id: " << id << ", name: " << name << ", level: " << level << endl;
    }
};

class Weapon : public Item {
public:
    int damage = 0;
    Weapon(int _id,string _name,int _level,int _damage):Item(_id,_name,_level),damage(_damage) {}
    void print() override {
        cout << "id: " << id << ", name: " << name << ", level: " << level << ", damage: " << damage << endl;
    }
    ~Weapon()
    {
        cout << "Weapon 소멸자" << endl;
    }
};
class Armor : public Item {
    public:
    int defense = 0;
    Armor(int _id,string _name,int _level,int _defense):Item(_id,_name,_level),defense(_defense) {}
    void print() override {
        cout << "id: " << id << ", name: " << name << ", level: " << level << ", defense: " << defense << endl;
    }
    ~Armor()
    {
        cout << "Armor 소멸자" << endl;
    }
};
class Ring : public Item {
    public:
    int hp = 0;
    Ring(int _id,string _name,int _level,int _hp):Item(_id,_name,_level),hp(_hp) {}
    ~Ring()
    {
        cout << "Ring 소멸자" << endl;
    }
};

class ItemManager {
    vector<unique_ptr<Item>> ItemList;
    using itemIter = vector<unique_ptr<Item>>::iterator;
    public:
    ItemManager() {}
    ~ItemManager() {
        ItemList.clear();
    }

    void AddItem(unique_ptr<Item> item) {
        ItemList.push_back(move(item));
    }
    void RemoveItem(int id) {
        auto iter = find_if(ItemList.begin(), ItemList.end(), [id](auto& item) {return item->id == id;});
        if (iter != ItemList.end()) {
            ItemList.erase(iter);
        }
    }
    void PrintAll() {
        for (auto& item : ItemList) {
            item->print();
        }
    }

    static bool LevelSort(itemIter& a, itemIter& b) {
        return (*a)->level < (*b)->level;
    }
    static bool NameSort(itemIter& a, itemIter& b) {
        return (*a)->name < (*b)->name;
    }
    static bool IndexSort(itemIter& a, itemIter& b) {
        return (*a)->id < (*b)->id;
    }
    void Sort(bool(*sort)(itemIter& a, itemIter& b)) {
        std::sort(ItemList.begin(), ItemList.end(), sort);
    }
};;



int main() {
    ItemManager im;

    im.AddItem(make_unique<Weapon>(1,"단검",1,10));
    im.AddItem(make_unique<Weapon>(2, "단검", 5, 20));
    im.AddItem(make_unique<Armor>(3, "갑옷", 5, 10));
    im.AddItem(make_unique<Armor>(4, "갑옷", 3, 5));

    im.PrintAll();

    cout << "LevelSort" << endl;
    im.Sort(&ItemManager::LevelSort);
    im.PrintAll();

    cout << "RemoveItem3" << endl;
    im.RemoveItem(3);
    im.PrintAll();

    return 0;
}