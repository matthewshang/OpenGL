#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>

#include "Vec3.h"

class Quaternion
{
public:
	static Quaternion fromAxisAngle(Vec3 axis, float angle);
	Quaternion();

	Vec3 getImaginary() const;
	float getReal() const;
	
	Quaternion getConjugate();
	Quaternion& normalize();

	Quaternion& operator*=(const Quaternion& v);

private:
	Quaternion(Vec3 i, float r);

	Vec3 m_i;
	float m_r;
};

#endif;