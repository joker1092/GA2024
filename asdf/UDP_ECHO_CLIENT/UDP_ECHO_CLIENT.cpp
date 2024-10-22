// UDP 클라이언트 (블러킹 소켓)

#include <WinSock2.h> 
#include <ws2tcpip.h>
#include <string>
#include <iostream>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 7070 // 서버 포트 번호
#define SERVER_ADDR "127.0.0.1" // 서버 IP 주소
//#define SERVER_ADDR "172.21.1.32" // 서버 IP 주소 //용우
//#define SERVER_ADDR "172.21.1.35" // 서버 IP 주소 //세민
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

    if (inet_pton(AF_INET, SERVER_ADDR, &(srvAddr.sin_addr)) != 1)
    {
        cout << "Invalid IP address: " << WSAGetLastError() << endl;
    }
    else
    {
        cout << "UDP Client running " << endl;

        int sentSeq = 0;
        char sendBuf[BUFSIZE] = { 0, };
        int nSentPacketLimit = 10;
        int nSentPacketCount = 0;
        int nRecvPacketCount = 0;

        //blocking mode
        while (nSentPacketCount <= nSentPacketLimit)
        {
            memset(sendBuf, 0, BUFSIZE);

            if (nSentPacketCount == 0)
            {
                strcpy_s(sendBuf, "start*");
            }
            else if (nSentPacketCount == nSentPacketLimit)
            {
                strcpy_s(sendBuf, "end*");
            }
            else
            {
                sprintf_s(sendBuf, "seq*%d", ++sentSeq);
            }


            int nSent = sendto(hSocket, sendBuf, strnlen_s(sendBuf, BUFSIZE), 0, (SOCKADDR*)&srvAddr, sizeof(srvAddr));
            cout << sentSeq << " > Sent: " << nSent << " bytes" << endl;

            if (nSent == -1)
            {
                cout << "Send Error: " << WSAGetLastError() << endl;
                break;
            }

            nSentPacketCount++;

            Sleep(10);
        }

        while (nRecvPacketCount < nSentPacketCount)
        {
            char recvBuf[BUFSIZE] = { 0, };
            int nRecv = recvfrom(hSocket, recvBuf, BUFSIZE, 0, NULL, NULL);

            if (nRecv == -1)
            {
                cout << "Receive Error: " << WSAGetLastError() << endl;
                break;
            }

            cout << "Received: " << recvBuf << endl;

            nRecvPacketCount++;
        }

    }

    system("pause");

    /* 4. 소켓 종료 및 윈속 반환 */
    closesocket(hSocket);
    WSACleanup();


    return 0;
}