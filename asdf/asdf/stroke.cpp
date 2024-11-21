#include <iostream>
using namespace std;


void operator "" _print(unsigned long long num)
{
    cout << num << endl;
}

bool operator "" _odd(unsigned long long num) {
    return num % 2 == 1;
}

void operator "" _print(const char* str, size_t len)
{
    cout << str << endl;
}

int main()
{
    123_print;

    bool is_odd = 1234_odd;

    "aaa"_print;
}
