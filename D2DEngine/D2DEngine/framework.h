#pragma once
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <Windows.h>

#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <map>

#include <d2d1.h>
#include <comdef.h>
#include <wincodec.h>
#include <dwrite.h>
#include <d2d1_1helper.h>

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
