#pragma once

// ���������� �ϴ�, ������ �� �� �ֵ��� ���� ��� �� ���Դϴ�.
// �ʿ信 ���� �߰��ϰų� �����ϼŵ� �˴ϴ�.
enum class PacketType : short
{
    C2S_ECHO = 0, // Ŭ���̾�Ʈ���� ������ ���� ��û - �׽�Ʈ ����
    S2C_ECHO,
    
    C2S_LOGIN,  // ���̵� �ߺ��� �ƴϸ� ����� �ݽô�.
    S2C_LOGIN,
    
    C2S_LOGOUT,
    S2C_LOGOUT,

    S2C_USER_LIST,  // ������ �������� ���� ���ӵǾ��� ���� ����Ʈ�� �����ݴϴ�.
    S2C_USER_ENTER, // �ٸ� ������ �������� ��
    S2C_USER_LEAVE, // �ٸ� ������ ������ ������ ��

    C2S_CHAT,
    S2C_CHAT,

    C2S_GAME_START, // ���� ���� ��û, ���� ������ �����Ƿ� ��ΰ� �ش� ��Ŷ�� ������ ������ ���۵˴ϴ�.
    S2C_GAME_START, // ���� ����
    C2S_TRY_NUMBERS, // 4�ڸ� ���� �õ�
    S2C_TRY_NUMBERS, // �� ������  �õ��ߴٴ� ���� �˸�, �õ��� ���ڴ� �������� ����
    S2C_TIME_OUT, // �ð��� �ʰ��Ǿ��� �� -> Ż��.
 
    S2C_RESULT_ANSWER, // CAT: 1234,0S2B, 2B2S ��
    S2C_GAME_RESULT,    // ���� ����� �˷��ݴϴ�. 

    // �߱� ���� �� ���ϰ� ���������� �߰��� ���ô�.
};

//* 1����Ʈ ���� ��ŷ�� �����ϰ� �������� ������ �ֽ��ϴ�.
#pragma pack(push, 1)
struct PacketHeader
{
    short len;
    PacketType type;
};

struct PacketC2S_Echo : public PacketHeader
{
    PacketC2S_Echo()
    {
        len = sizeof(PacketC2S_Echo);
        type = PacketType::C2S_ECHO;
    }

    __int64 timestamp;  
};


class  PacketS2C_Echo : public PacketHeader
{
    PacketS2C_Echo()
    {
        len = sizeof(PacketS2C_Echo);
        type = PacketType::S2C_ECHO;
    }

    __int64 timestamp; // Ŭ�� �� �� �״�� ���� ��
};

// ��Ŷ�� ���� �غ�����.

#pragma pack(pop)