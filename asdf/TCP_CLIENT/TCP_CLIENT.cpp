
#include<iostream>
#include<string> 
#include<WinSock2.h> 
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;
#define SERVER_PORT   6060 // 서버 포트 번호
#define SERVER_ADDR   "172.21.1.17" // 서버 IP 주소
#define BUFSIZE 100

int main()
{
    /* 1. 윈속 초기화 */
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        cout << "Winsock 초기화 오류" << endl;

    /* 2. 접속할 서버 정보 저장 */
    SOCKADDR_IN srvAddr;
    memset(&srvAddr, 0, sizeof(srvAddr));
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, SERVER_ADDR, &(srvAddr.sin_addr)) != 1)
    {
        cout << "Invalid IP address" << endl;
        return -1;
    }
    else
    {
        cout << "Server IP address: " << SERVER_ADDR << endl;

        /* 3. 클라이언트 소켓 생성 */
        SOCKET hSocket = socket(PF_INET, SOCK_STREAM, 0);


        /* 4. 서버에 접속 요청 */
        connect(hSocket, (SOCKADDR*)&srvAddr, sizeof(srvAddr));

        cout << "Connecting Ok...\n";

        string sendMessage;
        
        cout << "\nInput massge: ";
        getline(cin, sendMessage);

        /* 5. 메시지 전송 */

        send(hSocket, sendMessage.c_str(), sendMessage.length(), 0);

        closesocket(hSocket);
    }

    WSACleanup();
    return 0;
}