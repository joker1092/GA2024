#pragma once
//����ó���� ���� ������Ǯ Ŭ����

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

const DWORD MAX_WORKER_THREAD_COUNT = 4;  //���� ���� ��� �ִ� ��� ������ ���� ����

class CThredPool
{
	public:
	CThredPool();
	~CThredPool();
	//������Ǯ �ʱ�ȭ
	void Init();
	//������Ǯ ����
	void Release();

	//������Ǯ�� �۾��� �߰�
	void AddJob(void* pJob);

	//������Ǯ���� �۾��� �Ϸ�ɶ����� ���
	bool WaitJobDone();

private:
	//������Ǯ �۾��� ó���ϴ� �Լ�
	static unsigned int __stdcall ThreadProc(void* pParam);

	
	DWORD dwWorkerThreadCount = 0; //������ Ǯ���� ����� ������ ����
	HANDLE* g_phCompleteEventList = nullptr; //������ Ǯ���� ����� �۾��Ϸ� �̺�Ʈ �ڵ�
	THREAD_ARG* pArgList = nullptr; //������ Ǯ���� ����� ������ ����
};

