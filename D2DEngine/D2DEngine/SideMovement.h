#pragma once
#include "Movement.h"
class SideMovement : public Movement
{
	static float m_Gravity;
protected:
	bool m_IsJumping = false;  //점프 상태
	float m_GravityScale = 100.0f; //중력 가속도 스케일
	float m_JumpSpeed = 500.0f;  //점프속도
	float m_GravityScaled = 0.0f; //스케일 적용된 중력값
	float m_SpeedY = 0.0f;    //Y축 속도
	float m_MaxSpeedY = 600.0f; //Y축 최대 속도
public:
	SideMovement();
	virtual ~SideMovement();
	virtual void Update(float deltaTime) override;
	virtual void SetDirection(MathHelper::Vector2F direction) override;
	void SetGravityScale(float scale) { m_GravityScale = scale; }
	void ResetGravity() { m_GravityScaled = m_Gravity * m_GravityScale; }
	void Jump();
	bool isJumping() { return m_IsJumping; }
	void EndJump();
};


