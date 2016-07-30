#include "Mat4.h"

Mat4::Mat4()
{
	setZero();
}

void Mat4::set(int row, int col, float value)
{
	m[row * 4 + col] = value;
}

float Mat4::get(int row, int col) const
{
	return m[row * 4 + col];
}

float* Mat4::getInternal() const
{
	return (float *) m;
}

Mat4 Mat4::createIdentity()
{
	Mat4 i;
	i.set(0, 0, 1.0f);
	i.set(1, 1, 1.0f);
	i.set(2, 2, 1.0f);
	i.set(3, 3, 1.0f);
	return i;
}

Mat4 Mat4::translate(Vec3 trans)
{
	Mat4 t;
	t.setIdentity();
	t.set(0, 3, trans.x);
	t.set(1, 3, trans.y);
	t.set(2, 3, trans.z);
	t.set(3, 3, 1.0f);
	return t;
}

Mat4 Mat4::scale(Vec3 scale)
{
	Mat4 s;
	s.setIdentity();
	s.set(0, 0, scale.x);
	s.set(1, 1, scale.y);
	s.set(2, 2, scale.z);
	s.set(3, 3, 1.0f);
	return s;
}

Mat4 Mat4::rotate(Quaternion q)
{
	Mat4 r;
	q.normalize();
	r.setIdentity();
	Vec3 i = q.getImaginary();
	float w = q.getReal();
	r.set(0, 0, 1.0f - 2.0f * (i.y * i.y + i.z * i.z));
	r.set(0, 1, 2.0f * (i.x * i.y - w * i.z));
	r.set(0, 2, 2.0f * (i.x * i.z + w * i.y));

	r.set(1, 0, 2.0f * (i.x * i.y + w * i.z));
	r.set(1, 1, 1.0f - 2.0f * (i.x * i.x + i.z * i.z));
	r.set(1, 2, 2.0f * (i.y * i.z - w * i.x));

	r.set(2, 0, 2.0f * (i.x * i.z - w * i.y));
	r.set(2, 1, 2.0f * (i.y * i.z + w * i.x));
	r.set(2, 2, 1.0f - 2.0f * (i.x * i.x + i.y * i.y));
	return r;
}

Vec3 Mat4::mulVec3(Vec3 v, float w)
{
	return Vec3(
		v.x * get(0, 0) + v.y * get(0, 1) + v.z * get(0, 2) + w * get(0, 3),
		v.x * get(1, 0) + v.y * get(1, 1) + v.z * get(1, 2) + w * get(1, 3),
		v.x * get(2, 0) + v.y * get(2, 1) + v.z * get(2, 2) + w * get(2, 3)
	);
}

Mat4 Mat4::operator*(const Mat4& a)
{
	Mat4 ret;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ret.set(i, j, get(i, 0) * a.get(0, j) + 
						  get(i, 1) * a.get(1, j) + 
						  get(i, 2) * a.get(2, j) + 
						  get(i, 3) * a.get(3, j));
		}
	}
	return ret;
}

void Mat4::setZero()
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = 0.0f;
	}
}

void Mat4::setIdentity()
{
	setZero();
	set(0, 0, 1.0f);
	set(1, 1, 1.0f);
	set(2, 2, 1.0f);
	set(3, 3, 1.0f);
}