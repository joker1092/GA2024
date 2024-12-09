// 아래 Base 클래스의 특수맴버 함수들을 각각 정의하세요. 
// default 키워드를 활용하세요.

#include <iostream>
using namespace std;

class Base {
public:
    // 생성자
    Base() = default;
    // 소멸자
    ~Base() = default;
    // 복사 생성자
    Base(const Base& b) {
        cout << "복사 생성자 호출" << endl;
    }
    // 복사 대입 연산
    Base& operator=(const Base& b) {
		cout << "복사 대입 연산자 호출" << endl;
		return *this;
	}
    // 이동 생성자
    Base(const Base&& b) noexcept {
    cout << "이동 생성자 호출" << endl;
    }
    // 이동 대입 연산
    Base& operator=(const Base&& b) noexcept {
        cout << "이동 대입 연산자 호출" << endl;
        return *this;
    }
};

int main()
{
    Base b1;
    Base b2 = b1;            // 복사 생성자 호출
    Base b3 = std::move(b1); // 이동 생성자 호출
    b2 = b3;                 // 복사 대입 연산자 호출
    b3 = std::move(b2);      // 이동 대입 연산자 호출
}
