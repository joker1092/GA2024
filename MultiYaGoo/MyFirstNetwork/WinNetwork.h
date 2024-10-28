#pragma once
#include "WinSocket.h"
#include "TCPSocket.h"
//https://docs.microsoft.com/en-us/cpp/cpp/explicitly-defaulted-and-deleted-functions?redirectedfrom=MSDN&view=msvc-170


_MYNETWORK_BEGIN

class WinNetwork
{
public:
	WinNetwork();
	~WinNetwork();

	bool Init();
	void CleanUp();

	WSADATA m_wsd;

private:
	WinNetwork(const WinNetwork&) = delete;
	WinNetwork& operator=(const WinNetwork&) = delete;

};

_MYNETWORK_END