#pragma once

#include "vec3.h"
#include "quaternion.h"

class Mat4
{
public:
	Mat4();

	void set(int row, int col, float value);
	float get(int row, int col) const;
	float* getInternal() const;

	static Mat4 createIdentity();
	static Mat4 translate(Vec3 trans);
	static Mat4 scale(Vec3 scale);
	static Mat4 rotate(Quaternion q);
	static Mat4 perspective(float fov, float aspect, float near, float far);
	static Mat4 lookAt(Vec3 pos, Vec3 target, Vec3 up);

	Vec3 mulVec3(Vec3 v, float w);

	Mat4 operator*(const Mat4& a);

private:
	void setZero();
	void setIdentity();

	float m[16];
};