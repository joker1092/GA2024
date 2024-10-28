#include "Session.h"
#include "Client.h"
#include <cassert>

namespace netfish
{
	SessionId Session::s_sessionIdCounter;

	Session::Session()
	{
		
	}

	Session::~Session()
	{
	}
	
	void Session::Write(const char* pData, int len)
	{
		// m_pClient->Send 를 바로 호출하지 않고 m_writeBuffer에 복사해둔다.
	}

	void Session::ReadUpdate()
	{
		// 소켓에 m_readBuffer 를 던져서 읽어오게 한다.
		// TODO: 받은 패킷을 어떻게 파싱할 것인가에 따라 구조가 바뀌므로 일단은 나중에 다시 이야기 합니다.

		assert(m_pClient != nullptr);

		int bufLen = BUF_SIZE - m_readBytes;

		int nRead = m_pClient->Recv(m_readBuffer, bufLen);

		m_readBytes += nRead;

	}
	
	void Session::NetUpdate()
	{
		// 송신 버퍼에 데이터가 있으면 클라이언트에게 전송한다. m_pClient->Send
		if (m_writeBytes)
		{
			int nSent = m_pClient->Send(m_writeBuffer, m_writeBytes);

			if (nSent > 0)
			{
				m_writeBytes -= nSent;

				if (m_writeBytes > 0)
				{
					memmove(m_writeBuffer, m_writeBuffer + nSent, m_writeBytes);
				}
			}
			else if (nSent == 0)
			{
				// 소켓 버퍼가 가득 차서 전송이 불가능
				// 이럴 때 어떻게 할까? 생각해 보자. ? 생각해볼 시간 잠깐 줍니다.
			}
			else
			{
				// 소켓 에러가 발생함. 어쩔까? 뭐 정리해야죠. 
			}

		}
		
	
		if (m_readBytes)
		{
			//수신 버퍼에 데이터가 있으면 유효한 패킷인지 확인한다.
			//여러 분의 정의하는 것인데 지금 샘플은 
			// 앞의 2바이트는 패킷의 크기를 의미하고.
			// 그 다음 2바이트는 패킷의 아이디를 의미합니다.
			/*struct PacketHeader
			{
				short size;
				short id;
			};*/
			// 
			//1. 수신 버퍼의 첫 2바이트를 읽어서 사이즈를 확인해 봅니다. 비정상적이라면? 너! 나가.
			//2. 사이즈 정보가 예를 들어 30바이트인 경우, 뒤에 수신한 데이터 크기를 포함해서
			//   (사이즈 정보를 포함한 크기라는 전제하에) 30바이트 이상 있는지 확인한다. 아니면? 수신을 더해야하니 고
			//3. 사이즈 정보가 충분해. 그런데 패킷 아이디를 확인해서 처리하려 보니 정의된 아이디가 아님. 너! 나가. 로그.
			//4. 모든 조건이 문제가 없다면 패킷 id 별로 처리 함수를 호출하는게 가장 심플한 버전.


			//먼저 여러분이 할 것은 일단은 받은 데이터를 그냥, 송신 버퍼에 복사해 봅시다.
			//m_readBuffer의 받은 데이터를 m_writeBuffer 로 복사해봅니다.
		}
	}

	void Session::SetClient(Client* pClient)
	{
		m_sessionId = ++s_sessionIdCounter;

		m_pClient = pClient;

		m_pClient->SetSessionId(m_sessionId);
	}
	
}