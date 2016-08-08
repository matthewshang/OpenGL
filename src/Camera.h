#ifndef CAMERA_H
#define CAMERA_H

#include "math/Vec3.h"
#include "math/Mat4.h"
#include "math/MathUtils.h"
#include "InputState.h"

class Camera
{
public:
	enum Movement
	{
		FOWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	Camera(Vec3 position, float lookSens, float moveSpeed);

	const Vec3& getPosition();
	const Vec3& getFront();

	void update(float delta, InputState& input);
	Mat4 getViewMatrix();

private:
	Vec3 m_position;
	Vec3 m_front;
	Vec3 m_up;
	Vec3 m_right;
	float m_pitch;
	float m_yaw;
	const Vec3 m_worldUp;
	const float m_lookSens;
	const float m_moveSpeed;

	void updateVectors();
};

#endif