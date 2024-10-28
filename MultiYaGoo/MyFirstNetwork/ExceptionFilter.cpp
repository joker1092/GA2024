#pragma once
#include <Windows.h>
#include "dbghelp.h"
#include "ExceptionFilter.h"

#pragma comment(lib, "Dbghelp.lib")

LONG WINAPI MyExceptionFilter(struct _EXCEPTION_POINTERS* pExceptionInfo)
{
    // 숙제 예고
    // 파일 관련 수업을 한 후에 test.dmp 를 파일명+날짜+시각으로 만들어 특정 디렉토리에 생성하는 코드를 작성합니다.
    HANDLE hFile = CreateFile(TEXT("test.dmp"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    MINIDUMP_EXCEPTION_INFORMATION stExceptionParam;
    stExceptionParam.ThreadId = GetCurrentThreadId();
    stExceptionParam.ExceptionPointers = pExceptionInfo;
    stExceptionParam.ClientPointers = FALSE;

    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpWithFullMemory, &stExceptionParam, NULL, NULL);
    CloseHandle(hFile);

    return EXCEPTION_EXECUTE_HANDLER;
}