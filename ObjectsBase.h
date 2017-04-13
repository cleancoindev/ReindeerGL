#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <memory>
#include <string>
#include <SOIL/SOIL.h>

#include "Shaders.h"
#include "GLMath.h"

#define MEMBER_OFFSET(s,m) ((char *)NULL + (offsetof(s,m)))

class Object3D
{
public:
	float Mass;

	Object3D() = delete;
	Object3D(const Object3D& Src) = delete;
	Object3D& operator=(Object3D& Src) = delete;
	~Object3D();

	void Draw(const mat4& projectionViewMatrix);

	void SetPosition(const float3& newPos);
	void Translate(const float3& vector);
	void SetScale(const float3& newScale);
	void Rotate(const Quaternion& rotation);
	void SetVelocity(const float3& velocity);
	void Transform(const mat4& transform);

protected:
	float3 position;
	mat4 rotationMatrix;
	float3 velocity;
	float3 scale;

	float3* vertices;
	float2* texCoords;
	std::string TexFile;
	mat4 modelMatrix;
	GLuint vaoId, vboId, texCoordBufferId, textureId;
	const unsigned int verts, coords;
	const GLenum mode;

	GLuint programId, fragmentShaderId, vertexShaderId;
	bool initialized;

	Object3D(int Verts, int Coords, int Mode);
	void SetupVerticesAndShaders(const std::string& ImgName, const std::string& vertName = "dummy.glslv", const std::string& fragName = "dummy.glslf");
	void UpdateModelMatrix();
};
