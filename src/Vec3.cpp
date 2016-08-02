#include "Vec3.h"

Vec3::Vec3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vec3::Vec3(float ix, float iy, float iz)
{
	x = ix;
	y = iy;
	z = iz;
}

Vec3& Vec3::normalize()
{
	float len = length();
	x /= len;
	y /= len;
	z /= len;
	return *this;
}

float Vec3::length()
{
	return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::cross(const Vec3& v)
{
	return Vec3(v.z * y - v.y * z,
		        v.x * z - v.z * x,
				v.y * x - v.x * y);
}

Vec3& Vec3::operator=(const Vec3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vec3& Vec3::operator+=(const Vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vec3 Vec3::operator+(const Vec3& v)
{
	return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3& Vec3::operator-=(const Vec3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vec3 Vec3::operator-(const Vec3& v)
{
	return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3 Vec3::operator*(float s)
{
	return Vec3(x * s, y * s, z * s);
}

Vec3& Vec3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

float Vec3::operator*(const Vec3& v)
{
	return x * v.x + y * v.y + z * v.z;
}