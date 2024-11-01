#pragma once
enum class PacketType : short
{
    C2S_ECHO = 0,    // 클라이언트 -> 서버 에코
    S2C_ECHO,        // 서버 -> 클라이언트 에코

    C2S_CONNECT,     // 클라이언트 -> 서버 연결 요청
    S2C_CONNECT,     // 서버 -> 클라이언트 연결 성공

    C2S_DISCONNECT,  // 클라이언트 -> 서버 연결 해제
    S2C_DISCONNECT,  // 서버 -> 클라이언트 연결 해제

    C2S_CHAT,        // 클라이언트 -> 서버 채팅 ==>브로드케스트 요청
    S2C_CHAT,        // 서버 -> 클라이언트 채팅 ==>브로드케스트된 메시지

    S2C_TIME_OUT,    // 서버 -> 클라이언트 타임아웃

    HEADER_COUNT     // 패킷 타입 개수
};

#pragma pack(push, 1)
struct PacketHeader
{
    short len;
    PacketType type;
};

struct PacketC2S_Echo : public PacketHeader
{
    PacketC2S_Echo() {
        len = sizeof(PacketC2S_Echo);
        type = PacketType::C2S_ECHO;
    }
    __int64 timestamp;
};

struct PacketS2C_Echo : public PacketHeader
{
    PacketS2C_Echo() {
        len = sizeof(PacketS2C_Echo);
        type = PacketType::S2C_ECHO;
    }
    __int64 timestamp;
};

struct PacketC2S_Connect : public PacketHeader
{
    PacketC2S_Connect() {
        len = sizeof(PacketC2S_Connect);
        type = PacketType::C2S_CONNECT;
    }
};

struct PacketS2C_Connect : public PacketHeader
{
    PacketS2C_Connect() {
        len = sizeof(PacketS2C_Connect);
        type = PacketType::S2C_CONNECT;
    }
};

struct PacketC2S_Disconnect : public PacketHeader
{
    PacketC2S_Disconnect() {
        len = sizeof(PacketC2S_Disconnect);
        type = PacketType::C2S_DISCONNECT;
    }
};

struct PacketS2C_Disconnect : public PacketHeader
{
    PacketS2C_Disconnect() {
        len = sizeof(PacketS2C_Disconnect);
        type = PacketType::S2C_DISCONNECT;
    }
};

struct PacketC2S_Chat : public PacketHeader
{
    PacketC2S_Chat() {
        len = sizeof(PacketC2S_Chat);
        type = PacketType::C2S_CHAT;
    }
    char msg[256];
};

struct PacketS2C_Chat : public PacketHeader
{
    PacketS2C_Chat() {
        len = sizeof(PacketS2C_Chat);
        type = PacketType::S2C_CHAT;
    }
    __int64 id;
    char msg[256];
    __int64 timestamp;
};

struct PacketS2C_TimeOut : public PacketHeader
{
    PacketS2C_TimeOut() {
        len = sizeof(PacketS2C_TimeOut);
        type = PacketType::S2C_TIME_OUT;
    }
};