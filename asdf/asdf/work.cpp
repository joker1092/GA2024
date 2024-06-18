
//--------------------------------------------------------------------------------
// 연산자 오버로딩을 구현하여 코드를 완성하세요

#include <iostream>
using namespace std;

class CMyData
{
private:
	int m_nData = 0;
public:
	CMyData(int nParam) : m_nData(nParam) {}

	// +
	CMyData operator+(CMyData& other) { return CMyData(m_nData + other.m_nData); }
	// + 단항
	CMyData operator+() { return CMyData(-this->m_nData); }
	// ++
	CMyData& operator++() { ++this->m_nData; return *this; }
	// ++(int)
	CMyData operator++(int) { CMyData temp{ this->m_nData }; this->m_nData++; return temp; }
	// <
	bool operator<(CMyData& other) { return this->m_nData < other.m_nData; }
	// >
	bool operator>(CMyData& other) { return this->m_nData > other.m_nData; }
};


void main()
{
	CMyData a(1);
	CMyData b(2);

	CMyData c = a + b;

	c = +a;

	c = ++a;

	c = a++;

	cout << (a > b) << endl;
}

//-------------------------------------------------------------------------------- -
//주요 연산자오버로드에 대한 사용예시를 작성하세요.

//산술연산자 + -*%
// CMyData operator+(CMyData& other) { return CMyData(m_nData + other.m_nData); }
//비교연산자 < > <= >= == !=
// bool operator<(CMyData& other) { return this->m_nData < other.m_nData; }
//부호연산자 + -
// CMyData operator+() { return CMyData(-this->m_nData); }
//출력연산자
// friend std::ofstream& operator<<(std::ofstream& cout,CMyData& data) { std::cout << data.m_nData; return cout;	}
//배열연산자[]
// T& operator[](size_t index) { return array[index]; }
//함수연산자()
// CMyData operator()(int index) { return CMyData(this->m_nData+index); }
//포인터연산자 * ->
//T operator*(MyPtr) { return *ptr; }
//T* operator->(MyPtr) { return ptr; }
