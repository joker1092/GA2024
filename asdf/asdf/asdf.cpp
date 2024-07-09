#include <iostream>
using namespace std;

template <typename T>
class CStaticMember
{
private:
	static T mem;					//템플릿 클래스의 static 맴버

public:
	void Add(int num) { mem += num; }
	void Show() { cout << mem << endl; }
};

template <typename T>
T CStaticMember<T>::mem = 0;		//외부에서 초기화

//template<>						
//long CStaticMember<long>::mem = 5;	//static 멤버 특수화

int main(void)
{
	CStaticMember<int> obj1;
	CStaticMember<int> obj2;
	obj1.Add(2);
	obj2.Add(3);
	obj1.Show();

	CStaticMember<long> obj3;
	CStaticMember<long> obj4;
	obj3.Add(100);
	obj4.Show();
	return 0;
}