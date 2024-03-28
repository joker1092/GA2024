#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int paper[101][101] = {};

    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        int x = 0;
        int y = 0;
        cin >> x >> y;
        
        for (int i = x; i < x+10; i++)
        {
            for (int j = y; j < y+10; j++)
            {
                if (paper[i][j]==0)
                {
                    paper[i][j] = 1;
                    sum++;
                }
            }
        }
    }
    
    cout << sum;
    
    return 0;
}

