#pragma once
#include <string>
#include <vector>
#include "CommonDefines.h"


_MYNETWORK_BEGIN

class Datagram
{
public:
	char		packetBuf[DGRAM_SIZE_MAX];
	std::string peerIP;
	int			peerPort;
};

class DatagramQue
{
public:
	DatagramQue() = delete;
	DatagramQue(const DatagramQue&) = delete;
	DatagramQue& operator=(const DatagramQue&) = delete;

	DatagramQue(const int size) 
		: m_readIndex{ 0 }, m_writeIndex{ 0 }
	{
		
		m_Datagram.reserve(size);		
	}

	~DatagramQue() {}
	

private:
	short	m_readIndex;
	short	m_writeIndex;

	std::vector<Datagram> m_Datagram;
};

_MYNETWORK_END