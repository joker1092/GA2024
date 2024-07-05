#pragma once

//Com객체가 아닌 일반적인 객체의 참조 카운트를 관리하는 클래스
class ReferanseCounter
{
	private:
		//참조 카운트
		int m_RefCount;
	public:
	ReferanseCounter();
	~ReferanseCounter();

	//참조 카운트를 증가시킨다.
	void AddRef();

	//참조 카운트를 감소시킨다.
	int Release();

	//참조 카운트를 반환한다.
	int GetRefCount();
};

