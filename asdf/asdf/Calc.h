#pragma once
#include <iostream>

namespace Calc {
	extern int g_count;

	int Add(int n, int m);
	int Sub(int n, int m);
	int Mul(int n, int m);
	int Div(int n, int m);
	void PrintCount();
}