#include <iostream>
#include <cstring> 
class SomeClass
{
public:

    SomeClass()
    {
        std::cout << "Default Constructor called" << std::endl;
        m_data = nullptr;
    }

    SomeClass(const char* str)
    {
        std::cout << "Parameterized Constructor called" << std::endl;

        const int nLen = strlen(str);
        m_data = new char[nLen + 1];

        strcpy_s(m_data, nLen + 1, str);
    }

    SomeClass(const SomeClass& other)
    {
        std::cout << "Copy Constructor called" << std::endl;
        const int nLen = strlen(other.m_data);
        m_data = new char[nLen + 1];
        strcpy_s(m_data, nLen + 1, other.m_data);
    }

    SomeClass(SomeClass&& other) noexcept
    {
        std::cout << "Move Constructor called" << std::endl;
        m_data = other.m_data;
        other.m_data = nullptr;
    }

    void operator = (const SomeClass& other) {
        if (this == &other) return;

        std::cout << "Copy operator called" << std::endl;
        const int nLen = strlen(other.m_data);
        m_data = new char[nLen + 1];
        strcpy_s(m_data, nLen + 1, other.m_data);
    }

    void operator = (SomeClass&& other) noexcept {
		if (this == &other) return;

		std::cout << "Move operator called" << std::endl;
		m_data = other.m_data;
		other.m_data = nullptr;
	}


    ~SomeClass()
    {
        std::cout << "Destructor called" << std::endl;
        delete[] m_data;
    }

    char* Data() { return m_data; }

private:
    char* m_data;
};


int main()
{

    SomeClass obj1("Hello");
    SomeClass obj2 = obj1;
    SomeClass obj3;
    obj3 = obj1;

    SomeClass obj4;
    obj4 = std::move(obj1);
    std::cout << "obj4 data: " << obj4.Data() << std::endl;
    //std::cout << "obj1 data: " << obj1.Data() << std::endl;
    std::cout << "obj2 data: " << obj2.Data() << std::endl;
    std::cout << "obj3 data: " << obj2.Data() << std::endl;

    system("pause");
    return 0;
}