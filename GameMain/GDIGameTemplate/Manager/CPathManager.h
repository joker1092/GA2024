#pragma once
#include "../stdafx.h"
class CPathManager
{
private:
	//��θ� ������ ����
	wchar_t contentPath[255];
public:
	void Init(); // �ʱ�ȭ
	const wchar_t* GetContentPath() { return contentPath; } //resource ���� ��� ��ȯ
};


