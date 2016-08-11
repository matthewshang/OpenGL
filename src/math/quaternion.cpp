#include "quaternion.h"

#include <cmath>

Quaternion::Quaternion()
{
	m_r = 0.0f;
}

Quaternion::Quaternion(Vec3 i, float r)
{
	m_i = i;
	m_r = r;
}

Vec3 Quaternion::getImaginary() const
{
	return m_i;
}

float Quaternion::getReal() const
{
	return m_r;
}

Quaternion Quaternion::fromAxisAngle(Vec3 axis, float angle)
{
	float halfAngle = angle / 2.0f;
	return Quaternion(axis.normalize() * sin(halfAngle), cos(halfAngle));
}

Quaternion Quaternion::getConjugate()
{
	return Quaternion(m_i * -1.0f, m_r);
}

Quaternion& Quaternion::normalize()
{
	float inv = 1 / sqrt(m_i.x * m_i.x + m_i.y * m_i.y + m_i.z * m_i.z + m_r * m_r);
	m_i *= inv;
	m_r *= inv;
	return *this;
}

Quaternion& Quaternion::operator=(const Quaternion& q)
{
	m_i = q.getImaginary();
	m_r = q.getReal();
	return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& v)
{
	Vec3 vi = v.getImaginary();
	float vr = v.getReal();
	m_i = m_i.cross(vi) + vi * m_r + m_i * vr;
	m_r = m_r * vr - vi * m_i;
	return *this;
}

Quaternion Quaternion::operator*(const Quaternion& q)
{
	Quaternion v = *this;
	v *= q;
	return v;
}