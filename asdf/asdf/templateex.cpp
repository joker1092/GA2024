#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;





template<typename T> class Vector
{
    T* buff;
public:
    Vector() {}             // Ÿ�� �߷��� �Ұ��� �Ұ�� ���� ���� �߷� ���̵� �ʿ�
    Vector(int sz, T initValue) {}
};

Vector()->Vector<int>;


int main()
{
    Vector v1(10, 3);       // ������ �Ű������� �߷а��� 
    Vector v2;              // ���̵带 ���ؼ� �߷� ����
}