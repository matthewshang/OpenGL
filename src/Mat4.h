#ifndef MAT4_H
#define MAT4_h

#include <cmath>

#include "Vec3.h"
#include "Quaternion.h"
#include "MathUtils.h"

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

	Vec3 mulVec3(Vec3 v, float w);

	Mat4 operator*(const Mat4& a);

private:
	void setZero();
	void setIdentity();

	float m[16];
};

#endif