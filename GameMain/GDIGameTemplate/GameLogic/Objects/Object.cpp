#include "Object.h"

#define ANIMATION_DELAY 0.05f

void Object::Init()
{

}

void Object::Update(float delta)
{
	std::cout << "Object::Update" << std::endl;
	// 입력 벡터를 Normalize 하여  방향 벡터로 변환
	/*if (m_inputDir != Vector2(0.0f, 0.0f))
	{
		m_inputDir.Normalize();
		m_moveDir = m_inputDir;
	}
	else
	{
		m_moveDir = Vector2(0.0f, 0.0f);
	}	

	m_pos += m_moveDir * m_speed * delta;*/

	/*if (m_moveDir.x != 0.0f)
	{
		m_AnimationFlip = m_moveDir.x < 0 ? true : false;
	}*/

	//공격 중이면 상태	변경하지 않는다.
	/*if (m_status != ObjectStatus::OBJECT_STATUS_ATTACK) 
	{
		if (m_moveDirPrev == Vector2(0.0f,0.0f))
		{
			if (m_moveDir != Vector2(0.0f, 0.0f))
				ChangeStatus(ObjectStatus::OBJECT_STATUS_MOVE);
		}
		else if (m_moveDirPrev != Vector2(0.0f, 0.0f))
		{
			if (m_moveDir == Vector2(0.0f, 0.0f))
				ChangeStatus(ObjectStatus::OBJECT_STATUS_IDLE);
		}
	}*/


	// 화면 밖으로 나가지 않도록 처리. // 나갈 경우 있음.
	//SIZE size = Render::GetScreenSize(); 
	//m_pos = Vector2(std::clamp(m_pos.x, 0.0f, (float)size.cx), std::clamp(m_pos.y, 0.0f, (float)size.cy));

	if (m_pAnimationResource && m_AnimationMotionIndex != -1)
		UpdateAnimation(delta);

	// 이전 방향 벡터 저장
	//m_moveDirPrev = m_moveDir;
}

void Object::Render()
{
	if(m_isActive)
		return;
	
	/*Render::DrawRect((int)m_pos.x - (int)m_renderBounds.extents.x,
		(int)m_pos.y - (int)m_renderBounds.extents.y,
		(int)m_renderBounds.extents.x * 2,
		(int)m_renderBounds.extents.y * 2, RGB(0, 255, 0));*/

	// 애니메이션 리소스가 있고 특정 모션이 설정되어 있으면 해당 프레임을 그린다.
	if (m_pAnimationResource && m_AnimationMotionIndex != -1)
	{
		Frame& frame = m_pAnimationResource->m_motions[m_AnimationMotionIndex].Frames[m_AnimationFrameIndex];
		Gdiplus::Bitmap* bitmap = m_AnimationFlip ? m_pAnimationResource->m_bitmapFlip : m_pAnimationResource->m_bitmap;
		SIZE size = Render::GetScreenSize();
		
		int x = m_AnimationFlip ? (int)m_pos.x - (frame.Size.cx - frame.CenterX) : (int)m_pos.x - frame.CenterX;
		int y = (int)m_pos.y - frame.CenterY;
		int srcX = m_AnimationFlip ? m_pAnimationResource->m_bitmapFlip->GetWidth() - frame.Size.cx - frame.Source.left : frame.Source.left;
		int srcY = frame.Source.top;
	
		//Render::DrawImage(x, y, bitmap, srcX, srcY, frame.Size.cx, frame.Size.cy);		
	}
}

//bool Object::Collide(const Object& other)
//{
//	RECT rc = { (LONG)m_posX - m_colliderSize.cx / 2, (LONG)m_posY - m_colliderSize.cy / 2,
//			(LONG)m_posX + m_colliderSize.cx / 2, (LONG)m_posY + m_colliderSize.cy / 2 };
//
//	RECT rcOther = { (LONG)other.m_posX - other.m_colliderSize.cx / 2, (LONG)other.m_posY - other.m_colliderSize.cy / 2,
//				(LONG)other.m_posX + other.m_colliderSize.cx / 2, (LONG)other.m_posY + other.m_colliderSize.cy / 2 };
//	
//	RECT rcIntersect;
//	if (::IntersectRect(&rcIntersect,&rc,&rcOther))
//	{	
//		return true;
//	}	
//	return false;
//}

void Object::SetMotion(int index)
{
	if (m_pAnimationResource == nullptr)
		return;

	assert(m_pAnimationResource->m_motionCount > index);
	m_AnimationMotionIndex = index;
	m_AnimationFrameIndex = 0;
	m_AnimationAccTime = 0.0f;
}

void Object::UpdateAnimation(float delta)
{
	int frameCount = m_pAnimationResource->m_motions[m_AnimationMotionIndex].FrameCount;
	bool isLoop = m_pAnimationResource->m_motions[m_AnimationMotionIndex].IsLoop;

	// 누적된 시간으로 보여줄 프레임 찾기
	m_AnimationAccTime += delta;
	while (m_AnimationAccTime > ANIMATION_DELAY)
	{
		m_AnimationAccTime -= ANIMATION_DELAY;
	
		if(m_AnimationFrameIndex < frameCount)
			m_AnimationFrameIndex++;
	}

	// 끝 프레임 넘어갔을때 처리
	if (m_AnimationFrameIndex >= frameCount)
	{
		if (isLoop)
		{
			m_AnimationFrameIndex = 0;
		}
		else
		{					
			if (m_status == ObjectStatus::OBJECT_STATUS_ATTACK)
				ChangeStatus(ObjectStatus::OBJECT_STATUS_IDLE);
		}
	}
}

void Object::ChangeStatus(ObjectStatus status)
{
	if (m_status == status)
		return;

	// End 이전 상태를 끝내면서 처리할 내용을 작성
	switch (m_status)
	{
	case OBJECT_STATUS_IDLE:
		break;	
	case OBJECT_STATUS_MOVE:
		break;
	case OBJECT_STATUS_ATTACK:
		break;
	default:
		break;
	}


	m_status = status;

	// Begin 새로운 상태가 시작될때 처리할 내용을 작성
	switch (m_status)
	{
	case ObjectStatus::OBJECT_STATUS_IDLE:
		SetMotion(ObjectStatus::OBJECT_STATUS_IDLE);
		break;
	case ObjectStatus::OBJECT_STATUS_MOVE:
		SetMotion(ObjectStatus::OBJECT_STATUS_MOVE);
		break;
	case ObjectStatus::OBJECT_STATUS_ATTACK:
		SetMotion(ObjectStatus::OBJECT_STATUS_ATTACK);
		break;
	}
}

Vector2 Object::GetPosition() {
	return m_pos;
}





