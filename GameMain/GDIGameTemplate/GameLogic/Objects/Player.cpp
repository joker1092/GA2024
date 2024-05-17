#include "Player.h"
#include "Fish.h"
#include "../../System/InputSystem.h"
#include "../Event.h"

Player::Player()
{
	moveSpeed = 70.0f;
	radius = 50.0f;
	pauseEvent = nullptr;
	moveDirection = { 0.f, 0.f };
	m_AnimationMotionIndex = 0;
	Init();
}

//Player::~Player()
//{
//	/*if (pauseEvent != nullptr) {
//		delete pauseEvent;
//	}*/
//}

void Player::Init()
{
	playerBitmap = Gdiplus::Bitmap::FromFile(L"Player.png");
	m_collider = new CircleCollider({ 0,0 }, radius);
	m_collider->parent = this;

	m_renderBounds = { { 0,0 }, {playerBitmap->GetWidth() / 2.f, playerBitmap->GetHeight() / 2.f}};

	isAwake = false;
}

void Player::Update(float delta)
{
	/*sScale -= delta;
	if (sScale <= 0.7f)
	{
		sScale = 0.7f;
	}*/
	movePlayer(delta);

	ScoopUp(delta);

	//if (flag == true)
	//{
	//	ChangeStatus(ObjectStatus::OBJECT_STATUS_MOVE);
	//}
	//else
	//{
	//	ChangeStatus(ObjectStatus::OBJECT_STATUS_IDLE);
	//}
	//
	////if(Input::IsKeyDown('F'))
	//if (m_pAnimationResource && m_AnimationMotionIndex != -1)
	//{
	//	UpdateAnimation(delta);
	//}

}

void Player::Render(float alpha)
{
	/*Render::DrawCircle(m_pos.x, m_pos.y, radius, RGB(0, 255, 0));
	Render::*/

	if (m_pAnimationResource && m_AnimationMotionIndex != -1)
	{
		Frame& frame = m_pAnimationResource->m_motions[m_AnimationMotionIndex].Frames[m_AnimationFrameIndex];
		Gdiplus::Bitmap* bitmap = m_AnimationFlip ? m_pAnimationResource->m_bitmapFlip : m_pAnimationResource->m_bitmap;
		SIZE size = Render::GetScreenSize();

		int x = m_AnimationFlip ? (int)m_pos.x - (frame.Size.cx - frame.CenterX) : (int)m_pos.x - frame.CenterX;
		int y = (int)m_pos.y - frame.CenterY;
		int srcX = m_AnimationFlip ? m_pAnimationResource->m_bitmapFlip->GetWidth() - frame.Size.cx - frame.Source.left : frame.Source.left;
		int srcY = frame.Source.top;

		Render::DrawImage(x, y, bitmap, srcX, srcY, frame.Size.cx, frame.Size.cy , alpha);
	}
	//Render::DrawCircle(m_pos.x, m_pos.y, radius, RGB(0, 255, 0));
	//Render::DrawRect(m_pos.x, m_pos.y, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2, RGB(255, 0, 0));
	//Render::DrawImage(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, playerBitmap, 0, 0, playerBitmap->GetWidth(), playerBitmap->GetHeight());
	//if(r) Render::DrawCircle(m_pos.x, m_pos.y, radius, RGB(0, 255, 0));
	Render::DrawImage(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, playerBitmap, 0, 0, playerBitmap->GetWidth(), playerBitmap->GetHeight(), alpha, scale);
}

void Player::OnTrigger()
{
	// 물고기 잡을때 트리거
}
void Player::movePlayer(float delta)
{
	moveDirection = { 0.f, 0.f };
	if (Input::IsKey('W')) {
		moveDirection.y = isAwake ? -1 : up;
	}
	else if (Input::IsKey('S')) {
		moveDirection.y = isAwake ? 1 : down;
	}
	if (Input::IsKey('A')) {
		moveDirection.x = isAwake ? -1 : left;
	}
	else if (Input::IsKey('D')) {
		moveDirection.x = isAwake ? 1 : right;
	}
	if(moveDirection != Vector2(0.f, 0.f))
		moveDirection.Normalize();
	m_pos += moveDirection * moveSpeed * delta;
	if (Input::IsKey(VK_ESCAPE))
	{
		//pauseEvent
		pauseEvent->OnTrigger();
	}
}

void Player::ScoopUp(float delta)
{
	if (Input::IsKeyDown(' ') && isScoopUp == false) {
		isScoopUp = true;
		moveSpeed = 45.f;
		isOnScoopUpSound = true;
	}

	if (isScoopUp == true) {
		scoopUpTime += delta;
		if (scoopUpTime >= 0.f && scoopUpTime < 1.5f) {
			scale -= delta * 0.25f / 1.5f; // 1.5초에 걸쳐서 0.75 scale까지 줄어듦.
			if (scale < 0.75f)
				scale = 0.75f;
		}
		else if (scoopUpTime >= 1.5f && scoopUpTime < 4.5f) {
			// nothing
		}
		else if (scoopUpTime >= 4.5f && scoopUpTime < 6.f) {
			scale += delta * 0.25f / 1.5f;
			if (scale > 1.f)
				scale = 1.f;
		}

		if (scoopUpTime >= 1.3f && scoopUpTime < 1.5f) {
			//r = true;
			if (isOnScoopUpSound == true) {
				// 사운드, 시각효과 Play
				isOnScoopUpSound = false; // 1회만 실행하기 위한 bool값
			}
		}
		else if (scoopUpTime >= 1.5f && scoopUpTime < 4.5f) {
			SceneManager* s = SceneManager::GetInstance();
			auto c = s->GetCurScene();

			Collider* fishs[24];
			int count = c->colliderManager->GetCountCollidersAtType(m_collider, fishs, 20, TYPE::FISH);
			for (int i = 0; i < count; i++) {
				fishs[i]->parent->OnTrigger();
			}
		}
		else if (scoopUpTime >= 4.5f && scoopUpTime < 6.f) {
			
		}
		else if (scoopUpTime >= 6.f){
			isScoopUp = false;
			scoopUpTime = 0.f;
			moveSpeed = 70.f;
			//r = false;
		}
	}
}

