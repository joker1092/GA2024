//c++ 타입변환 연산자 4가지
//1. static_cast
//2. dynamic_cast
//3. const_cast
//4. reinterpret_cast

//reinterpret_cast<new_type>(expression)
//주로 포인터 타입간의 변환에 사용
//정수형을 포인터로 변환하거나 포인터를 정수형으로 변환할때 사용
//expression에 해당하는 타입을 비트단위로 new_type으로 변환

#include <iostream>

int main()
{
    int a = 0x00'00'01'21;

    //int* ptr = reinterpret_cast<int*>(a);

    //int -> int* 로 변환
    //int를 int*로 변환할때는 주소값이 아닌 정수값을 가지고 변환
    //메모리 주소 0x00'00'01'02를 번지를 가리키는 포인터로 변환
    //명확히 정의되지 않은 행동이므로 사용을 자제해야함

    int* ptr2 = &a;
    char* c;
    c = reinterpret_cast<char*>(ptr2);

    std::cout << " int* - > char* " << *c << std::endl;  //0x21->33
    printf("int* - > char* print type %d\n", *c);        //33







    return 0;
}