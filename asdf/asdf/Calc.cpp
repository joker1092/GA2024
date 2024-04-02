#include <iostream>

namespace Calc {
	int g_count = 0;

	int Add(int n, int m) {
		g_count++;
		return n + m;
	}
	int Sub(int n, int m) {
		g_count++;
		return n - m;
	}
	int Mul(int n, int m) {
		g_count++;
		return n * m;
	}
	int Div(int n, int m) {
		g_count++;
		return n / m;
	}
	void PrintCount() {
		std::cout << g_count;
	}
}