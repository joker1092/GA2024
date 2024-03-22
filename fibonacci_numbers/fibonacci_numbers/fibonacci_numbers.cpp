#include <iostream>
using namespace std;

int main()
{
    //피보나치 수열
    char a[101][21] = {};
    a[0][0] = 0;
    a[1][0] = 1;
    for (size_t i = 2; i < 101; i++)
    {
        for (size_t j = 0; j < 21; j++)
        {
            /*if (i == 100) {
                cout << "입" << a[i - 1][j] << a[i - 2][j] << endl;
                cout << "출" << a[i - 1][j] + a[i - 2][j] << endl;
            }*/

            a[i][j] = a[i][j] + a[i - 1][j] + a[i - 2][j];
            if (a[i][j] >= 10)
            {
                a[i][j] = a[i][j] - 10;
                a[i][j + 1] = a[i][j + 1] + 1;
            }
        }
    }

    for (size_t k = 21; k > 0; k--)
    {
        cout << (int)a[100][k - 1];
    }

    return 0;
}
