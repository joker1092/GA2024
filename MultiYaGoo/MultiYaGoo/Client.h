#pragma once
#include "AsyncSocket.h"
#include "Types.h"

namespace netfish
{
	/*
	*  Client is a class that represents a connection to a client.
	*  Peer Client �� 1-1 ���� �Ǵ� ���� Ŭ���� : ��Ʈ��ũ ���� ���� � ����
	*/
	class Client : public AsyncSocket
	{
	public:
		Client() = default;
		virtual ~Client() = default;
		
		void SetSessionId(SessionId sessionId) { m_sessionId = sessionId; }
		SessionId GetSessionId() { return m_sessionId; }

	private:

		// ���� ��ü�� Ŭ���̾�Ʈ(����) ��ü�� 1-1 ������ ����
		// ��Ʈ��ũ ������ ����� �ϴ��� ���� ��ü�� ����־�� �ϴ� ��찡 ���� �� ����.
		// ������ �ٸ� ��ü�� �����ؼ� ó���� �� �Ϸ� �Ǹ� ���� �ؾ� ��
		// ���� ��� �α��� �����̶�� �غ��ô�. ������ �Ǹ� Ŭ���̾�Ʈ ��ü�� ����,
		// ���������� ���� ��ü�� ���� �ٷ� ���踦 �ξ������� ���ǿ����� �Ǿ�� ���� ���� �ڵ带 ���� ������
		// ���� �ð��� �����Ŀ� �������� ������ ���� �����ϴ�.
		SessionId m_sessionId = 0;

	};

}
