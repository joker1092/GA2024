// UDP 서버 (넌블러킹 소켓)

#include <WinSock2.h>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT  7070
#define BUFSIZE  100
//#define MAX_MSG 10

struct Msgblock {
    char Msgbuf[BUFSIZE + 1] = "";
};


struct Session {
    SOCKADDR_IN peerAddr;
    vector<Msgblock*> msgblockList;
    void release()
    {
        for (auto& m : msgblockList)
        {
            delete m;
        }
        msgblockList.clear();
    }
    void reverseBlock()
    {
        reverse(msgblockList.begin(), msgblockList.end());
    }
};

unsigned int HashFunc(const SOCKADDR_IN& addr)
{
    return addr.sin_addr.s_addr+ addr.sin_port;
}

int main()
{
    WSADATA wsaData;
    
    unordered_map<unsigned int, Session*> sessionMap = {};

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "Winsock 초기화 오류" << endl;
        return -1;
    }

    SOCKET srvSocket;
    srvSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    u_long iMode = 1;
    //u_long iMode = 0;
    int iResult = ioctlsocket(srvSocket, FIONBIO, &iMode);
    if (iResult != NO_ERROR)
        printf("ioctlsocket failed with error: %ld\n", iResult);

    SOCKADDR_IN srvAddr;
    memset(&srvAddr, 0, sizeof(srvAddr));

    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(SERVER_PORT);
    srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(srvSocket, (SOCKADDR*)&srvAddr, sizeof(srvAddr));

    cout << "Binding OK..." << endl;
    cout << "UDP Server running... " << endl;

    SOCKADDR_IN peerAddr;
    int nAddrSize = sizeof(peerAddr);
    char recvMsg[BUFSIZE + 1] = "";

    int nError = 0;

    while (true)
    {
        int nRecv = recvfrom(srvSocket, recvMsg, sizeof(recvMsg), 0,
            (SOCKADDR*)&peerAddr, &nAddrSize);
        if (nRecv > 0)
        {
            int index = min(nRecv, BUFSIZE);
            recvMsg[nRecv] = '\0';

            unsigned int key =  HashFunc(peerAddr);
            auto iter = sessionMap.find(key);
            
            Session* pSession = nullptr;
            if (iter == sessionMap.end())
            {
                pSession = new Session();
                pSession->peerAddr = peerAddr;
                sessionMap.insert(make_pair(key, pSession));
            }
            else {
                pSession = iter->second;
            }

            Msgblock* pMsgblock = new Msgblock();
            strcat_s(pMsgblock->Msgbuf, recvMsg);
            pSession->msgblockList.push_back(pMsgblock);
            cout << "Client : " << recvMsg << endl;
            /*cout << "pSession Msgbuf: " << "";
            for (auto& msg : pSession->msgblockList)
            {
                cout << msg->Msgbuf << " ";
            }
            cout  << endl;*/

            if (!strcmp(recvMsg, "end*")) {
                pSession->reverseBlock();    
                for (auto& msg : pSession->msgblockList)
                {
                    int send = sendto(srvSocket, msg->Msgbuf, strlen(msg->Msgbuf), 0,
                        (SOCKADDR*)&pSession->peerAddr, nAddrSize);
                    cout << "Send: "<< msg->Msgbuf <<" "<< send << " bytes" << endl;
                }
                pSession->release();
            }

            /*sendto(srvSocket, recvMsg, nRecv, 0,
                (SOCKADDR*)&peerAddr, nAddrSize);*/
        }
        else
        {
            nError = WSAGetLastError();
            if (nError != WSAEWOULDBLOCK)
            {
                cout << "Error Code : " << nError << endl;
                break;
            }
        }

    }

    
    for(auto& s : sessionMap)
    {
        s.second->release();
        delete s.second;
    }
    sessionMap.clear();
    closesocket(srvSocket);
    WSACleanup();

    return 0;
}



