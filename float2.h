#pragma once

class float2
{
public:
	float x() const;
	float y() const;
	float& x();
	float& y();
	float n[2];
	float2(float x, float y);
	float2(float k);
	float2();

 	float Magnitude() const;
  	void Normalize();

	float2& operator= (const float2& Src);
	bool operator== (const float2& cmp) const;
	float2& operator+= (const float2& Src);
	float2& operator-= (const float2& Src);

	float2 operator+ (const float2& Src) const;
	float2 operator- (const float2& Src) const;
	float2 operator- () const;
	float2 operator/ (float Num) const;
	float2 operator* (float Num) const;
};
