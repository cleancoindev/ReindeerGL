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

class SphereObj: public Object3D
{
public:
 // Number of vertices = 3 * 8 * 4^n = 3 * 2^3 * 2^(2n) = 3 * 2^(2n + 3) (or 8*4^n triangles)
	SphereObj(const std::string& label, const unsigned int n, const std::string& texturePath);

private:
	float2 PointToTexcoord(const float3& normPoint);
};

class Triangle: public Object3D
{
public:
	Triangle(const std::string& label, const std::string& texturePath);
};

class MeshObj : public Object3D
{
public:
	const unsigned int x;
	const unsigned int y;

	MeshObj(const std::string& label, const unsigned int X, const unsigned int Y, const std::string& texfilePath, const std::string& vertShaderFile, const std::string& fragShaderFile, const bool useTexCoords = true);

	void SetXAxisRange(float low, float high);
	void SetYAxisRange(float low, float high);

protected:
	float2 xRange;
	float2 yRange;

	void SetVertsFromGrid(const std::unique_ptr<float3[/*must be size x*y, y major order*/]>& arrayOfPositions);
	static std::unique_ptr<float3[]> CreateGridMesh(unsigned int X, unsigned int Y);
};
