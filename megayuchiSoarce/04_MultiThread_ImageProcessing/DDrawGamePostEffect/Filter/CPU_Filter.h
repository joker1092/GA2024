#pragma once

#include <windows.h>
#include "Filter_typedef.h"
#include <process.h>

#define MAX_THREAD_NUM 32

void CPU_BW_Filter(char* pDest, const char* pSrc, DWORD dwWidth, DWORD dwHeight);
void CPU_Blur_Filter(char* pDest, const char* pSrc, DWORD dwWidth, DWORD dwHeight);
void CPU_Edge_Filter(char* pDest, DWORD dwDestPitch, const char* pSrc, DWORD dwImageWidth, DWORD dwImageHeight, DWORD dwSrcPitch);
void CPU_Edge_Filter_SIMD(char* pDest, DWORD dwDestPitch, const char* pSrc, DWORD dwImageWidth, DWORD dwImageHeight, DWORD dwSrcPitch);
void CPU_Edge_Filter_MT(char* pDest, DWORD dwDestPitch, const char* pSrc, DWORD dwImageWidth, DWORD dwImageHeight, DWORD dwSrcPitch, DWORD dwStartHeight, DWORD dwPocessHeight);
void CPU_Edge_Filter_MT_SIMD(char* pDest, DWORD dwDestPitch, const char* pSrc, DWORD dwImageWidth, DWORD dwImageHeight, DWORD dwSrcPitch, DWORD dwStartHeight, DWORD dwPocessHeight);

struct IMAGE_PROCESS_DESC
{
	char*		pSrc;
	char*		pDest;
	FILTER_TYPE	FilterType;
	DWORD		Width;
	DWORD		Height;
	DWORD		dwSrcPitch;
	DWORD		dwDestPitch;
	DWORD		dwStartHeight;
	DWORD		dwProcessHeight;
};

enum THREAD_EVENT
{
	THREAD_EVENT_PROCESS,
	THREAD_EVENT_PROCESS_SIMD,
	THREAD_EVENT_DESTROY,
	THREAD_EVENT_COUNT
};

struct THREAD_ARG {
	IMAGE_PROCESS_DESC* pDesc;
	HANDLE hThread;
	DWORD dwThreadIndex;
	HANDLE hEventList[THREAD_EVENT_COUNT];
	HANDLE* hCompletedEvent;
};
//static HANDLE* m_hCompletedEvent = nullptr; // ��ü �����尡 �Ϸ�Ǿ����� Ȯ���ϱ� ���� �̺�Ʈ �ڵ�
UINT __stdcall ImageProcessThread(void* pParam);