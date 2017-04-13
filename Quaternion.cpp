#include "Quaternion.h"
#include <cmath>

Quaternion::Quaternion()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion::Quaternion(float k)
{
	x = k;
	y = k;
	z = k;
	w = k;
}

Quaternion::Quaternion(const float3& num, float W)
{
	x = num.x();
	y = num.y();
	z = num.z();
	w = W;
}

Quaternion::Quaternion(const Quaternion& q)
{
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
}

float Quaternion::Magnitude() const
{
  	return sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

void Quaternion::Normalize()
{
	float magnitude = Magnitude();
	if(magnitude)
	{
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		w /= magnitude;
	}
}
void Quaternion::Normalize3()
{
	float magnitude = sqrt((x * x) + (y * y) + (z * z));
	if(magnitude)
	{
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}
}

Quaternion Quaternion::Conjugate() const
{
	return Quaternion(-x, -y, -z, w);
}

float3 Quaternion::ToFloat3() const
{
	return float3(x, y, z);
}

Quaternion Quaternion::operator* (const Quaternion& Src) const
{
	return Quaternion  ((w*Src.x) + (x*Src.w) + (y*Src.z) - (z*Src.y),\
						(w*Src.y) - (x*Src.z) + (y*Src.w) + (z*Src.x),\
						(w*Src.z) + (x*Src.y) - (y*Src.x) + (z*Src.w),\
						(w*Src.w) - (x*Src.x) - (y*Src.y) - (z*Src.z));
}

Quaternion& Quaternion::operator*= (const Quaternion& Src)
{
	float xP = x;
	float yP = y;
	float zP = z;
	float wP = w;

	x = (wP*Src.x) + (xP*Src.w) + (yP*Src.z) - (zP*Src.y);
	y = (wP*Src.y) - (xP*Src.z) + (yP*Src.w) + (zP*Src.x);
	z = (wP*Src.z) + (xP*Src.y) - (yP*Src.x) + (zP*Src.w);
	w = (wP*Src.w) - (xP*Src.x) - (yP*Src.y) - (zP*Src.z);

	return *this;
}

Quaternion& Quaternion::operator+= (const float3& Src)
{
	x += Src.x();
	y += Src.y();
	z += Src.z();
	return *this;
}

Quaternion& Quaternion::operator-= (const float3& Src)
{
	x -= Src.x();
	y -= Src.y();
	z -= Src.z();
	return *this;
}

Quaternion& Quaternion::operator= (const Quaternion& Src)
{
	x = Src.x;
	y = Src.y;
	z = Src.z;
	w = Src.w;
	return *this;
}
