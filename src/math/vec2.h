#pragma once

class Vec2
{
public:
	float x;
	float y;

	Vec2();
	Vec2(float ix, float iy);

	Vec2& operator=(const Vec2& v);
};