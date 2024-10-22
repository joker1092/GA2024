#include <iostream>
#include <cstdio>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main()
{
    unsigned short hostPort = 0x1234;
    unsigned short networkPort = htons(hostPort);

    cout << "호스트 순서   Port : " << hex << hostPort << endl;
    cout << "네트워크 순서 Port : " << hex << networkPort << endl;
    cout << endl;

    unsigned long hostIpAddress = 0x12345678;
    unsigned long networkIpAddress = htonl(hostIpAddress);
    cout << "호스트 순서   IP : " << hex << hostIpAddress << endl;
    cout << "네트워크 순서 IP : " << hex << networkIpAddress << endl;

    cout << "\n*Host Byte Odering 확인*" << endl;
    unsigned char* p = (unsigned char*)&hostIpAddress;

    for (int i = 0; i < sizeof(unsigned long); i++)
    {
        printf("%p = 0x%02x\n", (p + i), *(p + i));
    }

    return 0;
}