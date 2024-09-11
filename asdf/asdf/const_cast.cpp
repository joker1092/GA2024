//c++ Ÿ�Ժ�ȯ ������ 4����
//1. static_cast
//2. dynamic_cast
//3. const_cast
//4. reinterpret_cast

//const_cast<new_type>(expression)
//const_cast�� const�� volatile �Ӽ��� ���ִ� ������
//������� ������ ������

#include <iostream>



int main()
{
    //������ ������ ����� ����
    char str[] = "apple";
    const char* ptr = str;
    std::cout << "before : " << str << std::endl;

    //ptr[0] = "Q"; //error
    //char* c = (char*)ptr;  //const�� ����
    char* c = const_cast<char*>(ptr);  //const�� ����
    c[0] = 'Q';
    std::cout << "after : " << str << std::endl;

    //������ ������ ����� ����
    int tmp = 15;
    const int& ref = tmp;
    std::cout << "before : " << tmp << std::endl;

    //ref = 20; //error

    int& ref2 = const_cast<int&>(ref);
    ref2 = 20;
    std::cout << "after : " << tmp << std::endl;

    // const�� ������ ���� ������ ��찡 ����
    // cv_  ===> c : const, v : volatile
    // cvr_ ===> c : const, v : volatile, r : reference

    volatile int v = 10;
    //volatile �ֹ߼�
    //�׻� �޸𸮿� �ִ� ������ �о��
    //�����Ϸ��� ����ȭ�� ���� ����


    return 0;
}