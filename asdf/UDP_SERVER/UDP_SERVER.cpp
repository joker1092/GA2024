// UDP 서버 

#include <WinSock2.h>
#include <iostream>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT  7070
#define BUFSIZE  100

int main()
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "Winsock 초기화 오류" << endl;
        return -1;
    }

    SOCKET srvSocket;
    srvSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    SOCKADDR_IN srvAddr;
    memset(&srvAddr, 0, sizeof(srvAddr));

    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(SERVER_PORT);
    srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(srvSocket, (SOCKADDR*)&srvAddr, sizeof(srvAddr));

    while (1) {
        cout << "Binding OK..." << endl;
        cout << "UDP Server running... " << endl;

        SOCKADDR_IN peerAddr;
        int nAddrSize = sizeof(peerAddr);
        char recvMsg[BUFSIZE + 1] = "";


        int nRecv = recvfrom(srvSocket, recvMsg, sizeof(recvMsg), 0,
            (SOCKADDR*)&peerAddr, &nAddrSize);


        recvMsg[BUFSIZE] = '\0';

        cout << "Client : " << recvMsg << endl;

        if (nRecv == -1)
        {
            cout << "Receive Error: " << WSAGetLastError() << endl;
            break;
        }
    }
    

    closesocket(srvSocket);
    WSACleanup();

    return 0;
}
