#include "Fish.h"


void Fish::Move(float delta) {
	m_pos += m_moveDirection * m_speed * delta;
}
void Fish::AngularVelocity(float delta) {
	// �ð�������� �����ϸ�-, �ݽð�������� �����ϸ�+

	// ��Ʈ�� ����
	// ** rect���� ���� ��ġ�� �������� ��ġ�� �Ÿ��� �̿��Ͽ� �̵��ð��� ������ ������.
	// bug rect�� �ʹ� ����� ��찡 �ִµ� �̴� ���߿� �׽�Ʈ �غ���.
	float cross = (m_AngulerDirection.x * m_moveDirection.y - m_AngulerDirection.y * m_moveDirection.x); // ȸ������ ���ϱ�
	float inner = m_AngulerDirection.x * m_moveDirection.x + m_AngulerDirection.y * m_moveDirection.y;
	float radian = acosf(inner);

	float dirScale = cross > 0 ? radian : -radian;
	float dir = cross > 0 ? m_AngulerSpeed * delta : -m_AngulerSpeed * delta;
	//std::cout << "deg2: " << 3.14159f - abs(radian) << ", dirScale: " << abs(dir) << std::endl;
	if (3.14159f - abs(radian) <= abs(dir)) { // ���� �������� ȸ���� ������ Ŭ �� ������ m_moveDirection = m_AngulerDirection;
		m_moveDirection = { -m_AngulerDirection.x,  -m_AngulerDirection.y};
		// ȸ���� �Ϸ�Ǹ� ȸ���� �����ϴ� ���𰡸� �߰��ϸ� �ɵ�.
		m_AngulerDirection = { 0.f, 0.f };
	}
	else {
		float cosF = cosf(dir);
		float sinF = sinf(dir);
		float thetaX = m_moveDirection.x * cosF - m_moveDirection.y * sinF;
		float thetaY = m_moveDirection.x * sinF + m_moveDirection.y * cosF;

		m_moveDirection = { thetaX, thetaY };
	}

	// m_moveDirection�� ȸ���� ���ͷ� �ʱ�ȭ. (���� ���� < ������ ������ ũ��) ��� m_moveDirection = m_AngulerDirection; �ؾ��ϰ� ȸ������.
}

Vector2 Fish::GetRandomDirection() {
	/*float theta = rand() % 360;
	theta -= 180;
	theta = theta / 180.f * 3.14159f;
	float a = cosf(theta);
	float b = sinf(theta);
	return { cosf(theta), sinf(theta) };*/
	//int random = rand() % 20000;
	//random -= 10000;
	//float x = random / 10000.f; //-1.f ~ 1.f
	//float y = 1 - (x * x);
	//y = sqrtf(y);
	//y = (rand() % 2) == 0 ? -y : y;
	//return { x, y };
	//std::cout << "���� ��ġ: " << (int)m_pos.x << ", " << (int)m_pos.y << std::endl;
	Vector2 position = GetRandomPosition();
	//std::cout << "���� ��ġ: " << position.x << ", " << position.y;
	float distance = sqrtf(pow(m_pos.x - position.x, 2) + pow(m_pos.y - position.y, 2)); // �Ÿ��� �� �ð��� ��.
	maxTime = distance / m_speed;
	//std::cout << ", " << maxTime << std::endl;
	Vector2 direction = m_pos - position;
	direction.Normalize(); // ����.
	return direction;
}

Vector2 Fish::GetRandomPosition() {
	int boundsX = (int)m_renderBounds.extents.x;
	int boundsY = (int)m_renderBounds.extents.y;
	int width =  (x2 - boundsX) - (x1 + boundsX);
	int height = (y2 - boundsY) - (y1 + boundsY);

	width = rand() % width + (x1 + boundsX);
	height = rand() % height + (y1 + boundsY);

	return { (float)width, (float)height };
}

