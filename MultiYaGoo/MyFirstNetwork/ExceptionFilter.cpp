#pragma once
#include <Windows.h>
#include "dbghelp.h"
#include "ExceptionFilter.h"

#pragma comment(lib, "Dbghelp.lib")

LONG WINAPI MyExceptionFilter(struct _EXCEPTION_POINTERS* pExceptionInfo)
{
    // ���� ����
    // ���� ���� ������ �� �Ŀ� test.dmp �� ���ϸ�+��¥+�ð����� ����� Ư�� ���丮�� �����ϴ� �ڵ带 �ۼ��մϴ�.
    HANDLE hFile = CreateFile(TEXT("test.dmp"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    MINIDUMP_EXCEPTION_INFORMATION stExceptionParam;
    stExceptionParam.ThreadId = GetCurrentThreadId();
    stExceptionParam.ExceptionPointers = pExceptionInfo;
    stExceptionParam.ClientPointers = FALSE;

    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpWithFullMemory, &stExceptionParam, NULL, NULL);
    CloseHandle(hFile);

    return EXCEPTION_EXECUTE_HANDLER;
}