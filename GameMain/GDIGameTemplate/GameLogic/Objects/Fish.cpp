#include "Fish.h"


void Fish::Move(float delta) {
	m_pos += m_moveDirection * m_speed * delta;
}
void Fish::AngularVelocity(float delta) {
	// �ð�������� �����ϸ�-, �ݽð�������� �����ϸ�+
	float angulerdirScale = sqrtf(powf(m_AngulerDirection.x, 2) + powf(m_AngulerDirection.y, 2));
	float movedirScale = sqrtf(powf(m_moveDirection.x, 2) + powf(m_moveDirection.y, 2));

	float deg = (m_AngulerDirection.x * m_moveDirection.y - m_AngulerDirection.y * m_moveDirection.x) /
		(angulerdirScale * movedirScale); // ȸ������ ���ϱ�
	//deg = asinf(deg) * 180.f / 3.14159f;
	//float rad = asinf(deg);
	
	float inner = m_AngulerDirection.x * m_moveDirection.x + m_AngulerDirection.y * m_moveDirection.y;
	float deg2 = acosf(inner / (angulerdirScale * movedirScale)) * 180.f / 3.14159f;

	float dirScale = deg > 0 ? deg2 : -deg2;
	float dir = deg > 0 ? m_AngulerSpeed * delta : -m_AngulerSpeed * delta;
	if (abs(dirScale) <= abs(dir)) { // ���� �������� ȸ���� ������ Ŭ �� ������ m_moveDirection = m_AngulerDirection;
		m_moveDirection = m_AngulerDirection;
		// ȸ���� �Ϸ�Ǹ� ȸ���� �����ϴ� ���𰡸� �߰��ϸ� �ɵ�.
		m_AngulerDirection = { 0.f, 0.f };
	}
	else {
		dir = dir  / 180.f * 3.14159f;
		float thetaX = m_moveDirection.x * cosf(dir) - m_moveDirection.y * sinf(dir);
		float thetaY = m_moveDirection.x * sinf(dir) + m_moveDirection.y * cosf(dir);

		m_moveDirection = { thetaX, thetaY };
	}

	// m_moveDirection�� ȸ���� ���ͷ� �ʱ�ȭ. (���� ���� < ������ ������ ũ��) ��� m_moveDirection = m_AngulerDirection; �ؾ��ϰ� ȸ������.
}

Vector2 Fish::GetRandomDirection() {
	float theta = rand() % 360;
	theta -= 180;
	theta = theta / 180.f * 3.14159f;
	float a = cosf(theta);
	float b = sinf(theta);
	return { cosf(theta), sinf(theta) };
}

void Fish::Init() {
	// �׽�Ʈ��
	m_collider = new RectangleCollider({ 0.f,0.f }, 100.f, 100.f);
	m_collider->parent = this;
	m_renderBounds = { {0.f, 0.f}, {50.f, 50.f} };
	m_moveDirection = GetRandomDirection();
}

void Fish::Update(float delta) {
	time += delta;
	if (time > maxTime) {
		m_AngulerDirection = GetRandomDirection();
		time -= maxTime;
	}

	Move(delta);
	if (m_AngulerDirection != Vector2(0.f, 0.f))
		AngularVelocity(delta);
}

void Fish::Render() {
	// �׽�Ʈ��
	Render::DrawRect(m_pos.x, m_pos.y, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2, RGB(0, 0, 255));
}

void Fish::OnTrigger() {

}