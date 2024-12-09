#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;





template<typename T> class Vector
{
    T* buff;
public:
    Vector() {}             // 타입 추론이 불가능 할경우 유저 정의 추론 가이드 필요
    Vector(int sz, T initValue) {}
};

Vector()->Vector<int>;


int main()
{
    Vector v1(10, 3);       // 생성자 매개변수로 추론가능 
    Vector v2;              // 가이드를 통해서 추론 가능
}