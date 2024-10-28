// LibraryTest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <time.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>


// 경로와 종속성 체크
#include "..\\MyFirstNetwork\\WinNetwork.h"
#include "..\\MyFirstNetwork\\DebugUtils.h"
#include "..\\MyFirstNetwork\\ExceptionFilter.h"


#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\MyFirstNetwork.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\MyFirstNetwork.lib")
#endif

#define RCVPORT 5252
#define DATA_BUFSIZE 1024
#define PACKET_SIZE_MAX 256

simsim::WinNetwork GWinNet;
simsim::WinSocket Receiver;
simsim::WinSocket Sender;
//mynet::WinSocket Connector;
simsim::TCPSocket Connector(1024, 1024);

char sndBuf[DATA_BUFSIZE] = "";
char rcvBuf[DATA_BUFSIZE] = "";

char packetBuf[PACKET_SIZE_MAX] = "";

//SnailProject 와 테스트 해보려고 ...
enum class PACKET_ID : INT16
{
    ECHO = 1,
    BROADCAST
};

#pragma pack(push, 1)
struct PACKET_HEADER
{
    INT16 packet_size;
    INT16 packet_id;
    INT8 seqNum;
};

// 테스트 패킷
struct PACKET_DEV : PACKET_HEADER
{
    static const int PACKET_DEV_BUF_SIZE_MAX = 256;

    INT8 buffer[PACKET_DEV_BUF_SIZE_MAX];
};

#pragma pack(pop)

static const int PACKET_HEADER_SIZE = sizeof(PACKET_HEADER);
PACKET_DEV& GetTestPacketForSend(PACKET_ID id, void* pData, const int nData)
{
    static PACKET_DEV testPacket;
    static int seq = 0;

    testPacket.packet_size = PACKET_HEADER_SIZE + nData;
    testPacket.packet_id = static_cast<INT16>(id);
    testPacket.seqNum = ++seq;

    memcpy(testPacket.buffer, pData, static_cast<size_t>(PACKET_HEADER_SIZE + nData));

    return testPacket;
}

void PrintErrorMessage(const char* pmsg)
{
    printf("[ERROR:%d] %s\n", WSAGetLastError(), pmsg);
}

void CheckOption(SOCKET s)
{
    int option;
    socklen_t length = sizeof(option);
    if (getsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&option, &length) == -1)
    {
        PrintErrorMessage("getsockopt");
        return;
    }

    printf("send buffer size : %d\n", option);

    if (getsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&option, &length) == -1)
    {
        PrintErrorMessage("getsockopt");
        return;
    }

    printf("recv buffer size : %d\n", option);

}

void UDPSoketTest(const char peerIP[], const int peerPort, const char localIP[], const int localPort)
{
    std::cout << "UDPSoketTest! \n";

    if (false == Receiver.Open(IPPROTO_UDP))
    {
        PrintErrorMessage("Receiver.Open");
        return;
    }

    // 옵션 체크
    CheckOption(Receiver.GetHandle());

    SOCKADDR_IN RecvAddr;
    RecvAddr.sin_family = AF_INET;
    InetPtonA(AF_INET, localIP, &RecvAddr.sin_addr);
    RecvAddr.sin_port = htons(localPort);
    Receiver.Bind(RecvAddr);

    if (false == Sender.Open(IPPROTO_UDP))
    {
        PrintErrorMessage("Sender.Open");
        return;
    }

    SOCKADDR_IN PeerAddr;
    PeerAddr.sin_family = AF_INET;
    InetPtonA(AF_INET, peerIP, &PeerAddr.sin_addr);
    PeerAddr.sin_port = htons(peerPort);


    SOCKADDR_IN FromAddr;

    int error = 0;
    int count = 0;
    char fromStrIP[32] = "";

    printf("Recv %s:%d  Send %s:%d\n", localIP, localPort, peerIP, peerPort);
    while (true)
    {
        sprintf_s(sndBuf, "Seq. %d\n", ++count);

        if (Sender.SendTo(sndBuf, DATA_BUFSIZE, error, PeerAddr) < 0)
        {
            PrintErrorMessage("Send Error");
            break;
        }
        else
        {
            printf("--------------------------------> I Sent %s", sndBuf);
        }

        if (Receiver.RecvFrom(rcvBuf, DATA_BUFSIZE, error, FromAddr) < 0)
        {
            PrintErrorMessage("Recv Error");
            break;
        }
        else
        {
            InetNtopA(AF_INET, &FromAddr.sin_addr, fromStrIP, sizeof(fromStrIP));
            printf("[%s %d] %s", fromStrIP, FromAddr.sin_port, rcvBuf);
        }

        Sleep(1000);
    }
}


void UDPSoketTest_Sender(const char peerIP[], const int peerPort)
{
    std::cout << "UDPSoketTest_Sender! \n";

    if (false == Sender.Open(IPPROTO_UDP))
    {
        PrintErrorMessage("Sender.Open");
        return;
    }


    SOCKADDR_IN PeerAddr;
    PeerAddr.sin_family = AF_INET;
    InetPtonA(AF_INET, peerIP, &PeerAddr.sin_addr);
    PeerAddr.sin_port = htons(peerPort);

    int error = 0;
    int count = 0;
    char fromStrIP[32] = "";

    printf("Send To %s:%d\n", peerIP, peerPort);
    while (true)
    {
        sprintf_s(sndBuf, "Seq. %d\n", ++count);

        if (Sender.SendTo(sndBuf, DATA_BUFSIZE, error, PeerAddr) < 0)
        {
            PrintErrorMessage("Send Error");
            break;
        }
        else
        {
            printf("--------------------------------> I Sent %s", sndBuf);
        }

        Sleep(1000);
        //if (0 == (count % 10)) Sleep(1000);
    }
}

