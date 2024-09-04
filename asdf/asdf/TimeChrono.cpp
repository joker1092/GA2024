#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
    long sum = 0;

    system_clock::time_point start = system_clock::now();
    for (int i = 0; i < 1000000; i++)
    {
        sum += i;
    }
    system_clock::time_point end = system_clock::now();

    nanoseconds nano = end - start;

    cout << "경과시간(ns) : " << nano.count() << endl;

    return 0;
}