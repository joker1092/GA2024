#pragma once
#include "framework.h"
#include "AnimationAsset.h"

class AnimationInstance
{
private:
	AnimationAsset* pAnimationAsset;
	size_t frameIndex;
	size_t animationIndex;
	float progressTime;
	D2D1_VECTOR_2F position = { 0,0 };
	D2D1_MATRIX_3X2_F transform;
	D2D1_RECT_F srcRect;
	D2D1_RECT_F dstRect;
public:
	bool SetAnimationAsset(const wchar_t* FilePath,AnimationAsset::State state);
	void SetPosition(D2D1_VECTOR_2F _position) { position = _position; }
	void Update(float deltaTime);
	void Render(ID2D1RenderTarget* pRenderTarget);
	bool SetAnimationIndex(int index);
};

