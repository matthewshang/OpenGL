#include "inputstate.h"

#include <cstring>

InputState::InputState(int windowWidth, int windowHeight) : m_firstMouse(true)
{
	std::memset(&m_keys[0], false, 1024);
	m_mouseLast = Vec3((float) windowWidth, (float) windowHeight, 0.0f);
	m_mousePosition = m_mouseLast;
}

bool InputState::keyPressed(int key)
{
	return m_keys[key];
}

Vec3 InputState::getMousePosition()
{
	return m_mousePosition;
}

Vec3 InputState::getMouseLast()
{
	return m_mouseLast;
}

void InputState::updateKey(int key, bool pressed)
{
	m_keys[key] = pressed;
}

void InputState::updateMouse(float xpos, float ypos)
{
	m_mouseLast = m_mousePosition;
	if (m_firstMouse)
	{
		m_mouseLast = Vec3(xpos, ypos, 0.0f);
		m_firstMouse = false;
	}

	m_mousePosition = Vec3(xpos, ypos, 0.0f);
}