#include "Camera.h"

Camera::Camera(Vec3 position, float lookSens, float moveSpeed) : 
	m_position(position),
	m_front(Vec3(0.0f, 0.0f, -1.0f)),
	m_up(Vec3(0.0f, 1.0f, 0.0f)),
	m_pitch(0.0f),
	m_yaw(-90.0f),
	m_worldUp(Vec3(0.0f, 1.0f, 0.0f)),
	m_lookSens(1.0f / lookSens),
	m_moveSpeed(moveSpeed)
{
	updateVectors();
}

Mat4 Camera::getViewMatrix()
{
	return Mat4::lookAt(m_position, m_position + m_front, m_up);
}

Vec3 Camera::getPosition()
{
	return m_position;
}

void Camera::update(float delta, InputState& input)
{
	float d = m_moveSpeed * delta;
	if (input.keyPressed(InputState::KEY_W))
	{
		m_position += m_front * d;
	}
	if (input.keyPressed(InputState::KEY_S))
	{
		m_position -= m_front * d;
	}
	if (input.keyPressed(InputState::KEY_A))
	{
		m_position -= m_right * d;
	}
	if (input.keyPressed(InputState::KEY_D))
	{
		m_position += m_right * d;
	}
	if (input.keyPressed(InputState::KEY_SPACE))
	{
		m_position += m_worldUp * d;
	}
	if (input.keyPressed(InputState::KEY_LEFT_SHIFT))
	{
		m_position -= m_worldUp * d;
	}

	float xOff = input.getMousePosition().x - input.getMouseLast().x;
	float yOff = input.getMouseLast().y - input.getMousePosition().y;
	m_yaw += xOff * m_lookSens;
	m_pitch += yOff * m_lookSens;
	if (m_pitch > 89.0f)
	{
		m_pitch = 89.0f;
	}
	else if (m_pitch < -89.0f)
	{
		m_pitch = -89.0f;
	}
	updateVectors();
}

void Camera::updateVectors()
{
	Vec3 front;
	front.x = cos(MathUtils::toRadians(m_pitch)) * cos(MathUtils::toRadians(m_yaw));
	front.y = sin(MathUtils::toRadians(m_pitch));
	front.z = cos(MathUtils::toRadians(m_pitch)) * sin(MathUtils::toRadians(m_yaw));
	front.normalize();
	m_front = front;
	m_right = m_front.cross(m_worldUp);
	m_right.normalize();
	m_up = m_right.cross(m_front);
}