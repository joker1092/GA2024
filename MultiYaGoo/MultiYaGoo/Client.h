#pragma once
#include "AsyncSocket.h"
#include "Types.h"

namespace netfish
{
	/*
	*  Client is a class that represents a connection to a client.
	*  Peer Client 와 1-1 대응 되는 소켓 클래스 : 네트워크 연결 상태 등만 관리
	*/
	class Client : public AsyncSocket
	{
	public:
		Client() = default;
		virtual ~Client() = default;
		
		void SetSessionId(SessionId sessionId) { m_sessionId = sessionId; }
		SessionId GetSessionId() { return m_sessionId; }

	private:

		// 세션 객체와 클라이언트(소켓) 객체와 1-1 대응을 해줌
		// 네트워크 연결이 끊겼다 하더라도 세션 객체는 살아있어야 하는 경우가 있을 수 있음.
		// 세션은 다른 객체와 연동해서 처리가 다 완료 되면 해제 해야 함
		// 예를 들어 로그인 세션이라고 해봅시다. 연결이 되면 클라이언트 객체를 생성,
		// 예제에서는 세션 객체를 만들어서 바로 관계를 맺어주지만 현실에서는 피어로 부터 인증 코드를 받지 않으면
		// 일정 시간이 지난후에 서버에서 연결을 끊어 버립니다.
		SessionId m_sessionId = 0;

	};

}
