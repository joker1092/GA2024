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
		// m_pClient->Send �� �ٷ� ȣ������ �ʰ� m_writeBuffer�� �����صд�.
	}

	void Session::ReadUpdate()
	{
		// ���Ͽ� m_readBuffer �� ������ �о���� �Ѵ�.
		// TODO: ���� ��Ŷ�� ��� �Ľ��� ���ΰ��� ���� ������ �ٲ�Ƿ� �ϴ��� ���߿� �ٽ� �̾߱� �մϴ�.

		assert(m_pClient != nullptr);

		int bufLen = BUF_SIZE - m_readBytes;

		int nRead = m_pClient->Recv(m_readBuffer, bufLen);

		m_readBytes += nRead;

	}
	
	void Session::NetUpdate()
	{
		// �۽� ���ۿ� �����Ͱ� ������ Ŭ���̾�Ʈ���� �����Ѵ�. m_pClient->Send
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
				// ���� ���۰� ���� ���� ������ �Ұ���
				// �̷� �� ��� �ұ�? ������ ����. ? �����غ� �ð� ��� �ݴϴ�.
			}
			else
			{
				// ���� ������ �߻���. ��¿��? �� �����ؾ���. 
			}

		}
		
	
		if (m_readBytes)
		{
			//���� ���ۿ� �����Ͱ� ������ ��ȿ�� ��Ŷ���� Ȯ���Ѵ�.
			//���� ���� �����ϴ� ���ε� ���� ������ 
			// ���� 2����Ʈ�� ��Ŷ�� ũ�⸦ �ǹ��ϰ�.
			// �� ���� 2����Ʈ�� ��Ŷ�� ���̵� �ǹ��մϴ�.
			/*struct PacketHeader
			{
				short size;
				short id;
			};*/
			// 
			//1. ���� ������ ù 2����Ʈ�� �о ����� Ȯ���� ���ϴ�. ���������̶��? ��! ����.
			//2. ������ ������ ���� ��� 30����Ʈ�� ���, �ڿ� ������ ������ ũ�⸦ �����ؼ�
			//   (������ ������ ������ ũ���� �����Ͽ�) 30����Ʈ �̻� �ִ��� Ȯ���Ѵ�. �ƴϸ�? ������ ���ؾ��ϴ� ��
			//3. ������ ������ �����. �׷��� ��Ŷ ���̵� Ȯ���ؼ� ó���Ϸ� ���� ���ǵ� ���̵� �ƴ�. ��! ����. �α�.
			//4. ��� ������ ������ ���ٸ� ��Ŷ id ���� ó�� �Լ��� ȣ���ϴ°� ���� ������ ����.


			//���� �������� �� ���� �ϴ��� ���� �����͸� �׳�, �۽� ���ۿ� ������ ���ô�.
			//m_readBuffer�� ���� �����͸� m_writeBuffer �� �����غ��ϴ�.
		}
	}

	void Session::SetClient(Client* pClient)
	{
		m_sessionId = ++s_sessionIdCounter;

		m_pClient = pClient;

		m_pClient->SetSessionId(m_sessionId);
	}
	
}