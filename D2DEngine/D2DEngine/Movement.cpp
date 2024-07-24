#include "framework.h"
#include "Scene.h"
#include "Movement.h"

void Movement::Update(float deltaTime)
{
	if (m_pScene == nullptr)
		return;
	MathHelper::Vector2F pos = m_pScene->m_RelativeLocation;
	m_vVelocity = m_vDirection * m_fSpeed;

	if (m_bIsMoving)
	{
		m_vVelocity.x=-m_vVelocity.x;
	}

	pos += m_vVelocity * deltaTime;

	m_pScene->m_RelativeLocation = pos;
}

void Movement::SetDirection(MathHelper::Vector2F direction)
{
	m_vDirection = direction;
	m_vDirection.Normalize();
}
