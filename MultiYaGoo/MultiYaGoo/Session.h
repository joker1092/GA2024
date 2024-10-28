#pragma once
#include "Types.h"
#include <string>

namespace netfish
{
	class Client;

	class Session
	{
	public:
		Session();

		~Session();

		void Write(const char* pData, int len);

		void ReadUpdate();

		void NetUpdate();

		void SetClient(Client* pClient);

		SessionId GetSessionId() { return m_sessionId; }
	
	private:

		void Read(char* pData, int len);

		Client* m_pClient = nullptr;

		static constexpr int BUF_SIZE = 1024;

		char m_readBuffer[BUF_SIZE] = {};
		char m_writeBuffer[BUF_SIZE] = {};

		int m_readBytes = 0;
		int m_writeBytes = 0;


		SessionId m_sessionId = 0;

		static SessionId s_sessionIdCounter;

		//std::string m_userName;

	};
}


