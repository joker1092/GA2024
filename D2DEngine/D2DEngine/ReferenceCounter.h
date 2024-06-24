#pragma once
class ReferenceCounter
{
private:
	unsigned int m_RefCount;
public:
	ReferenceCounter():m_RefCount(0){}
	virtual ~ReferenceCounter(){}

	unsigned int AddRef() {
		m_RefCount++;
		return m_RefCount;
	}

	unsigned int Release() {
		m_RefCount--;
		if (m_RefCount == 0)
		{
			delete this;
			return 0;
		}
		return m_RefCount;
	}

	unsigned int GetRefCount() {
		return m_RefCount;
	}
};

