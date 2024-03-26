#include <iostream>
using namespace std;

int main()
{	
	int N = 0;
	cin >> N;

	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 1; j < N-i; j++)
		{
			cout << " ";
		}
		for (size_t j = 0; j < 2*i+1; j++)
		{
			cout << "*";
		}
		cout << "\n";
	}
	for (size_t i = N - 1; i > 0 ; i--)
	{
		for (size_t j = 1; j < N - i+1; j++)
		{
			cout << " ";
		}
		for (size_t j = 0; j < 2 * i -1; j++)
		{
			cout << "*";
		}
		
		cout << "\n";
	}


	return 0;
}