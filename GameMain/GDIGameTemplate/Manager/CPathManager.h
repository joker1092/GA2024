#pragma once
#include "../stdafx.h"
class CPathManager
{
private:
	//경로를 저장할 변수
	wchar_t contentPath[255];
public:
	void Init(); // 초기화
	const wchar_t* GetContentPath() { return contentPath; } //resource 폴더 경로 반환
};


