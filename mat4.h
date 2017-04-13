#pragma once
#include "Quaternion.h"

class mat4
{
public:
	float p[4][4];

	mat4();
	mat4(float num);
	mat4(float* m);
	mat4(const mat4& A);

	mat4 operator* (const mat4& B) const;
	Quaternion operator* (const Quaternion& q) const;
	float3 operator* (const float3& vec) const;

	mat4& operator= (const mat4& Src);
	bool operator== (const mat4& Src) const;
};
