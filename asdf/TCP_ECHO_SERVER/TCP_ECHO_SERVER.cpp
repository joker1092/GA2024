//MSDN 샘플 코드를 일부 수정하여 테스트해 봅시다.
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <unordered_map>
#include "PacketHeader.h"

#pragma comment(lib, "ws2_32.lib")

#define PORT 6060
#define DATA_BUFSIZE 8192


typedef struct _SOCKET_INFORMATION {

    CHAR Buffer[DATA_BUFSIZE];
    WSABUF DataBuf;
    SOCKET Socket;
    DWORD BytesSEND;
    DWORD BytesRECV;
} SOCKET_INFORMATION, * LPSOCKET_INFORMATION;


BOOL CreateSocketInformation(SOCKET s);
void FreeSocketInformation(DWORD Event);


DWORD EventTotal = 0;
WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS];
LPSOCKET_INFORMATION SocketArray[WSA_MAXIMUM_WAIT_EVENTS];


void printPacketType(PacketType type);


typedef struct _SESSION {
    UINT SessionID;
    LPSOCKET_INFORMATION SocketInfo;
    time_t LastAccessTime;
} SESSION, * LPSESSION;

class SessionManager {
    public:
    std::unordered_map<UINT, LPSESSION> SessionMap;
    UINT SessionID = 0;
    int SessionTimeout = 60;
    WSABUF BroadcastBuffer;

    LPSESSION CreateSession(DWORD SessionID, LPSOCKET_INFORMATION SocketInfo) {
        LPSESSION session = new SESSION;
        session->SessionID = SessionID++;
        session->SocketInfo = SocketInfo;
        session->LastAccessTime = time(NULL);
        SessionMap[session->SessionID] = session;
        return session;
    }

    void DeleteSession(UINT SessionID) {
        auto it = SessionMap.find(SessionID);
        if (it != SessionMap.end()) {
            //shutdown(it->second->SocketInfo->Socket, SD_BOTH);
            FreeSocketInformation(it->second->SessionID);
            it = SessionMap.erase(it);
        }
    }

    LPSESSION FindSession(UINT SessionID) {
        auto it = SessionMap.find(SessionID);
        if (it != SessionMap.end()) {
            return it->second;
        }
        return nullptr;
    }

    LPSESSION FindByInfo(_SOCKET_INFORMATION* SocketInfo) {
        for (auto& it : SessionMap) {
            if (it.second->SocketInfo == SocketInfo) {
                return it.second;
            }
        }
        return nullptr;
    }

    void UpdateSessionTime(UINT SessionID) {
        auto it = SessionMap.find(SessionID);
        if (it != SessionMap.end()) {
            std::cout<< "Update session Last " << it->second->LastAccessTime << "to " << time(NULL) <<std::endl;
            it->second->LastAccessTime = time(NULL);
        }
    }

    void CheckSessionTimeout() {
        std::cout << "CheckSessionTimeout" << std::endl;
        time_t currentTime = time(NULL);

        const char* msg = "Session Timeout Disconected";
        DWORD SendBytes;
        WSABUF DataBuf;

        for (auto it = SessionMap.begin(); it != SessionMap.end(); ) {
            if (currentTime - it->second->LastAccessTime > SessionTimeout) {
                std::cout << "Session Timeout" << std::endl;

                DataBuf.buf = (char*)msg;
                DataBuf.len = strlen(msg);

                if (WSASend(it->second->SocketInfo->Socket, &DataBuf, 1, &SendBytes, 0, NULL, NULL) == SOCKET_ERROR)
                {
                    if (WSAGetLastError() != WSAEWOULDBLOCK)
                    {
                        printf("WSASend() failed with error %d\n", WSAGetLastError());
                        FreeSocketInformation(it->second->SessionID);
                        return;
                    }
                }
                else
                {
                    printf("Send Disconnet Messege currunt :  %d\n", (UINT)currentTime);
                }

                shutdown(it->second->SocketInfo->Socket, SD_BOTH);
                FreeSocketInformation(it->second->SessionID);
                it = SessionMap.erase(it);
            }
            else {
                it++;
            }
        }
    }

