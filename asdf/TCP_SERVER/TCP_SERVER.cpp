// tcp_server.cpp
#include<iostream>
#include<string>
#include<winsock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

#define SERVER_PORT  6060  // 서버 포트
#define BUFSIZE 100  // 송수신 버퍼 크기

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "Winsock 초기화 오류" << endl;
        return -1;
    }

    /* 1. 소켓 생성 */
    SOCKET srvSocket;
    srvSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    /* 2. 소켓 구조체 변수 설정 */
    SOCKADDR_IN srvAddr;
    memset(&srvAddr, 0, sizeof(srvAddr));

    srvAddr.sin_family = AF_INET;
    srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    srvAddr.sin_port = htons(SERVER_PORT);

    /* 3. 바인딩 */
    bind(srvSocket, (SOCKADDR*)&srvAddr, sizeof(srvAddr));
    cout << "Binding OK..." << endl;

    /* 4. 리스닝, 클라이언트의 접속 요청을 기다리는 상태로 전환 */
    listen(srvSocket, 5);
    cout << "Listening OK..." << endl;

    /* 5. 접속해서 들어온 클라이언트 정보를 저장하기 위한 구조체 변수 */
    SOCKADDR_IN peerAddr;
    SOCKET hSocket;
    int cAddrLen = sizeof(peerAddr);

    /* 6. 클라이언트 접속 요청 수락 및 클라이언트 정보 저장 */
    hSocket = accept(srvSocket, (SOCKADDR*)&peerAddr, &cAddrLen);
    cout << "Client Accepted OK..." << endl;
    cout << "TCP Server running... " << endl;


    /* 7. 클라이언트에서 수신한 메시지 처리 */


    char recvMsg[BUFSIZE + 1] = "";
    // 메시지 수신
    int nRead = recv(hSocket, recvMsg, sizeof(recvMsg), 0);

    if (nRead == -1)
    {
        cout << "Receive Error: " << WSAGetLastError() << endl;
    }
    else
    {
        recvMsg[BUFSIZE] = '\0';
        cout << "\nReceived Message: " << recvMsg << endl;
    }

    /* 8. 소켓 종료 & 윈속 종료 */
    closesocket(hSocket);
    closesocket(srvSocket);
    WSACleanup();
    return 0;
}