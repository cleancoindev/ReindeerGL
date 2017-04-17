#pragma once
#include "float3.h"
#include "float2.h"
#include "Quaternion.h"
#include "mat4.h"

namespace GLMath
{
	const float PI = 3.14159265358979f;

	float3 Cross(const float3& a, const float3& b);
	float Dot(const float3& a, const float3& b);
	float Dot(const float2& a, const float2& b);

	mat4 Rotate(Quaternion q);
	mat4 RotateX(const float& angle);
	mat4 RotateY(const float& angle);
	mat4 RotateZ(const float& angle);
	mat4 Rotate(const float3& axisAngles);
  	mat4 Translate(const float3& n);
	mat4 Scale(const float3& s);
  	mat4 Scale(float x, float y, float z);
  	mat4 Perspective(float fov, float ratio, float nearZ, float farZ);
  	mat4 Identity();
	mat4 Inverse(const mat4& M);
}
