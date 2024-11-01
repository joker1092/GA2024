#pragma once
enum class PacketType : short
{
    C2S_ECHO = 0,    // Ŭ���̾�Ʈ -> ���� ����
    S2C_ECHO,        // ���� -> Ŭ���̾�Ʈ ����

    C2S_CONNECT,     // Ŭ���̾�Ʈ -> ���� ���� ��û
    S2C_CONNECT,     // ���� -> Ŭ���̾�Ʈ ���� ����

    C2S_DISCONNECT,  // Ŭ���̾�Ʈ -> ���� ���� ����
    S2C_DISCONNECT,  // ���� -> Ŭ���̾�Ʈ ���� ����

    C2S_CHAT,        // Ŭ���̾�Ʈ -> ���� ä�� ==>��ε��ɽ�Ʈ ��û
    S2C_CHAT,        // ���� -> Ŭ���̾�Ʈ ä�� ==>��ε��ɽ�Ʈ�� �޽���

    S2C_TIME_OUT,    // ���� -> Ŭ���̾�Ʈ Ÿ�Ӿƿ�

    HEADER_COUNT     // ��Ŷ Ÿ�� ����
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