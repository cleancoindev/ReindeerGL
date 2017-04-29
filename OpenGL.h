#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <memory>
#include <math.h>
#include <SOIL/SOIL.h>
#include <chrono>

#include "ObjectContainer.h"
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
	void Fullscreen();
	bool IsFullscreen() const;
	void Wireframe();
	bool IsFilling() const;
	void SaveScreenshot(const std::string& filename);

	template<class subObject>
	std::shared_ptr<subObject> AddNewObject(const std::string& newLabel, const std::string& optionalTextureFile = "")
	{
		std::shared_ptr<subObject> subObjPtr = std::make_shared<subObject>(newLabel, optionalTextureFile);
		topLevelContainer.AddObjectPtr(OBJECT3D_PTR(subObjPtr));
		return subObjPtr;
	}
	template<class subObject>
	void AddAnObjectPtr(const std::shared_ptr<subObject>& subObjPtr)
	{
		topLevelContainer.AddObjectPtr(OBJECT3D_PTR(subObjPtr));
	}

	void StartFPS();
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
	const float fieldOfView = 90;

	unsigned int frameCount;
	float framesPerSecond;
	std::chrono::high_resolution_clock::time_point previousTime;
	float deltaTime;
	void CalcFPS();

	ObjectContainer topLevelContainer;
};
