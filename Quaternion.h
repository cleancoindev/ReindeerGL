#pragma once
#include "float3.h"

#include <string>

class Quaternion
{
public:
	float x, y, z, w;

	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(float k);
	Quaternion(const float3& num, float w = 0);
	Quaternion(const Quaternion& q);

	float3 RotatePoint(const float3& p) const;
  	float Magnitude() const;
	void Normalize();
	void Normalize3();
	Quaternion Conjugate() const;
	float3 ToFloat3() const;
	std::string ToString() const;

	Quaternion operator* (const Quaternion& Src) const;
	Quaternion& operator*= (const Quaternion& Src);
	Quaternion& operator+= (const float3& Src);
	Quaternion& operator-= (const float3& Src);
	Quaternion& operator= (const Quaternion& Src);
};
