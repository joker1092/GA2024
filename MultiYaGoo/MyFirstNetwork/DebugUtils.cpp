#include <stdarg.h>
#include "DebugUtils.h"
//���� ����
//https://docs.microsoft.com/ko-kr/cpp/c-runtime-library/reference/va-arg-va-copy-va-end-va-start?view=msvc-160

#ifdef _DEBUG
	#ifdef UNICODE
		#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
	#else
		#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
	#endif
#endif

//! ���� !! �����忡 �������� �ʽ��ϴ�.
//! ���� ���� : concurrent_queue �� ���� �˾ƺ� ��, Thread-safe �ϵ��� ����� ���ϴ�.
void	DebugPrint(const char* pFormat, ...)
{
	static char logBuf[8192];
	va_list args;
	va_start(args, pFormat);

	vsprintf_s(logBuf, pFormat, args);
	va_end(args);

	printf(logBuf);
}
