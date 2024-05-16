#include "Object.h"

#define ANIMATION_DELAY 0.05f

void Object::Init()
{

}

void Object::Update(float delta)
{
	// �Է� ���͸� Normalize �Ͽ�  ���� ���ͷ� ��ȯ
	/*if (m_inputDir != Vector2(0.0f, 0.0f))
	{
		m_inputDir.Normalize();
		m_moveDir = m_inputDir;
	}*/
	//if (m_moveDir != Vector2(0.0f, 0.0f))
	//{
	//	m_moveDir.Normalize();
	//}
	//else
	//{
	//	m_moveDir = Vector2(0.0f, 0.0f);
	//}	

	//m_pos += m_moveDir * delta;

	//if (m_moveDir.x != 0.0f)
	//{
	//	m_AnimationFlip = m_moveDir.x < 0 ? true : false;
	//}

	//���� ���̸� ����	�������� �ʴ´�.
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


	// ȭ�� ������ ������ �ʵ��� ó��. // ���� ��� ����.
	//SIZE size = Render::GetScreenSize(); 
	//m_pos = Vector2(std::clamp(m_pos.x, 0.0f, (float)size.cx), std::clamp(m_pos.y, 0.0f, (float)size.cy));

	/*if (m_pAnimationResource && m_AnimationMotionIndex != -1)
		UpdateAnimation(delta);*/

	// ���� ���� ���� ����
	//m_moveDirPrev = m_moveDir;
}

void Object::Render(float alpha)
{
	if(m_isActive)
		return;
	
	/*Render::DrawRect((int)m_pos.x - (int)m_renderBounds.extents.x,
		(int)m_pos.y - (int)m_renderBounds.extents.y,
		(int)m_renderBounds.extents.x * 2,
		(int)m_renderBounds.extents.y * 2, RGB(0, 255, 0));*/

	// �ִϸ��̼� ���ҽ��� �ְ� Ư�� ����� �����Ǿ� ������ �ش� �������� �׸���.

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

	// ������ �ð����� ������ ������ ã��
	m_AnimationAccTime += delta;
	while (m_AnimationAccTime > ANIMATION_DELAY)
	{
		m_AnimationAccTime -= ANIMATION_DELAY;
	
		if(m_AnimationFrameIndex < frameCount)
			m_AnimationFrameIndex++;
	}

	// �� ������ �Ѿ���� ó��
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

	// End ���� ���¸� �����鼭 ó���� ������ �ۼ�
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

	// Begin ���ο� ���°� ���۵ɶ� ó���� ������ �ۼ�
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





