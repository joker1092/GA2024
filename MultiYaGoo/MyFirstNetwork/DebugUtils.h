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
	// TODO: �ʿ��� �α׸� ����ϴ�.
	#define FILE_PRINT() __noop
	#define DEBUG_PRINT __noop
	#define _ASSERT(x) __noop
#endif