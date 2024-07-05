#pragma once
#include "ReferanseCounter.h"

//com��ü�� �ƴ� Animation�� ����	�� ��� ��ü
class AnimationAsset : public ReferanseCounter
{
	//�ִϸ��̼� �� �������� ������ ��� ����ü
	struct FrameInfo
	{
		//�ؽ��� �»�� x��ǥ
		float left;
		//�ؽ��� �»�� y��ǥ
		float top;
		//�ؽ��� ���ϴ� x��ǥ
		float right;
		//�ؽ��� ���ϴ� y��ǥ
		float bottom;
		//�ؽ����� �߽� x��ǥ
		float centerX;
		//�ؽ����� �߽� y��ǥ
		float centerY;
		//�������� ������ ���ӽð�
		float duration;
		
		FrameInfo()
		{
			left = 0;
			top = 0;
			right = 0;
			bottom = 0;
			centerX = 0;
			centerY = 0;
			duration = 0;
		}
		//������ ������ �����ϴ� �Լ�
		FrameInfo(float _left, float _top, float _right, float _bottom, float _centerX, float _centerY, float _duration)
		{
			left = _left;
			top = _top;
			right = _right;
			bottom = _bottom;
			centerX = _centerX;
			centerY = _centerY;
			duration = _duration;
		}
		//rect�� �޴� ���
		FrameInfo(D2D1_RECT_F _rect, float _centerX, float _centerY, float _duration)
		{
			left = _rect.left;
			top = _rect.top;
			right = _rect.right;
			bottom = _rect.bottom;
			centerX = _centerX;
			centerY = _centerY;
			duration = _duration;
		}
		//������ �ް� �߽��� ����Ʈ�� �޴� ���



	};

	//�ִϸ��̼� ������ ��� ����ü
	struct AnimationInfo
	{
		//�ִϸ��̼� �̸�
		std::wstring name;
		//�ִϸ��̼��� ������ ����
		std::vector<FrameInfo> frameInfos;
		
		AnimationAsset::AnimationInfo()
		{
			//������ �⺻ ������ 10���� ����
			frameInfos.resize(10);
		}
		//�ִϸ��̼��� ������ ������ ��ȯ�ϴ� �Լ�
		const FrameInfo& GetFrameInfo(int _index)
		{
			return frameInfos[_index];
		}
	};
		
	//�ִϸ��̼� ������ ��� ����
	std::vector<AnimationInfo> animations;
	
	//�ε��� �ؽ����� �ּ�
	ID2D1Bitmap* texture;
	public:
		AnimationAsset();
		~AnimationAsset();
		//�ִϸ��̼� ������ �ε��ϴ� �Լ�
		void Load(const wchar_t* _fileName);
		//�ִϸ��̼� ������ ��ȯ�ϴ� �Լ�
		const AnimationInfo& GetAnimationInfo(const std::wstring& _name);
		//�ε��� �ؽ����� �ּҸ� ��ȯ�ϴ� �Լ�
		ID2D1Bitmap* GetTexture() { return texture; }
		//�ִϸ��̼� ������ ��ȯ�ϴ� �Լ�
		const std::vector<AnimationInfo>& GetAnimations() { return animations; }
		
		//�ؽ��� �ε�
		void LoadTexture(const wchar_t* _fileName);

		//���Ϸ� ���� �ִϸ��̼� ������ �ε��ϴ� �Լ�
		void LoadAnimationInfo(const wchar_t* _fileName);
};

