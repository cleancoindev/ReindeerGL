#pragma once
#include "float3.h"

class Quaternion
{
public:
	float x, y, z, w;

	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(float k);
	Quaternion(const float3& num, float w = 1);
	Quaternion(const Quaternion& q);

  	float Magnitude() const;
	void Normalize();
	void Normalize3();
	Quaternion Conjugate() const;
	float3 ToFloat3() const;
	Quaternion operator* (const Quaternion& Src) const;
	Quaternion& operator*= (const Quaternion& Src);
	Quaternion& operator+= (const float3& Src);
	Quaternion& operator-= (const float3& Src);
	Quaternion& operator= (const Quaternion& Src);
};
