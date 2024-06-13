#include <iostream>

//#define ALIGNAS alignas(16)
#define ALIGNAS

// 컴파일러 설정 (8)

struct ALIGNAS Data0
{
    char c;
    double d; //8
};

struct ALIGNAS Data1
{
    double d; //8
    char c;
};

struct ALIGNAS Data2
{
    char c;
    int n;
    double d; //8
};

struct ALIGNAS Data3
{
    char c1;
    char c2;
    int n;
};

void main()
{
    std::cout << "Alignment of Data0 struct: " << alignof(Data0) << std::endl;

    std::cout << "Size of Data0 struct: " << sizeof(Data0) << std::endl;

    std::cout << "Size of Data1 struct: " << sizeof(Data1) << std::endl;

    std::cout << "Size of Data2 struct: " << sizeof(Data2) << std::endl;

    std::cout << "Size of Data3 struct: " << sizeof(Data3) << std::endl;

}
