#include "pch.h"
#include "Windows.h"
#include "CThredPool.h"

CThredPool::CThredPool()
{

}

CThredPool::~CThredPool()
{

}

void CThredPool::Init()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	DWORD dwLogicalCores = sysInfo.dwNumberOfProcessors;

	dwWorkerThreadCount = dwLogicalCores;
	if (dwWorkerThreadCount > MAX_WORKER_THREAD_COUNT)
		dwWorkerThreadCount = MAX_WORKER_THREAD_COUNT;

	g_phCompleteEventList = new HANDLE[dwWorkerThreadCount];

	//
	for (DWORD i = 0; i < dwWorkerThreadCount; i++)
	{
		g_phCompleteEventList[i] = CreateEvent(nullptr, FALSE, FALSE, nullptr);	// worker스레드의 작업이 완료되었을때 시그널될 이벤트

		for (DWORD j = 0; j < THREAD_EVENT_COUNT; j++)
		{
			pArgList[i].hEventList[j] = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		}
		pArgList[i].dwThreadIndex = i;

		UINT ThreadID = 0;
		//pArgList[i].hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadProc, pArgList + i, 0, &ThreadID);
	}
}

void CThredPool::Release()
{
}

void CThredPool::AddJob(void* pJob)
{
}

bool CThredPool::WaitJobDone()
{
    return false;
}
