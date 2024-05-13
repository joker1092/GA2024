
#include "CPathManager.h"


void CPathManager::Init()
{
	//현제 폴더 경로 찾음
	GetCurrentDirectory(255, contentPath);

	int len = wcslen(contentPath);
	//글자를 잘라내여 상위 폴더로
	for (int i = len -1 ; 0 <=i ; i--)
	{
		if (contentPath[i]=='\\')
		{
			contentPath[i] = '\0';
			break;
		}
	}
	//사용할 리소스가 들어간 폴더 경로 추가
	wcscat_s(contentPath, 255, L"\\bin\\Resource\\");
}
