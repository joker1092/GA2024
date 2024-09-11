//c++ Ÿ�Ժ�ȯ ������ 4����
//1. static_cast
//2. dynamic_cast
//3. const_cast
//4. reinterpret_cast

//dynamic_cast<new_type>(expression)
//safe downcasting�� ���
//�θ�Ŭ������ �����͸� �ڽ�Ŭ������ �����ͷ� ��ȯ�Ҷ� ���
//����ð��� �ٿ�ĳ������ �������� �˻�
//���� ���� ������ ��� ����

//������ ��� : new_type�� value�� ��ȯ
//������ ��� : nullptr ��ȯ
//�������� ������ ��� : std::bad_cast ���ܸ� ����


#include <iostream>

class Base
{
public:
    Base() { std::cout << "Base()\n"; };
    virtual ~Base() { std::cout << "~Base()\n"; };
    void Show() { std::cout << "Base Show()" << std::endl; }
};

class Derived : public Base
{
public:
    int n = 0;
    Derived() { std::cout << "Derived()\n"; };
    ~Derived() { std::cout << "~Derived()\n"; };
    void Show() { std::cout << "Derived  Show()" << std::endl; }
};



int main()
{
    Base* b = new Derived(); //��ĳ���� Derived* -> Base*
    //Derived* d = new Base(); //�ٿ�ĳ���� Base* -> Derived* //error 
    //Derived* d = (Derived*)new Base(); //�ٿ�ĳ���� Base* -> Derived* //����� ����ȯ�� ���� �ϳ� ����
    //d->n = 0; //runtime error

    Derived* d = (Derived*)b; //������ �ٿ�ĳ���� //�ڽ� --> �θ� --> �ڽ� ���� ���� ���
    d->n = 0; //ok


    return 0;
}