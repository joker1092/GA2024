#include <iostream>
using namespace std;

//String 클래스를 구현하세요. ( 특수맴버함수, 연산자 오버로드 )
class String
{
private:
    char* str;
public:
    //생성자	
    String() { str = new char[1]; }
    String(const char* _str) {
        str = new char[strlen(_str) + 1];
        strcpy_s(str, strlen(_str) + 1, _str);
    }
    //복사 생성자
    String(const String& oStr)
    {
        str = new char[strlen(oStr.str) + 1];
        strcpy_s(str, strlen(oStr.str) + 1, oStr.str);
    }
    String(String&& rStr) noexcept
    {
        str = rStr.str;
        rStr.str = nullptr;
    }
    //복사 대입 연산자
    String& operator=(const String& oStr) {
        delete[] str;
        str = new char[strlen(oStr.str) + 1];
        strcpy_s(str, strlen(oStr.str) + 1, oStr.str);
    }
    String& operator=(String&& rStr) noexcept {
        delete[] str;
        str = rStr.str;
        rStr.str = nullptr;
    }

    String& operator+=(const String& oStr)
    {
        int size = strlen(str) + strlen(oStr.str) + 1;
        char* temp = new char[size];
        strcpy_s(temp, size, str);
        strcat_s(temp, size, oStr.str);
        delete[] str;
        str = temp;
        return *this;
    }
    //연산자 함수 + == <<
    String operator+(const String& oStr)
    {
        int size = strlen(str) + strlen(oStr.str) + 1;
        char* temp = new char[size];
        strcpy_s(temp, size, str);
        strcat_s(temp, size, oStr.str);
        String tempobj = (temp);
        delete[] temp;
        return tempobj;
    }
    bool operator==(const String& oStr)
    {
        return strcmp(str, oStr.str);
    }

    friend ostream& operator<<(ostream& o, const String& obj) {
        o << obj.str;
        return o;
    }

    ~String()
    {
        delete[] str;
    }
};


int main(void)
{
    String s1 = "abc";
    String s2 = "def";

    String s3 = s1 + s2;

    String s4 = ""; s4 += s3;

    cout << s1 << " " << s2 << " " << s3 << " " << s4 << endl;


    cout << (s1 == s4) << endl;

    return 0;
}