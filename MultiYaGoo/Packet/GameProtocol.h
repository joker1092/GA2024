#pragma once

// 프로토콜은 일단, 시작을 할 수 있도록 예를 들어 준 것입니다.
// 필요에 따라 추가하거나 수정하셔도 됩니다.
enum class PacketType : short
{
    C2S_ECHO = 0, // 클라이언트에서 서버로 에코 요청 - 테스트 목적
    S2C_ECHO,
    
    C2S_LOGIN,  // 아이디 중복만 아니면 허용해 줍시다.
    S2C_LOGIN,
    
    C2S_LOGOUT,
    S2C_LOGOUT,

    S2C_USER_LIST,  // 접속한 유저에게 기존 접속되었던 유저 리스트를 보내줍니다.
    S2C_USER_ENTER, // 다른 유저가 접속했을 때
    S2C_USER_LEAVE, // 다른 유저가 접속을 끊었을 때

    C2S_CHAT,
    S2C_CHAT,

    C2S_GAME_START, // 게임 시작 요청, 방장 개념이 없으므로 모두가 해당 패킷을 보내면 게임이 시작됩니다.
    S2C_GAME_START, // 게임 시작
    C2S_TRY_NUMBERS, // 4자리 숫자 시도
    S2C_TRY_NUMBERS, // 각 유저가  시도했다는 것을 알림, 시도한 숫자는 보여주지 않음
    S2C_TIME_OUT, // 시간이 초과되었을 때 -> 탈락.
 
    S2C_RESULT_ANSWER, // CAT: 1234,0S2B, 2B2S 등
    S2C_GAME_RESULT,    // 게임 결과를 알려줍니다. 

    // 야구 게임 룰 정하고 프로토콜을 추가해 봅시다.
};

//* 1바이트 단위 패킹은 간단하고 빠르지만 단점도 있습니다.
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

    __int64 timestamp; // 클라가 준 것 그대로 돌려 줌
};

// 패킷을 정의 해보세요.

#pragma pack(pop)