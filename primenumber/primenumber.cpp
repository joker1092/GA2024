#include <iostream>

bool isPrime(int n, int divisor = 2) {
	if (n == 2)
	{
		return true;
	}
	if (n % divisor == 0) {
		return false;
	}
	if (divisor * divisor > n) {
		return true;
	}
	return isPrime(n, divisor + 1);
}


//bool isPrime(int n) {
//	for (int i = 2; i * i < n; i++)
//	{
//		if (n % i == 0)
//		{
//			return false;
//		}
//	}
//	return true;
//}


int main()
{
	int i = 1;
	while (true)
	{
		if (isPrime(i))
		{
			if (i > 1000)
			{
				std::cout << i << std::endl;
				break;
			}
		}
		i++;
	}
	return 0;
}