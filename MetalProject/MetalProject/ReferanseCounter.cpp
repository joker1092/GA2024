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
	//참조 카운트 증가
	m_RefCount++;
}

int ReferanseCounter::Release()
{
	//참조 카운트 감소
	m_RefCount--;
	//참조카운트가 0이 되면 메모리 해제
	if (m_RefCount == 0)
	{
		delete this;
	}
	// 참조 카운트 반환
	return m_RefCount;
}

int ReferanseCounter::GetRefCount()
{
    return m_RefCount;
}
