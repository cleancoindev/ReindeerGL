#include <cmath>
#include "float2.h"

float2::float2(float x, float y)
{
	n[0] = x;
	n[1] = y;
}

float2::float2(float k)
{
	n[0] = k;
	n[1] = k;
}

float2::float2()
{
	n[0] = 0;
	n[1] = 0;
}

float& float2::x()
{
	return n[0];
}

float& float2::y()
{
	return n[1];
}

float float2::x() const
{
	return n[0];
}

float float2::y() const
{
	return n[1];
}

float float2::Magnitude() const
{
	return sqrt((x() * x()) + (y() * y()));
}

void float2::Normalize()
{
	float mag = Magnitude();
	n[0] /= mag;
	n[1] /= mag;
}

float2& float2::operator= (const float2& Src)
{
	n[0] = Src.x();
	n[1] = Src.y();
	return *this;
}

bool float2::operator== (const float2& cmp) const
{
	if(x() == cmp.x() && y() == cmp.y())
		return true;
	else
		return false;
}
float2& float2::operator+= (const float2& Src)
{
	n[0] += Src.x();
	n[1] += Src.y();
	return *this;
}

float2& float2::operator-= (const float2& Src)
{
	n[0] -= Src.x();
	n[1] -= Src.y();
	return *this;
}

float2 float2::operator+ (const float2& Src) const
{
	return float2(x() + Src.x(), y() + Src.y());
}

float2 float2::operator- (const float2& Src) const
{
	return float2(x() - Src.x(), y() - Src.y());
}

float2 float2::operator- () const
{
	return float2(-x(), -y());
}

float2 float2::operator/ (float Num) const
{
	return float2(x() / Num, y() / Num);
}

float2 float2::operator* (float Num) const
{
	return float2(x() * Num, y() * Num);
}
