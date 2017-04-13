#include "float3.h"

#include <cmath>
#include <utility>
#include <sstream>
#include <iomanip>

float3::float3(float x, float y, float z)
{
	n[0] = x;
	n[1] = y;
	n[2] = z;
}

float3::float3(float k)
{
	n[0] = k;
	n[1] = k;
	n[2] = k;
}

float3::float3()
{
	n[0] = 0;
	n[1] = 0;
	n[2] = 0;
}

float& float3::x()
{
	return n[0];
}

float& float3::y()
{
	return n[1];
}

float& float3::z()
{
	return n[2];
}

float float3::x() const
{
	return n[0];
}

float float3::y() const
{
	return n[1];
}

float float3::z() const
{
	return n[2];
}

void float3::CompWiseDiv(const float3& Src)
{
	n[0] /= Src.x();
  	n[1] /= Src.y();
  	n[2] /= Src.z();
}

void float3::CompWiseMult(const float3& Src)
{
	n[0] *= Src.x();
  	n[1] *= Src.y();
  	n[2] *= Src.z();
}

float float3::Magnitude() const
{
	return sqrt((x() * x()) + (y() * y()) + (z() * z()));
}

void float3::Normalize()
{
	float mag = Magnitude();
	if(mag)
	{
		n[0] /= mag;
		n[1] /= mag;
		n[2] /= mag;
	}
}

float3 float3::Norm() const
{
	float3 r(*this);
	r.Normalize();
	return std::move(r);
}

std::string float3::ToString() const
{
	std::stringstream ss;
	ss << "< " << n[0] << " , " << n[1] << " , " << n[2] << " >";

	return ss.str();
}

float3& float3::operator= (const float3& Src)
{
	n[0] = Src.x();
	n[1] = Src.y();
	n[2] = Src.z();
	return *this;
}

bool float3::operator== (const float3& cmp) const
{
	if(x() == cmp.x() && y() == cmp.y() && z() == cmp.z())
		return true;
	else
		return false;
}
float3& float3::operator+= (const float3& Src)
{
	n[0] += Src.x();
	n[1] += Src.y();
	n[2] += Src.z();
	return *this;
}

float3& float3::operator-= (const float3& Src)
{
	n[0] -= Src.x();
	n[1] -= Src.y();
	n[2] -= Src.z();
	return *this;
}

float3 float3::operator+ (const float3& Src) const
{
	return float3(x() + Src.x(), y() + Src.y(), z() + Src.z());
}

float3 float3::operator- (const float3& Src) const
{
	return float3(x() - Src.x(), y() - Src.y(), z() - Src.z());
}

float3 float3::operator- () const
{
	return float3(-x(), -y(), -z());
}

float3 float3::operator/ (float Num) const
{
	return float3(x() / Num, y() / Num, z() / Num);
}

float3 float3::operator* (float Num) const
{
	return float3(x() * Num, y() * Num, z() * Num);
}
