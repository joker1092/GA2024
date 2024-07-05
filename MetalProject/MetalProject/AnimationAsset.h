#pragma once
#include "ReferanseCounter.h"

//com객체가 아닌 Animation을 정보	를 담는 객체
class AnimationAsset : public ReferanseCounter
{
	//애니메이션 한 프레임의 정보를 담는 구조체
	struct FrameInfo
	{
		//텍스쳐 좌상단 x좌표
		float left;
		//텍스쳐 좌상단 y좌표
		float top;
		//텍스쳐 우하단 x좌표
		float right;
		//텍스쳐 우하단 y좌표
		float bottom;
		//텍스쳐의 중심 x좌표
		float centerX;
		//텍스쳐의 중심 y좌표
		float centerY;
		//프레임이 보여질 지속시간
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
		//프레임 정보를 설정하는 함수
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
		//rect로 받는 경우
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
		//변수를 받고 중심을 포인트로 받는 경우



	};

	//애니메이션 정보를 담는 구조체
	struct AnimationInfo
	{
		//애니메이션 이름
		std::wstring name;
		//애니메이션의 프레임 정보
		std::vector<FrameInfo> frameInfos;
		
		AnimationAsset::AnimationInfo()
		{
			//생성시 기본 사이즈 10으로 설정
			frameInfos.resize(10);
		}
		//애니메이션의 프레임 정보를 반환하는 함수
		const FrameInfo& GetFrameInfo(int _index)
		{
			return frameInfos[_index];
		}
	};
		
	//애니메이션 정보를 담는 벡터
	std::vector<AnimationInfo> animations;
	
	//로드한 텍스쳐의 주소
	ID2D1Bitmap* texture;
	public:
		AnimationAsset();
		~AnimationAsset();
		//애니메이션 정보를 로드하는 함수
		void Load(const wchar_t* _fileName);
		//애니메이션 정보를 반환하는 함수
		const AnimationInfo& GetAnimationInfo(const std::wstring& _name);
		//로드한 텍스쳐의 주소를 반환하는 함수
		ID2D1Bitmap* GetTexture() { return texture; }
		//애니메이션 정보를 반환하는 함수
		const std::vector<AnimationInfo>& GetAnimations() { return animations; }
		
		//텍스쳐 로드
		void LoadTexture(const wchar_t* _fileName);

		//파일로 부터 애니메이션 정보를 로드하는 함수
		void LoadAnimationInfo(const wchar_t* _fileName);
};

