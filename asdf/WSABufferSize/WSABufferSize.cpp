#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;

    int recvBuffSize, sendBuffSize;
    int optLen = sizeof(int);

    // 초기화
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // 소켓 생성
    SOCKET udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    SOCKET tcpSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 수신 버퍼 크기 확인
    recvBuffSize = 0;
    getsockopt(udpSocket, SOL_SOCKET, SO_RCVBUF, (char*)&recvBuffSize, &optLen);
    printf("UDP 수신 버퍼 크기: %d\n", recvBuffSize);

    recvBuffSize = 0;
    getsockopt(tcpSocket, SOL_SOCKET, SO_RCVBUF, (char*)&recvBuffSize, &optLen);
    printf("TCP 수신 버퍼 크기: %d\n", recvBuffSize);

    // 송신 버퍼 크기 확인
    sendBuffSize = 0;
    getsockopt(udpSocket, SOL_SOCKET, SO_SNDBUF, (char*)&sendBuffSize, &optLen);
    printf("UDP 송신 버퍼 크기: %d\n", sendBuffSize);

    sendBuffSize = 0;
    getsockopt(tcpSocket, SOL_SOCKET, SO_SNDBUF, (char*)&sendBuffSize, &optLen);
    printf("TCP 송신 버퍼 크기: %d\n", sendBuffSize);

    // 종료
    closesocket(udpSocket);
    closesocket(tcpSocket);

    WSACleanup();

    return 0;
}
