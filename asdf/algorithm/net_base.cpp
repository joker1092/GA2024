#include <iostream>
#include <cstdio>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main()
{
    unsigned short hostPort = 0x1234;
    unsigned short networkPort = htons(hostPort);

    cout << "ȣ��Ʈ ����   Port : " << hex << hostPort << endl;
    cout << "��Ʈ��ũ ���� Port : " << hex << networkPort << endl;
    cout << endl;

    unsigned long hostIpAddress = 0x12345678;
    unsigned long networkIpAddress = htonl(hostIpAddress);
    cout << "ȣ��Ʈ ����   IP : " << hex << hostIpAddress << endl;
    cout << "��Ʈ��ũ ���� IP : " << hex << networkIpAddress << endl;

    cout << "\n*Host Byte Odering Ȯ��*" << endl;
    unsigned char* p = (unsigned char*)&hostIpAddress;

    for (int i = 0; i < sizeof(unsigned long); i++)
    {
        printf("%p = 0x%02x\n", (p + i), *(p + i));
    }

    return 0;
}