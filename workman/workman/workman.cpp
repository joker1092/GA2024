#include <iostream>
using namespace std;

int Squre(int num, int s) {
    int sum = 1;
    for (size_t i = 0; i < s; i++)
    {
        sum *= num;
    }
    return sum;
}

int main()
{
    char chNums[11];
    int splitNums[11];

    int converse;
    cin >> chNums;
    cin >> converse;

    int count = 0;
    while (true)
    {
        if (chNums[count] == '\0')
        {
            break;
        }
        if ('0'<=chNums[count] && '9' >= chNums[count])
        {
            splitNums[count] = chNums[count]-'0';
        }
        else if('A' <= chNums[count] && 'Z' >= chNums[count]) {
            splitNums[count] = chNums[count] - 'A' + 10;
        }
        count++;
    }
    
    int rt = 0;
    for (int i = 0; i < count; i++)
    {
        rt += (int)splitNums[i] * Squre(converse, i);
    }

    cout << rt;

    return 0;
}