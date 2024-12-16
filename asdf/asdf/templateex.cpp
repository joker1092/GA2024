#include <iostream>
using namespace std;
template<typename ... types>
void print(types ... agrs) {
    ((cout <<agrs<<" "), ...)<<endl;
}


int main()
{
    print(1, 3);
    print(1, 2, 3, 4);
    return 0;
}