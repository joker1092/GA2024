#include "framework.h"
#include "Scene.h"
#include "SideMovement.h"

float SideMovement::m_Gravity = 9.8f;

SideMovement::SideMovement()
{
	m_GravityScaled = m_Gravity * m_GravityScale;
}

SideMovement::~SideMovement()
{
	
}

void SideMovement::Update(float deltaTime)
{
	if (!m_pScene)
		return;
	
	MathHelper::Vector2F Location = m_pScene->GetRelativeLocation();

	m_vVelocity.x = (MathHelper::Vector2F(m_vDirection) * m_fSpeed).x;

	m_SpeedY += m_GravityScaled * deltaTime;    //중력가속도 적용
	m_SpeedY = min(m_MaxSpeedY, m_SpeedY);	//중력가속도 적용시 종단속도 제한
	m_vVelocity.y = (MathHelper::Vector2F(0.0f, -1.0f) * m_SpeedY).y;

	Location = Location + m_vVelocity * deltaTime; 
	Location.y = max(0.0f, Location.y);      //todo :: 지면에 닿았는지 체크 현제는 location.y가 0이면 지면에 닿은것으로 판단
	
	if (Location.y <= 0.0f) {
		EndJump();
	}

	m_pScene->SetRelativeLocation(Location);
	//std::cout << "m_IsJumping" << m_IsJumping << "m_GravityScaled" << m_GravityScaled << "Location.y" << Location.y << std::endl;
}

void SideMovement::SetDirection(MathHelper::Vector2F direction)
{
	float len = direction.Length();
	m_vDirection.x = direction.x/len;
	m_vDirection.y = 0;

}

void SideMovement::Jump()
{
	if (m_IsJumping)
		return;
	m_GravityScaled = m_Gravity * m_GravityScale;
	m_IsJumping = true;
	m_SpeedY = m_JumpSpeed*-1;
}

void SideMovement::EndJump()
{
	m_IsJumping = false;
	m_SpeedY = 0;
}
