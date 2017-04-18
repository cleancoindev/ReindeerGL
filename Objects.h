#pragma once
#include "ObjectsBase.h"
#include "GLMath.h"

#include <string>


class CubeObj: public Object3D
{
public:
	CubeObj(const std::string& label, const std::string& texturePath);
};

class LineObj: public Object3D
{
public:
	LineObj(const std::string& label, const std::string& texturePath);
};

class PlaneObj: public Object3D
{
public:
	PlaneObj(const std::string& label, const std::string& texturePath);
};

// class SphereObj: public Object3D
// {
// public:
// 	SphereObj(const std::string& label, unsigned int n, const std::string& texturePath);

// private:
// 	unsigned int SphereFindPoint(unsigned int n);
// };

class Triangle: public Object3D
{
public:
	Triangle(const std::string& label, const std::string& texturePath);
};

class MeshObj : public Object3D
{
public:
	MeshObj(const std::string& label, unsigned int X, unsigned int Y, const std::string& texfilePath, const std::string& vertShaderFile, const std::string& fragShaderFile);

	void SetXAxisRange(float low, float high);
	void SetYAxisRange(float low, float high);

private:
	const unsigned int x;
	const unsigned int y;

	float2 xRange;
	float2 yRange;
};
