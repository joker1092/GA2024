
#include "CPathManager.h"


void CPathManager::Init()
{
	//���� ���� ��� ã��
	GetCurrentDirectory(255, contentPath);

	int len = wcslen(contentPath);
	//���ڸ� �߶󳻿� ���� ������
	for (int i = len -1 ; 0 <=i ; i--)
	{
		if (contentPath[i]=='\\')
		{
			contentPath[i] = '\0';
			break;
		}
	}
	//����� ���ҽ��� �� ���� ��� �߰�
	wcscat_s(contentPath, 255, L"\\bin\\Resource\\");
}
