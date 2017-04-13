#pragma once

class float3
{
public:
	float x() const;
	float y() const;
	float z() const;
	float& x();
	float& y();
	float& z();
	float n[3];
	float3(float x, float y, float z);
	float3(float k);
	float3();

	void CompWiseDiv(const float3& Src);
	void CompWiseMult(const float3& Src);

 	float Magnitude() const;
  	void Normalize();
	float3 Norm() const;

	float3& operator= (const float3& Src);
	bool operator== (const float3& cmp) const;
	float3& operator+= (const float3& Src);
	float3& operator-= (const float3& Src);

	float3 operator+ (const float3& Src) const;
	float3 operator- (const float3& Src) const;
	float3 operator- () const;
	float3 operator/ (float Num) const;
	float3 operator* (float Num) const;
};
