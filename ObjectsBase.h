#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <memory>
#include <string>
#include <SOIL/SOIL.h>
#include <map>
#include <functional>

#include "Shaders.h"
#include "GLMath.h"

// Forward declare reference-looped class
class ObjectContainer;

class Object3D
{
public:
	Object3D() = delete;
	Object3D(const Object3D& Src) = delete;
	Object3D& operator=(const Object3D& Src) = delete;
	virtual ~Object3D();

	const std::string& GetLabel() const;
	virtual std::shared_ptr<Object3D> MakeCopyNamed(const std::string& newLabel) const;

	ObjectContainer& GetContainer();

	virtual void Draw(const mat4& projectionViewMatrix);
	void SetTickTock(std::function<void(std::shared_ptr<Object3D>&, float)> tickTock);
	std::function<void(std::shared_ptr<Object3D>&, float)> GetTickTock() const;

	void SetPosition(const float3& newPos);
	const float3& Position() const;
	void Translate(const float3& vector);
	void SetScale(const float3& newScale);
	void Rotate(const Quaternion& rotation);
	void SetVelocity(const float3& velocity);
	const float3& Velocity() const;
	void Transform(const mat4& transform);

	void Texture(const std::string& ImgFilename);
	void ColourSolid(const float3& redGreenBlue);		// [0 - 1] range

	bool Drawing2D() const;

protected:
	// Unique label for the object (at least for the container its in)
	const std::string objectLabel;

	// A container of sub-contained items that we are responsible for the rendering of
	ObjectContainer container;

	// Draw properties
	float3 position;
	mat4 rotationMatrix;
	float3 velocity;
	float3 scale;
	bool draw2D;
	mat4 modelMatrix;

	// OpenGL stuff
	float3* vertices;
	float2* texCoords;
	std::string textureFilepath, vertShaderFile, fragShaderFile;
	GLuint vaoId, vboId, texCoordBufferId, textureId;
	const unsigned int verts;
	const bool useCoords;
	const GLenum mode;
	GLuint programId, fragmentShaderId, vertexShaderId;
	bool initialized;

	// Allocate vertice and texCoord arrays from vert and coord counts, and set draw mode and label
	Object3D(const std::string& label, int Verts, bool UseTexCoords, int Mode);

	// An update callback for applying things over time (passes self and delta time between frames)
	std::function<void(std::shared_ptr<Object3D>&, float)> tickTockCallback;

	// // Creates VertexArrayObject and VertexBufferObject for vertices and TexCoords
	void SetupVerticesAndInitialize();

	// Opens the specified shader files & compiles/links them and opens ImgFilename as texture if non-empty
	void SetShaders(const std::string& vertName, const std::string& fragName, const std::string& ImgFilename = "");
	void ClearShaders();
	void SetShaders() {
		SetShaders("dummy.glslv", "dummy.glslf");
	}

	// Updates model matrix from position rotation and scale
	void UpdateModelMatrix();
};
