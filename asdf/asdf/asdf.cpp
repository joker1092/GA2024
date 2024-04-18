#include <iostream>
using namespace std;

void nstrcpy(char* string1, char* string2) {
    int i = 0;
    while (string2[i] != '\0') {
        string1[i] = string2[i];
        
        i++;
    }
    string1[i] = '\0';
}

int main()
{
    char str1[20] = "abc";
    char str2[20] = "abcdefghij";

    nstrcpy(str1, str2);

    cout << str1;

	return 0;
}
