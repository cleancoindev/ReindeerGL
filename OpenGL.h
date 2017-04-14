#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <memory>
#include <math.h>
#include <SOIL/SOIL.h>

#include "Objects.h"
#include "Shaders.h"
#include "GLMath.h"

#define OBJECT3D_PTR(ptr) std::static_pointer_cast<Object3D>(ptr)

class OpenGL
{
public:
	float3 Position;
	float3 Rotation;
	float3 Velocity;

	OpenGL() = default;
	OpenGL(int argc, char** argv, int width, int height, const std::string& Title);
	void GLInit(int argc, char** argv, int width, int height, const std::string& Title);
	void DrawAll();
	void CalcFPS();
	void StartFPS();
	void Fullscreen();
	bool IsFullscreen() const;
	void Wireframe();
	bool IsFilling() const;
	void SaveScreenshot(const std::string& filename);

	std::shared_ptr<CubeObj> AddCube(const std::string& textureFile);
	void AddCube(const std::shared_ptr<CubeObj>& cube);
	std::shared_ptr<LineObj> AddLine(const std::string& textureFile);
	void AddLine(const std::shared_ptr<LineObj>& cube);
	std::shared_ptr<PlaneObj> AddPlane(const std::string& textureFile);
	void AddPlane(const std::shared_ptr<PlaneObj>& cube);
	std::shared_ptr<Triangle> AddTriangle(const std::string& textureFile);
	void AddTriangle(const std::shared_ptr<Triangle>& tri);
	void AddObject(const std::shared_ptr<Object3D>& object);

	float FramesPerSecond() const;
	GLuint WindowId() const;
	float DeltaTime() const;
	int Width() const;
	int Height() const;
	void SetCurrentWindowSize(const unsigned int width, const unsigned int height);
	void ShowCursor(bool show) const;

private:
	GLuint windowId;
	int width, height;
	bool filling, fullscreen;
	unsigned int frameCount;
	float framesPerSecond;
	unsigned int currentTime, previousTime, elapsedTime;
	float deltaTime;
	const float fieldOfView = 90;

	std::vector<std::shared_ptr<Object3D>> objects;
};
