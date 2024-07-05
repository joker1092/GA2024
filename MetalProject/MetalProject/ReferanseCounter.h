#pragma once

//Com��ü�� �ƴ� �Ϲ����� ��ü�� ���� ī��Ʈ�� �����ϴ� Ŭ����
class ReferanseCounter
{
	private:
		//���� ī��Ʈ
		int m_RefCount;
	public:
	ReferanseCounter();
	~ReferanseCounter();

	//���� ī��Ʈ�� ������Ų��.
	void AddRef();

	//���� ī��Ʈ�� ���ҽ�Ų��.
	int Release();

	//���� ī��Ʈ�� ��ȯ�Ѵ�.
	int GetRefCount();
};

