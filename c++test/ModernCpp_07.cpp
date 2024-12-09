// 아래 코드를 실행하면, 벡터 관리 중에 복사(copy)가 발생됩니다.
// 
// 이동생성자가 호출되도록, 
// MyClass 클래스를 수정하세요.

#include <iostream>
#include <vector>

struct MyClass
{
    int value;

    explicit MyClass(int value) : value(value) {  }

    MyClass(MyClass const& other) : value(other.value) {
        std::cout << "copy\n";
    } 

    MyClass(MyClass&& other) noexcept : value(std::move(other.value)) {
        std::cout << "move\n";
    }
};

int main()
{
    std::vector<MyClass> v;
    v.emplace_back(1);
    v.emplace_back(2);
}
