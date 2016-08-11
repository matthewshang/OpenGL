#pragma once

#include "vec3.h"

class Quaternion
{
public:
	static Quaternion fromAxisAngle(Vec3 axis, float angle);
	Quaternion();
	Quaternion(Vec3 i, float r);

	Vec3 getImaginary() const;
	float getReal() const;
	
	Quaternion getConjugate();
	Quaternion& normalize();

	Quaternion& operator=(const Quaternion& q);
	Quaternion& operator*=(const Quaternion& v);
	Quaternion operator*(const Quaternion& q);

private:

	Vec3 m_i;
	float m_r;
};