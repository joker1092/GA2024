#include "pch.h"
#include "AnimationAsset.h"


AnimationAsset::AnimationAsset()
{
	//������ �⺻ ������ 10���� ����
	animations.resize(10);
}

AnimationAsset::~AnimationAsset()
{
	//�ִϸ��̼� ���� ����

}

void AnimationAsset::Load(const wchar_t* _fileName)
{

}

const AnimationAsset::AnimationInfo& AnimationAsset::GetAnimationInfo(const std::wstring& _name)
{
	// TODO: ���⿡ return ���� �����մϴ�.
}

void AnimationAsset::LoadTexture(const wchar_t* _fileName)
{
	//���ϸ����� ��Ʈ�� �ε�

}

void AnimationAsset::LoadAnimationInfo(const wchar_t* _fileName)
{
}
