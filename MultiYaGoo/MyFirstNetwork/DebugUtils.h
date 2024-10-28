#pragma once
#include <stdio.h>
#include <assert.h>

void	DebugPrint(const char* pFormat, ...);

//https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-160
//__func__, __line__


#define DEBUG_PRINT DebugPrint


#ifdef _DEBUG
	#define FILE_PRINT() printf("[%s:%d]\n", __FILE__, __LINE__)

	#define DEBUG_PRINT  DebugPrint
	#define _ASSERT(x)		assert(x)

#else
	// TODO: 필요한 로그를 남깁니다.
	#define FILE_PRINT() __noop
	#define DEBUG_PRINT __noop
	#define _ASSERT(x) __noop
#endif