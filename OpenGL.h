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
	void Wireframe();
	void SaveScreenshot(const std::string& filename);

	std::shared_ptr<CubeObj> AddCube(const std::string& textureFile);
	std::shared_ptr<LineObj> AddLine(const std::string& textureFile);
	std::shared_ptr<PlaneObj> AddPlane(const std::string& textureFile);
	void AddObject(std::shared_ptr<Object3D> object);

	float FramesPerSecond() const;
	GLuint WindowId() const;
	float DeltaTime() const;
	int Width() const;
	int Height() const;

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
