#include "pch.h"
#include "ReferanseCounter.h"

ReferanseCounter::ReferanseCounter()
{
	m_RefCount = 0;
}

ReferanseCounter::~ReferanseCounter()
{

}

void ReferanseCounter::AddRef()
{
	//���� ī��Ʈ ����
	m_RefCount++;
}

int ReferanseCounter::Release()
{
	//���� ī��Ʈ ����
	m_RefCount--;
	//����ī��Ʈ�� 0�� �Ǹ� �޸� ����
	if (m_RefCount == 0)
	{
		delete this;
	}
	// ���� ī��Ʈ ��ȯ
	return m_RefCount;
}

int ReferanseCounter::GetRefCount()
{
    return m_RefCount;
}
