// UDP 클라이언트

#include <WinSock2.h> 
#include <ws2tcpip.h>
#include <string>
#include <iostream>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 7070 // 서버 포트 번호
#define SERVER_ADDR "127.0.0.1" // 서버 IP 주소
#define SERVER_ADDR "172.21.1.17" // 서버 IP 주소
#define BUFSIZE 100

int main()
{

    /* 1. 윈속 초기화 */
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "Winsock 초기화 오류" << endl;
        return -1;
    }


    /* 2. UDP 서버 소켓 생성, 서버 정보 설정 */
    SOCKET hSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    SOCKADDR_IN srvAddr;

    memset(&srvAddr, 0, sizeof(srvAddr));

    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(SERVER_PORT);
    srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (inet_pton(AF_INET, SERVER_ADDR, &(srvAddr.sin_addr)) != 1)
    {
        cout << "Invalid IP address: " << WSAGetLastError() << endl;
    }
    else
    {
        cout << "UDP Client running " << endl;


        /* 3. 서버로 메시지 전달 */
        string sendMessage = "";
        /*while (sendMessage != "-1")
        {
            cout << "\nInput massge: ";
            getline(cin, sendMessage);

            int nSent = sendto(hSocket, sendMessage.c_str(), sendMessage.length(), 0, (SOCKADDR*)&srvAddr, sizeof(srvAddr));

            cout << "Sent: " << nSent << " bytes" << endl;

            if (nSent == -1)
            {
                cout << "Send Error: " << WSAGetLastError() << endl;
            }
        }*/

        while (1) {
            sendMessage = "eeee";
            int nSent = sendto(hSocket, sendMessage.c_str(), sendMessage.length(), 0, (SOCKADDR*)&srvAddr, sizeof(srvAddr));

            cout << "Sent: " << nSent << " bytes" << endl;

            if (nSent == -1)
            {
                cout << "Send Error: " << WSAGetLastError() << endl;
            }
        }
    }


    system("pause");

    /* 4. 소켓 종료 및 윈속 반환 */
    closesocket(hSocket);
    WSACleanup();


    return 0;
}