#pragma once
#include "ObjectsBase.h"
#include "GLMath.h"

#include <string>


class CubeObj: public Object3D
{
public:
	CubeObj(const std::string& texturePath);
};

class LineObj: public Object3D
{
public:
	LineObj(const std::string& texturePath);
};

class PlaneObj: public Object3D
{
public:
	PlaneObj(const std::string& texturePath);
};

class SphereObj: public Object3D
{
public:
	SphereObj(unsigned int n, float radius);

private:
	unsigned int SphereFindPoint(unsigned int n);
};


class GravityPlane: public Object3D
{
public:
	GravityPlane();
	GLuint GetP() const;
};

class Triangle: public Object3D
{
public:
	Triangle();
};
