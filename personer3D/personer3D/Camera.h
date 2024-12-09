#pragma once
#include "../common/InputSystem.h"

class Camera : public InputPrecesser
{
private:
	Vector3 m_InitPos = { 0,0,-100 };

	Vector3 m_InputVector;

	float m_RotationSpeed = 0.004f;
public:
	Camera();
	~Camera() = default;

	Vector3 GetForward();
	Vector3 GetRight();
	Matrix m_World;
	Vector3 m_Position;
	Vector3 m_Rotation;

	float m_Speed = 60.0f;

	void Reset();
	void Update(float DeltaTime);
	void GetViewMatrix(Matrix& ViewMatrix);
	void AddInputVector(const Vector3& input);
	void SetSpeed(float speed) { m_Speed = speed; }
	void AddPitch(float angle);
	void AddYaw(float angle);

	void OnInputProcess(const Keyboard::State& KeyState, const Keyboard::KeyboardStateTracker& KeyTracker,
		const Mouse::State& MouseState, const Mouse::ButtonStateTracker& MouseTracker) override;
};

