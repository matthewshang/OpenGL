#ifndef VEC3F_H
#define VEC3F_H

#include <cmath>

class Vec3
{
public:
	float x;
	float y;
	float z;

	Vec3();
	Vec3(float ix, float iy, float iz);

	Vec3& normalize();
	float length();
	Vec3 cross(const Vec3& v);

	Vec3& operator=(const Vec3& v);
	Vec3& operator+=(const Vec3& v);
	Vec3 operator+(const Vec3& v);
	Vec3& operator-=(const Vec3& v);
	Vec3 operator-(const Vec3& v);
	Vec3 operator*(float s);
	Vec3& operator*=(float s);
	float operator*(const Vec3& v);
};

#endif