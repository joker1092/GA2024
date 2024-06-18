
//--------------------------------------------------------------------------------
// ������ �����ε��� �����Ͽ� �ڵ带 �ϼ��ϼ���

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
	// + ����
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
//�ֿ� �����ڿ����ε忡 ���� ��뿹�ø� �ۼ��ϼ���.

//��������� + -*%
// CMyData operator+(CMyData& other) { return CMyData(m_nData + other.m_nData); }
//�񱳿����� < > <= >= == !=
// bool operator<(CMyData& other) { return this->m_nData < other.m_nData; }
//��ȣ������ + -
// CMyData operator+() { return CMyData(-this->m_nData); }
//��¿�����
// friend std::ofstream& operator<<(std::ofstream& cout,CMyData& data) { std::cout << data.m_nData; return cout;	}
//�迭������[]
// T& operator[](size_t index) { return array[index]; }
//�Լ�������()
// CMyData operator()(int index) { return CMyData(this->m_nData+index); }
//�����Ϳ����� * ->
//T operator*(MyPtr) { return *ptr; }
//T* operator->(MyPtr) { return ptr; }
