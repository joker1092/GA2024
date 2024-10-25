#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;

template <typename T>
class Ref {
    T* t;
    public:
    Ref(T& t) : t(&t) {};
    void operator = (T& t) { this->t = &t; }
    operator T () { return *t; }
    T& get() const { return *t; }
};

template <typename T>
T& MyRef(T& t) {
    return Ref<T>(t).get();
}

int test(std::string name, int a, int b) {
    cout<<name << " " << a+b<< endl;
    return a+b;
}


class MyClass {
public:
    void display() {
        cout << "Hello MyClass" << endl;
    };
};

void func() { cout << "func" << endl; }

class FuncClass {
public:
    void mfunc1() { cout << "mfunc1" << endl; }
    void mfunc2(int value) { cout << "mfunc2" << endl; }
};


int main()
{
    vector<int> a(1);
    vector<int> b(2);
    vector<int> c(3);
    
    vector<vector<int>> container;

    container.push_back(a);
    container.push_back(b);
    container.push_back(c);

    vector<int> size_vec(4);

    transform(container.begin(), container.end(), size_vec.begin(), [](vector<int>& v) {return v.size(); });

    for (auto i : size_vec) {
        cout << i << endl;
    }
}