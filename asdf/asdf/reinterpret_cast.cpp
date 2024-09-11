//c++ Ÿ�Ժ�ȯ ������ 4����
//1. static_cast
//2. dynamic_cast
//3. const_cast
//4. reinterpret_cast

//reinterpret_cast<new_type>(expression)
//�ַ� ������ Ÿ�԰��� ��ȯ�� ���
//�������� �����ͷ� ��ȯ�ϰų� �����͸� ���������� ��ȯ�Ҷ� ���
//expression�� �ش��ϴ� Ÿ���� ��Ʈ������ new_type���� ��ȯ

#include <iostream>

int main()
{
    int a = 0x00'00'01'21;

    //int* ptr = reinterpret_cast<int*>(a);

    //int -> int* �� ��ȯ
    //int�� int*�� ��ȯ�Ҷ��� �ּҰ��� �ƴ� �������� ������ ��ȯ
    //�޸� �ּ� 0x00'00'01'02�� ������ ����Ű�� �����ͷ� ��ȯ
    //��Ȯ�� ���ǵ��� ���� �ൿ�̹Ƿ� ����� �����ؾ���

    int* ptr2 = &a;
    char* c;
    c = reinterpret_cast<char*>(ptr2);

    std::cout << " int* - > char* " << *c << std::endl;  //0x21->33
    printf("int* - > char* print type %d\n", *c);        //33







    return 0;
}