#include <iostream>
#include <string>

template <typename T>
void Print(T in) {
	std::cout << in << std::endl;
}

template <typename T>
void PrintTypeSize(T in) {
	std::cout << sizeof(in) << std::endl;
}

template <>
void PrintTypeSize(const char* in) {
	std::cout << strlen(in) << std::endl;
}



int main()
{
	Print(1);
	Print('a');
	Print("s");

	PrintTypeSize(1);
	PrintTypeSize('1');
	PrintTypeSize("1"); //strlen()
}