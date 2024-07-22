#pragma once
#include "Movement.h"
class SideMovement : public Movement
{
	static float m_Gravity;
protected:
	bool m_IsJumping = false;  //���� ����
	float m_GravityScale = 100.0f; //�߷� ���ӵ� ������
	float m_JumpSpeed = 500.0f;  //�����ӵ�
	float m_GravityScaled = 0.0f; //������ ����� �߷°�
	float m_SpeedY = 0.0f;    //Y�� �ӵ�
	float m_MaxSpeedY = 600.0f; //Y�� �ִ� �ӵ�
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