void UDPSoketTest_Receiver(const char localIP[], const int localPort)
{
    std::cout << "UDPSoketTest_Receiver! \n";

    if (false == Receiver.Open(IPPROTO_UDP))
    {
        PrintErrorMessage("Receiver.Open");
        return;
    }


    SOCKADDR_IN RecvAddr;
    RecvAddr.sin_family = AF_INET;
    InetPtonA(AF_INET, localIP, &RecvAddr.sin_addr);
    RecvAddr.sin_port = htons(localPort);
    Receiver.Bind(RecvAddr);

    if (false == Sender.Open(IPPROTO_UDP))
    {
        PrintErrorMessage("Sender.Open");
        return;
    }


    SOCKADDR_IN FromAddr;

    int error = 0;
    int count = 0;
    char fromStrIP[32] = "";

    printf("Recv At. %s:%d \n", localIP, localPort);
    while (true)
    {
        if (Receiver.RecvFrom(rcvBuf, DATA_BUFSIZE, error, FromAddr) < 0)
        {
            PrintErrorMessage("Recv Error");
            break;
        }
        else
        {
            InetNtopA(AF_INET, &FromAddr.sin_addr, fromStrIP, sizeof(fromStrIP));
            printf("[%s %d] %s", fromStrIP, FromAddr.sin_port, rcvBuf);
        }
    }
}

void TCPSocketTest_Connector(const char serverIP[], const int serverPort)
{
    std::cout << "TCPSocketTest_Connector! \n";

    if (false == Connector.Open(IPPROTO_TCP))
    {
        PrintErrorMessage("Connector.Open");
        return;
    }

    // 옵션 체크
    CheckOption(Connector.GetHandle());

    SOCKADDR_IN ServerAddr;
    ServerAddr.sin_family = AF_INET;
    InetPtonA(AF_INET, serverIP, &ServerAddr.sin_addr);
    ServerAddr.sin_port = htons(serverPort);

    Sleep(1000);
    if (false == Connector.Connect(ServerAddr))
    {
        PrintErrorMessage("Connector.Connect");
        return;
    }

    int ret = 0;
    int error = 0;
    int sent = 0, recv = 0;
    int count = 0;
    char fromStrIP[32] = "";

    printf("Connected %s:%d\n", serverIP, serverPort);

    UINT64 nowTickCnt = 0LL;
    UINT64 rcvTickCnt = 0LL;
    UINT64 sndTickCnt = 0LL;

    PACKET_HEADER PacketHeader;
    PACKET_DEV PacketRcved;
    while (true)
    {
        nowTickCnt = GetTickCount64();

        if (nowTickCnt < 3000 + sndTickCnt) continue; // 정신 사납다. 3초 마다 보내기로 하자.

        sndTickCnt = nowTickCnt;
        PACKET_DEV& sndPacket = GetTestPacketForSend(PACKET_ID::ECHO, &sndTickCnt, sizeof(sndTickCnt));

        if (Connector.PostPacket((char*)&sndPacket, sndPacket.packet_size))
        {
            Connector.SendUpdate();
        }
        else
        {
            printf("송신 실패");
        }

        Connector.RecvUpdate();

        printf("---------------------------------------------------------\n");
        while (Connector.PeekPacket(reinterpret_cast<char*>(&PacketHeader), PACKET_HEADER_SIZE))
        {
            // 온전한 패킷이 있다면 패킷을 만들어서 처리.
            memset(&PacketRcved, 0, sizeof(PacketRcved));
            if (Connector.ReadPacket(reinterpret_cast<char*>(&PacketRcved), PacketHeader.packet_size))
            {
                switch (PacketHeader.packet_id)
                {
                case static_cast<INT16>(PACKET_ID::ECHO):
                case static_cast<INT16>(PACKET_ID::BROADCAST):
                {
                    nowTickCnt = GetTickCount64();

                    memcpy(&rcvTickCnt, PacketRcved.buffer, sizeof(rcvTickCnt));

                    printf("Recv. [ %u ] %d\n", PacketRcved.seqNum, static_cast<int>(nowTickCnt - rcvTickCnt));
                }
                break;
                default:
                    printf("Unknown Packet! %d, size %d\n", PacketHeader.packet_id, PacketHeader.packet_size);
                }
            }
            else
            {
                printf("Connector.ReadPacket return false! \n");
                break;
            }
        }

    }
}



int main(int argc, char* argv[])
{
    SetUnhandledExceptionFilter(MyExceptionFilter);

    if (false == GWinNet.Init())
    {
        PrintErrorMessage("GWinNet.Init");
    }

    int localPort, peerPort;
    if (argc == 5)
    {
        localPort = std::stoi(argv[2]);
        peerPort = std::stoi(argv[4]);

        UDPSoketTest(argv[1], localPort, argv[3], peerPort);
    }
    else if (argc == 4)
    {
        int port = std::stoi(argv[3]);

        if (*argv[1] == 's' || *argv[1] == 'S')
        {
            UDPSoketTest_Sender(argv[2], port);
        }
        else if (*argv[1] == 'r' || *argv[1] == 'R')
        {
            UDPSoketTest_Receiver(argv[2], port);
        }
        else if (*argv[1] == 'c' || *argv[1] == 'C') //TCP 커넥터
        {
            TCPSocketTest_Connector(argv[2], port);
        }
        else
        {
            printf("wrong arg\n");
        }
    }
    else
    {
        UDPSoketTest("127.0.0.1", RCVPORT, "127.0.0.1", RCVPORT);
    }

}

