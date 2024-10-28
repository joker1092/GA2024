#include <stdarg.h>
#include "DebugUtils.h"
//가변 인자
//https://docs.microsoft.com/ko-kr/cpp/c-runtime-library/reference/va-arg-va-copy-va-end-va-start?view=msvc-160

#ifdef _DEBUG
	#ifdef UNICODE
		#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
	#else
		#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
	#endif
#endif

//! 주의 !! 스레드에 안전하지 않습니다.
//! 숙제 예고 : concurrent_queue 에 대해 알아본 후, Thread-safe 하도록 만들어 봅니다.
void	DebugPrint(const char* pFormat, ...)
{
	static char logBuf[8192];
	va_list args;
	va_start(args, pFormat);

	vsprintf_s(logBuf, pFormat, args);
	va_end(args);

	printf(logBuf);
}
