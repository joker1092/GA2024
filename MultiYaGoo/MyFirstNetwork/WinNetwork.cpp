#include "WinNetwork.h"

#pragma comment(lib, "Ws2_32.lib")

_MYNETWORK_BEGIN

WinNetwork::WinNetwork()
{
    memset(&m_wsd, 0, sizeof(m_wsd));
}


WinNetwork::~WinNetwork()
{

}

bool WinNetwork::Init()
{
    if (0 != WSAStartup(MAKEWORD(2, 2), &m_wsd))
    {
        return false;
    }

    return true;
}

void WinNetwork::CleanUp()
{
    WSACleanup();

}

_MYNETWORK_END