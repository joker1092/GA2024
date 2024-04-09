#include <iostream>
using namespace std;

int str_length(char* str);

int main(int argc, char* argv[])
{
	char str[] = { "What is your name?" };
	printf("이 문자열의 길이 : %d \n", str_length(str));
	return 0;
}

int str_length(char* str) {
	int rt = 0;
	while (str[rt] != '\0') {
		rt++;
	}
	return rt+1;
}