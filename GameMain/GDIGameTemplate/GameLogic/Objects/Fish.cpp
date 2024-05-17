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
	Vector2 position = GetRandomPosition();
	float distance = sqrtf(pow(m_pos.x - position.x, 2) + pow(m_pos.y - position.y, 2)); // �Ÿ��� �� �ð��� ��.
	maxTime = distance / m_speed;
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

Fish::Fish(const WCHAR* name, float moveSpeed, float angulerSpeed, const WCHAR* fileName, CResourceManager* CRM, const WCHAR* imageType, float rotateInterval1, float rotateInterval2, float colliderWidth, float colliderHeight)
{
	memset(m_name, '\0', 255);
	wcscpy_s(m_name, 255, name);

	m_speed = moveSpeed;
	angulerSpeed = m_AngulerSpeed;
	LoadAnimImage(fileName, CRM, imageType);
	m_rotateInterval1 = rotateInterval1;
	m_rotateInterval2 = rotateInterval2;

	m_collider = new RectangleCollider({ 0.f,0.f }, colliderWidth, colliderHeight);
	m_collider->parent = this;

	Init();
}

void Fish::Init() {
	// �׽�Ʈ��
	
	m_renderBounds = { {0.f, 0.f}, {m_bitmap[0]->GetWidth() / 2.f, m_bitmap[0]->GetHeight() / 2.f}};
	m_pos = GetRandomPosition();
	m_moveDirection = GetRandomDirection() * -1.f;

	animationFrame = rand() % 30;
}

void Fish::Update(float delta) {
	if (m_isActive == false) return;
	time += delta;
	if (time > maxTime) {
		m_AngulerDirection = GetRandomDirection();
		time = 0;
	}

	if (isCatch) {
		alphaTime -= delta;
		if (alphaTime <= 0) {
			alphaTime = 0.f;
			m_isActive = false;
			isCatch = false;
		}
	}

	if (!isCatch) {
		Move(delta);

		if (m_AngulerDirection != Vector2(0.f, 0.f))
			AngularVelocity(delta);

		animTime += delta;
		if (animTime >= animMaxTime) {
			animTime -= animMaxTime;
			animationFrame = (animationFrame + 1) % 30;
		}
	}
}

void Fish::Render(float alpha) {
	if (m_isActive == false) return;

	float deg = (0.f * m_moveDirection.y + 1.f * m_moveDirection.x);  // ȸ������ ���ϱ�

	float inner = 0.f * m_moveDirection.x - 1.f * m_moveDirection.y;
	float deg2 = acosf(inner) * 180.f / 3.14159f;

	float dirScale = deg > 0 ? deg2 : -deg2;

	Render::DrawRotateImage((int)m_pos.x - m_renderBounds.extents.x, (int)m_pos.y - m_renderBounds.extents.y, m_bitmap[animationFrame], dirScale, alphaTime);

	RectangleCollider* r = dynamic_cast<RectangleCollider*>(m_collider);
	
	// �׽�Ʈ��
	Render::DrawRect(m_pos.x - r->bounds.extents.x, m_pos.y - r->bounds.extents.y, r->bounds.extents.x * 2, r->bounds.extents.x * 2, RGB(0, 255, 0));

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

	////Render::DrawText(10, 10, std::to_string(dirScale).c_str(), RGB(255, 0, 0));
	//Render::DrawTextW(10, 70, std::to_string(time).c_str(), RGB(255, 0, 0));
}

void Fish::OnTrigger() {
	isCatch = true;
	m_collider->isActive = false;
}

void Fish::SetRandomPosition()
{
	m_pos = GetRandomPosition();
}

void Fish::LoadAnimImage(const WCHAR* fileName, CResourceManager* CRM, const WCHAR* imageType)
{
	int fileNameLength = wcslen(fileName);

	m_fileName[0] = fileName;
	m_bitmap[0] = CRM->LoadBitmapResouce(fileName, fileName);
	std::wstring noNumFileName = m_fileName[0].substr(0, fileNameLength - 6);

	for (int i = 1; i < 30; i++) {
		std::wstring wZero = std::to_wstring(0);

		std::wstring wNum = std::to_wstring(i);
		if (i < 10) {
			m_fileName[i] = noNumFileName.append(wZero).append(wNum);
		}
		else {
			m_fileName[i] = noNumFileName.append(wNum);
		}

		m_bitmap[i] = CRM->LoadBitmapResouce(m_fileName[i].c_str(), m_fileName[i].append(imageType).c_str());
		noNumFileName = noNumFileName.substr(0, fileNameLength - 6);
	}
}
