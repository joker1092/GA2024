#include "Player.h"
#include "../../System/InputSystem.h"

Player::Player()
{
	moveSpeed = 100.0f;
	center = { 0,0 };
	width = 50.0f;
	height = 50.0f;
	radius = 50.0f;
	angle = 10.0f;
}

Player::~Player()
{

}

void Player::Init()
{
	//m_collider = new RectangleCollider(center, width, height);
	m_collider = new CircleCollider(center, radius);
	m_collider->parent = this;
	//m_renderBounds = { center, {width / 2, height / 2} };
}

void Player::Update(float delta)
{
	movePlayer(delta);
}

void Player::Render()
{
	Render::DrawCircle(m_pos.x, m_pos.y, radius, RGB(0, 255, 0));
	//Render::DrawRect(m_pos.x, m_pos.y, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2, RGB(255, 0, 0));
}

void Player::OnTrigger()
{
	// 물고기 잡을때 트리거
}

void Player::movePlayer(float delta)
{
	if (Input::IsKey('W'))
	{
		Up(delta);
	}
	if (Input::IsKey('S'))
	{
		Down(delta);
	}
	if  (Input::IsKey('A'))
	{
		Left(delta);
	}
	if (Input::IsKey('D'))
	{
		Right(delta);
	}
}

void Player::Up(float delta)
{
	Vector2 normal = Vector2(0, -1);
	normal.Normalize();
	m_pos += normal * moveSpeed * delta;
}

void Player::Down(float delta)
{
	Vector2 normal = Vector2(0, 1);
	normal.Normalize();
	m_pos += normal * moveSpeed * delta;
}

void Player::Left(float delta)
{
	Vector2 normal = Vector2(-1, 0);
	normal.Normalize();
	m_pos += normal * moveSpeed * delta;
}

void Player::Right(float delta)
{
	Vector2 normal = Vector2(1, 0);
	normal.Normalize();
	m_pos += normal * moveSpeed * delta;
}

