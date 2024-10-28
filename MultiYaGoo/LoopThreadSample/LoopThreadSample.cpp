#include <windows.h>
#include <assert.h>
#include <process.h>
#include <conio.h>
#include <iostream>
#include <string>

using namespace std;

#include <concurrent_queue.h>
using namespace Concurrency;


// Win32 API 기반 Thread Class
namespace studysample
{
	class CEvent
	{
	public:
		CEvent(bool bInitialState = false, bool bManualReset = false, TCHAR* pEventName = nullptr);
		~CEvent();

		void	Set() { SetEvent(m_hEvent); }
		HANDLE	GetHandle() { return m_hEvent; }

	private:
		HANDLE	m_hEvent;
	};

	CEvent::CEvent(bool bInitialState, bool bManualReset, TCHAR* pEventName)
	{
		m_hEvent = CreateEvent(NULL, bManualReset, bInitialState, pEventName);
	}

	CEvent::~CEvent()
	{
		if (m_hEvent != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hEvent);
		}
	}


	class CLoopThreadBase
	{
	public:
		CLoopThreadBase(void);
		virtual ~CLoopThreadBase(void);

		virtual	void	DoUpdate() = 0;

		bool	Start(bool bBeginAndRun = true);
		bool	Stop(DWORD dwWaitTime = INFINITE); // millisec

	protected:
		HANDLE	m_hThread;
		UINT	m_ThreadID;

	private:
		static	unsigned int __stdcall	ThreadFunction(void* lpParam);

		CEvent	m_RunEvent;
		CEvent	m_QuitEvent;

		CLoopThreadBase(const CLoopThreadBase& rhs) = delete;
		CLoopThreadBase& operator=(const CLoopThreadBase& rhs) = delete;
	};

	CLoopThreadBase::CLoopThreadBase(void)
	{
		m_hThread = INVALID_HANDLE_VALUE;
		m_ThreadID = 0;
	}

	CLoopThreadBase::~CLoopThreadBase(void)
	{
		CloseHandle(m_hThread);
	}

	bool CLoopThreadBase::Start(bool bBeginAndRun)
	{
		if (m_hThread != INVALID_HANDLE_VALUE) return false; // Already running...

		m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadFunction, this, 0, &m_ThreadID);
		if (m_hThread == INVALID_HANDLE_VALUE) return false;

		if (bBeginAndRun)	m_RunEvent.Set();

		return true;
	}

	bool CLoopThreadBase::Stop(DWORD dwWaitTime)
	{
		if (m_hThread == INVALID_HANDLE_VALUE) return false; // Not running

		m_QuitEvent.Set();
		WaitForSingleObject(m_hThread, dwWaitTime);

		return true;
	}

	unsigned int __stdcall	CLoopThreadBase::ThreadFunction(void* lpParam)
	{
		CLoopThreadBase* lpThread = reinterpret_cast<CLoopThreadBase*>(lpParam);
		WaitForSingleObject(lpThread->m_RunEvent.GetHandle(), INFINITE);

		HANDLE hQuitEvent = lpThread->m_QuitEvent.GetHandle();
		while (true)
		{
			if (WAIT_TIMEOUT == WaitForSingleObject(hQuitEvent, 1))
			{
				lpThread->DoUpdate();
			}
			else
			{
				cout << "Bye." << endl;
				break;
			}
		}

		return 0;
	}


	class CMyLoopThread : public CLoopThreadBase
	{
	public:
		CMyLoopThread() {}
		virtual ~CMyLoopThread() {}

		virtual	void	DoUpdate() override;

		void	Init();
		void	PushString(const string& strMsg);

	private:
		void	OnSecond10();
		void	UpdateTick();

		time_t	m_lNowTime;
		time_t	m_lSecond10;

		concurrent_queue<string> m_StrQueue;
	};

	void CMyLoopThread::DoUpdate()
	{
		UpdateTick();
	}

	void CMyLoopThread::Init()
	{
		time(&m_lNowTime);
		m_lSecond10 = m_lNowTime; // time 은 초단위로 현재 시간을 가져옵니다
	}

	void CMyLoopThread::PushString(const string& strMsg)
	{
		m_StrQueue.push(strMsg);
	}


	void CMyLoopThread::OnSecond10()
	{
		cout << "10초 경과 하였습니다." << endl;

		string strMsg;
		while (m_StrQueue.try_pop(strMsg)) // 가져올 수 있다면
		{
			cout << strMsg.c_str() << endl;
		}

	}

	void CMyLoopThread::UpdateTick()
	{
		time(&m_lNowTime);

		if ((m_lSecond10 - m_lNowTime) < 0)
		{
			OnSecond10();
			m_lSecond10 += 10;
		}
	}

}


int main(void)
{
	studysample::CMyLoopThread myTenTimer;

	myTenTimer.Init();
	myTenTimer.Start(true);

	int KeyInfo;
	const string testMsg = "Hello World";
	do
	{
		KeyInfo = _getch();

		myTenTimer.PushString(testMsg);

	} while (tolower(KeyInfo) != 'q');

	myTenTimer.Stop();

	return 0;
}