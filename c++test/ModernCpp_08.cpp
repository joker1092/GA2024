// 기본 객체생성은 가능하지만
// 복사생성과 복사대입연산이 안 되도록 
// 
// Widget 클래스를 수정하세요.

#include <iostream>

class Widget {
public:
    Widget() = default;
	Widget(const Widget& w) = delete;
	Widget& operator=(const Widget& w) = delete;
	~Widget() = default;
private:
};

int main()
{
    Widget w;
    Widget w2(w);           // 복사생성 불가
    w2 = w;                 // 복사대입 불가
}
