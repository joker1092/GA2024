#pragma once
//병렬처리를 위한 쓰레드풀 클레스

enum THREAD_EVENT
{
	THREAD_EVENT_PROCESS,
	THREAD_EVENT_DESTROY,
	THREAD_EVENT_COUNT
};
struct THREAD_ARG
{
	HANDLE hThread;
	HANDLE hEventList[THREAD_EVENT_COUNT];
	DWORD dwThreadIndex;
};

const DWORD MAX_WORKER_THREAD_COUNT = 4;  //성능 저하 우려 최대 사용 쓰레드 개수 설정

class CThredPool
{
	public:
	CThredPool();
	~CThredPool();
	//쓰레드풀 초기화
	void Init();
	//쓰레드풀 해제
	void Release();

	//쓰레드풀에 작업을 추가
	void AddJob(void* pJob);

	//쓰레드풀에서 작업이 완료될때까지 대기
	bool WaitJobDone();

private:
	//쓰레드풀 작업을 처리하는 함수
	static unsigned int __stdcall ThreadProc(void* pParam);

	
	DWORD dwWorkerThreadCount = 0; //쓰레드 풀에서 사용할 쓰레드 개수
	HANDLE* g_phCompleteEventList = nullptr; //쓰레드 풀에서 사용할 작업완료 이벤트 핸들
	THREAD_ARG* pArgList = nullptr; //쓰레드 풀에서 사용할 쓰레드 인자
};