    void BroadCast(SESSION* sender,char* data,ULONG len) {
        for (auto it = SessionMap.begin(); it != SessionMap.end(); it++) {
            PacketC2S_Chat packet = *(PacketC2S_Chat*)data;
            
            PacketS2C_Chat* sendPacket = new PacketS2C_Chat();
            sendPacket->id = sender->SessionID;
            memcpy_s(sendPacket->msg, sizeof(sendPacket->msg), packet.msg, sizeof(packet.msg));
            sendPacket->timestamp = time(NULL);
            
            BroadcastBuffer.buf = (char*)sendPacket;
            BroadcastBuffer.len = sendPacket->len;

            DWORD SendBytes;
            if (WSASend(it->second->SocketInfo->Socket, &BroadcastBuffer, 1, &SendBytes, 0, NULL, NULL) == SOCKET_ERROR)
            {
                if (WSAGetLastError() != WSAEWOULDBLOCK)
                {
                    printf("WSASend() failed with error %d\n", WSAGetLastError());
                    FreeSocketInformation(it->second->SessionID);
                    return;
                }
            }
            else
            {
                printf("Send BroadCast Messege currunt :  %d\n", (UINT)time(NULL));
            }
            delete sendPacket;
        }
    }
    
};


int main(int argc, char** argv)
{
    SOCKET Listen;
    SOCKET Accept;
    SOCKADDR_IN InternetAddr;
    LPSOCKET_INFORMATION SocketInfo;

    DWORD Event;
    WSANETWORKEVENTS NetworkEvents;
    WSADATA wsaData;
    DWORD Flags;
    DWORD RecvBytes;
    DWORD SendBytes;

    LPSESSION session = nullptr;
    // Session Manager
    SessionManager sessionManager;

    if (WSAStartup(0x0202, &wsaData) != 0)
    {
        printf("WSAStartup() failed with error %d\n", WSAGetLastError());
        return 1;
    }
    else
        printf("WSAStartup() is OK!\n");

    if ((Listen = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("socket() failed with error %d\n", WSAGetLastError());
        return 1;
    }
    else
        printf("socket() is OK!\n");


    if (CreateSocketInformation(Listen) == FALSE)
        printf("CreateSocketInformation() failed!\n");
    else
        printf("CreateSocketInformation() is OK lol!\n");

    if (WSAEventSelect(Listen, EventArray[EventTotal - 1], FD_ACCEPT | FD_CLOSE) == SOCKET_ERROR)
    {
        printf("WSAEventSelect() failed with error %d\n", WSAGetLastError());
        return 1;
    }
    else
        printf("WSAEventSelect() is pretty fine!\n");


    InternetAddr.sin_family = AF_INET;
    InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    InternetAddr.sin_port = htons(PORT);

    if (bind(Listen, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
    {
        printf("bind() failed with error %d\n", WSAGetLastError());
        return 1;
    }
    else
        printf("bind() is OK!\n");


    if (listen(Listen, 5))
    {
        printf("listen() failed with error %d\n", WSAGetLastError());
        return 1;
    }
    else
        printf("listen() is OK!\n");


    while (TRUE)
    {
        sessionManager.CheckSessionTimeout();
        // Wait for one of the sockets to receive I/O notification and
        //if ((Event = WSAWaitForMultipleEvents(EventTotal, EventArray, FALSE, WSA_INFINITE, FALSE)) == WSA_WAIT_FAILED)
        if ((Event = WSAWaitForMultipleEvents(EventTotal, EventArray, FALSE, 1000, FALSE)) == WSA_WAIT_FAILED)
        {
            // Event == 배열의 인덱스
            printf("WSAWaitForMultipleEvents() failed with error %d\n", WSAGetLastError());
            return 1;
        }
        else
            printf("WSAWaitForMultipleEvents() is pretty damn OK!\n");

        

        if(SocketArray[Event - WSA_WAIT_EVENT_0] == nullptr) {
            std::cout << "Not Accept Socket" << std::endl;
            continue;
        }

        if (EventArray[Event - WSA_WAIT_EVENT_0] == nullptr)
        {
            std::cout << "WSAWaitForMultipleEvents Not Event" << std::endl;
            continue;
        }

        if (WSAEnumNetworkEvents(SocketArray[Event - WSA_WAIT_EVENT_0]->Socket,
            EventArray[Event - WSA_WAIT_EVENT_0], &NetworkEvents) == SOCKET_ERROR)
        {
            printf("WSAEnumNetworkEvents() failed with error %d\n", WSAGetLastError());
            return 1;
        }
        else
            printf("WSAEnumNetworkEvents() should be fine!\n");

        session = sessionManager.FindByInfo(SocketArray[Event - WSA_WAIT_EVENT_0]);

        if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
        {
            if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
            {
                printf("FD_ACCEPT failed with error %d\n", NetworkEvents.iErrorCode[FD_ACCEPT_BIT]);
                break;
            }

            if ((Accept = accept(SocketArray[Event - WSA_WAIT_EVENT_0]->Socket, NULL, NULL)) == INVALID_SOCKET)
            {
                printf("accept() failed with error %d\n", WSAGetLastError());
                break;
            }
            else
                printf("accept() should be OK!\n");

            if (EventTotal > WSA_MAXIMUM_WAIT_EVENTS)
            {
                printf("Too many connections - closing socket...\n");
                closesocket(Accept);
                break;
            }

            CreateSocketInformation(Accept);

            if (WSAEventSelect(Accept, EventArray[EventTotal - 1], FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
            {
                printf("WSAEventSelect() failed with error %d\n", WSAGetLastError());
                return 1;
            }
            else
                printf("WSAEventSelect() is OK!\n");

            printf("Socket %d got connected...\n", (int)Accept);

            
            
            if (session == nullptr) {
            // Create a session
                session = sessionManager.CreateSession(EventTotal - 1,SocketArray[EventTotal - 1]);
            }
            
        }

        // Try to read and write data to and from the data buffer if read and write events occur

        if (NetworkEvents.lNetworkEvents & FD_READ || NetworkEvents.lNetworkEvents & FD_WRITE)
        {

            if (NetworkEvents.lNetworkEvents & FD_READ && NetworkEvents.iErrorCode[FD_READ_BIT] != 0)
            {
                printf("FD_READ failed with error %d\n", NetworkEvents.iErrorCode[FD_READ_BIT]);
                break;
            }
            else
                printf("FD_READ is OK!\n");


            if (NetworkEvents.lNetworkEvents & FD_WRITE && NetworkEvents.iErrorCode[FD_WRITE_BIT] != 0)
            {
                printf("FD_WRITE failed with error %d\n", NetworkEvents.iErrorCode[FD_WRITE_BIT]);

                break;
            }
            else
                printf("FD_WRITE is OK!\n");

            SocketInfo = SocketArray[Event - WSA_WAIT_EVENT_0];

            // Read data only if the receive buffer is empty
            if (SocketInfo->BytesRECV == 0)
            {
                SocketInfo->DataBuf.buf = SocketInfo->Buffer;
                SocketInfo->DataBuf.len = DATA_BUFSIZE;

                Flags = 0;

                if (WSARecv(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &RecvBytes, &Flags, NULL, NULL) == SOCKET_ERROR)
                {
                    if (WSAGetLastError() != WSAEWOULDBLOCK)
                    {
                        printf("WSARecv() failed with error %d\n", WSAGetLastError());
                        FreeSocketInformation(Event - WSA_WAIT_EVENT_0);
                        return 1;
                    }
                }
                else
                {
                    printf("[%d] WSARecv() is working!\n", RecvBytes);
                    SocketInfo->BytesRECV = RecvBytes;
                }
            }


            // Broadcast data
            if (SocketInfo->BytesRECV > 0)
            {
                SESSION* sender = sessionManager.FindByInfo(SocketInfo);
                PacketType packetType = ((PacketHeader*)SocketInfo->Buffer)->type;
                printPacketType(packetType);
                switch (packetType)
                {
                case PacketType::C2S_ECHO:
                    break;
                case PacketType::C2S_CONNECT:
                    break;
                case PacketType::C2S_DISCONNECT:
                    break;
                case PacketType::C2S_CHAT:
                    sessionManager.BroadCast(sender,SocketInfo->Buffer, SocketInfo->BytesRECV);
                    SocketInfo->BytesRECV = 0;
                    break;
                case PacketType::HEADER_COUNT:
                    break;
                }
                
            }

            //Old Echo
            //// Write buffer data if it is available
            //if (SocketInfo->BytesRECV > SocketInfo->BytesSEND)
            //{
            //    SocketInfo->DataBuf.buf = SocketInfo->Buffer + SocketInfo->BytesSEND;
            //    SocketInfo->DataBuf.len = SocketInfo->BytesRECV - SocketInfo->BytesSEND;

            //    if (WSASend(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &SendBytes, 0, NULL, NULL) == SOCKET_ERROR)
            //    {
            //        if (WSAGetLastError() != WSAEWOULDBLOCK)
            //        {
            //            printf("WSASend() failed with error %d\n", WSAGetLastError());
            //            FreeSocketInformation(Event - WSA_WAIT_EVENT_0);
            //            return 1;
            //        }

            //        // A WSAEWOULDBLOCK error has occurred. An FD_WRITE event will be posted
            //        // when more buffer space becomes available
            //    }
            //    else
            //    {
            //        SocketInfo->BytesSEND += SendBytes;
            //        printf("[%d] WSASend() is fine! Thank you...\n", SocketInfo->BytesSEND);

            //        if (SocketInfo->BytesSEND == SocketInfo->BytesRECV)
            //        {
            //            SocketInfo->BytesSEND = 0;
            //            SocketInfo->BytesRECV = 0;
            //        }
            //    }
            //}
            // Update session time
            if (session)
            {
                sessionManager.UpdateSessionTime(session->SessionID);
            }
        }

        

        if (NetworkEvents.lNetworkEvents & FD_CLOSE)
        {
            if (NetworkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
            {
                printf("FD_CLOSE failed with error %d\n", NetworkEvents.iErrorCode[FD_CLOSE_BIT]);
                //break;
            }
            else
                printf("FD_CLOSE is OK!\n");

            printf("Closing socket information %d\n", (int)SocketArray[Event - WSA_WAIT_EVENT_0]->Socket);
            sessionManager.DeleteSession(session->SessionID);
            //FreeSocketInformation(Event - WSA_WAIT_EVENT_0);
        }
    }

    return 0;
}


BOOL CreateSocketInformation(SOCKET s)
{
    LPSOCKET_INFORMATION SI;

    if ((EventArray[EventTotal] = WSACreateEvent()) == WSA_INVALID_EVENT)
    {
        printf("WSACreateEvent() failed with error %d\n", WSAGetLastError());
        return FALSE;
    }
    else
        printf("WSACreateEvent() is OK!\n");

    if ((SI = (LPSOCKET_INFORMATION)GlobalAlloc(GPTR, sizeof(SOCKET_INFORMATION))) == NULL)
    {
        printf("GlobalAlloc() failed with error %d\n", GetLastError());
        return FALSE;
    }
    else
        printf("GlobalAlloc() for LPSOCKET_INFORMATION is OK!\n");

    // Prepare SocketInfo structure for use

    SI->Socket = s;
    SI->BytesSEND = 0;
    SI->BytesRECV = 0;

    SocketArray[EventTotal] = SI;
    EventTotal++;
    return(TRUE);
}


void FreeSocketInformation(DWORD Event)
{
    LPSOCKET_INFORMATION SI = SocketArray[Event];
    DWORD i;

    closesocket(SI->Socket);
    GlobalFree(SI);

    if (WSACloseEvent(EventArray[Event]) == TRUE)
        printf("WSACloseEvent() is OK!\n\n");
    else
        printf("WSACloseEvent() failed miserably!\n\n");

    // Squash the socket and event arrays

    for (i = Event; i < EventTotal; i++)
    {
        EventArray[i] = EventArray[i + 1];
        SocketArray[i] = SocketArray[i + 1];
    }

    EventTotal--;
}


void printPacketType(PacketType type) {
    switch (type) {
    case PacketType::C2S_ECHO:
        printf("C2S_ECHO\n");
        break;
    case PacketType::S2C_ECHO:
        printf("S2C_ECHO\n");
        break;
    case PacketType::C2S_CONNECT:
        printf("C2S_CONNECT\n");
        break;
    case PacketType::S2C_CONNECT:
        printf("S2C_CONNECT\n");
        break;
    case PacketType::C2S_DISCONNECT:
        printf("C2S_DISCONNECT\n");
        break;
    case PacketType::S2C_DISCONNECT:
        printf("S2C_DISCONNECT\n");
        break;
    case PacketType::C2S_CHAT:
        printf("C2S_CHAT\n");
        break;
    case PacketType::S2C_CHAT:
        printf("S2C_CHAT\n");
        break;
    case PacketType::S2C_TIME_OUT:
        printf("S2C_TIME_OUT\n");
        break;
    case PacketType::HEADER_COUNT:
        printf("HEADER_COUNT\n");
        break;
    }
}