void Fish::Init() {
	// �׽�Ʈ��
	m_collider = new RectangleCollider({ 0.f,0.f }, 100.f, 100.f);
	m_collider->parent = this;
	
	m_FishImage = Gdiplus::Bitmap::FromFile(L"FishTest.png");
	m_renderBounds = { {0.f, 0.f}, {m_FishImage->GetWidth() / 2.f, m_FishImage->GetHeight() / 2.f}};

	m_moveDirection = GetRandomDirection();
	//renderBounds2 = { {0.f, 50.f} , {m_FishImage->GetWidth() / 2.f, m_FishImage->GetHeight() / 2.f} };
}

void Fish::Update(float delta) {
	if (m_isActive == false) return;
	time += delta;
	if (time > maxTime) {
		m_AngulerDirection = GetRandomDirection();
		time = 0;
	}

	Move(delta);

	if (m_AngulerDirection != Vector2(0.f, 0.f))
		AngularVelocity(delta);
}

void Fish::Render() {
	if (m_isActive == false) return;

	float deg = (0.f * m_moveDirection.y - 1.f * m_moveDirection.x);  // ȸ������ ���ϱ�
	//deg = asinf(deg) * 180.f / 3.14159f;
	//float rad = asinf(deg);

	float inner = 0.f * m_moveDirection.x + 1.f * m_moveDirection.y;
	float deg2 = acosf(inner) * 180.f / 3.14159f;

	float dirScale = deg > 0 ? deg2 : -deg2;
	//float dir = deg > 0 ? m_AngulerSpeed * delta : -m_AngulerSpeed * delta;


	// �׽�Ʈ��
	//Render::DrawRotateImage((int)m_pos.x, (int)m_pos.y + 100.f, m_FishImage, dirScale);
	Render::DrawRotateImage((int)m_pos.x - m_renderBounds.extents.x, (int)m_pos.y - m_renderBounds.extents.y, m_FishImage, dirScale);
	//Render::DrawRect(m_pos.x - 50.f, m_pos.y - 50.f, 100, 100, RGB(0, 255, 0));
	//Render::DrawImage(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, m_FishImage, 0, 0, (int)m_renderBounds.extents.x * 2, (int)m_renderBounds.extents.y * 2);

	Render::DrawLine((int)m_pos.x - m_renderBounds.extents.x,
		(int)m_pos.y + m_renderBounds.extents.y,
		(int)m_pos.x + m_renderBounds.extents.x,
		(int)m_pos.y + m_renderBounds.extents.y - 1, RGB(0, 255, 0));
	Render::DrawLine((int)m_pos.x - m_renderBounds.extents.x,
		(int)m_pos.y - m_renderBounds.extents.y,
		(int)m_pos.x + m_renderBounds.extents.x,
		(int)m_pos.y - m_renderBounds.extents.y + 1, RGB(0, 255, 0));
	Render::DrawLine((int)m_pos.x - m_renderBounds.extents.x,
		(int)m_pos.y + m_renderBounds.extents.y,
		(int)m_pos.x - m_renderBounds.extents.x + 1,
		(int)m_pos.y - m_renderBounds.extents.y, RGB(0, 255, 0));
	Render::DrawLine((int)m_pos.x + m_renderBounds.extents.x - 1,
		(int)m_pos.y + m_renderBounds.extents.y,
		(int)m_pos.x + m_renderBounds.extents.x,
		(int)m_pos.y - m_renderBounds.extents.y, RGB(0, 255, 0));

	Render::DrawLine(x1, y1, x2, y1 + 1, RGB(0, 255, 0));
	Render::DrawLine(x1, y2, x2, y2 - 1, RGB(0, 255, 0));
	Render::DrawLine(x1, y1, x1 + 1, y2, RGB(0, 255, 0));
	Render::DrawLine(x2, y1, x2 - 1, y2 - 1, RGB(0, 255, 0));

	//Render::DrawText(10, 10, std::to_string(dirScale).c_str(), RGB(255, 0, 0));
	Render::DrawTextW(10, 70, std::to_string(time).c_str(), RGB(255, 0, 0));
}

void Fish::OnTrigger() {
	m_isActive = false;
}