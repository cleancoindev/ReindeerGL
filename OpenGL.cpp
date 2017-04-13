#include "OpenGL.h"
#include "Shaders.h"

#include <iostream>
#include <fstream>
#include <SOIL/SOIL.h>
#include <string.h>


OpenGL::OpenGL(int argc, char** argv, int width, int height, const std::string& title)
{
	GLInit(argc, argv, width, height, title);
}

void OpenGL::GLInit(int argc, char** argv, int width, int height, const std::string& title)
{
	filling = true;
	fullscreen = false;
	//Position = float3(1.570796327, 0, 0);
	framesPerSecond = 60.0f;						// not the worst guess
	deltaTime = 0.0f;

	// FREEGLUT
	glutInit(&argc, argv);
	glutInitContextVersion(4, 2);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	if((windowId = glutCreateWindow(title.c_str())) < 1)
	{
		std::cerr << "Failed to create GLUT window\n";
		return;
	}

	// GLEW
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW\n";
		return;
	}

	// GL
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2, 0.3, 0.1, 1.0);
	int fbWidth = width, fbHeight = height;
	glViewport(0, 0, fbWidth, fbHeight);
}

void OpenGL::DrawAll()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH);
	CalcFPS();

	// mat4 projectionViewMatrix = GLMath::Perspective(fieldOfView, float(width) / float(height), 0.2f, 3000.0f) * GLMath::Rotate(Rotation) * GLMath::Translate(-Position);
	// mat4 projectionViewMatrix = GLMath::Perspective(fieldOfView, float(width) / float(height), 0.2f, 3000.0f) * GLMath::Translate(-Position);
	mat4 projectionViewMatrix = GLMath::Perspective(fieldOfView, 16.0f/9.0f, 0.2f, 1000.0f) * GLMath::Rotate(Rotation) * GLMath::Translate(-Position);

	for(std::shared_ptr<Object3D> object : objects)
	{
		object->Draw(projectionViewMatrix);
	}

	glutSwapBuffers();
    glutPostRedisplay();
}

void OpenGL::CalcFPS()
{
	frameCount++;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	if(currentTime - previousTime > 200)
	{
		framesPerSecond = frameCount * 1000.0f / (currentTime - previousTime);
		deltaTime = 1.0f / framesPerSecond;
		previousTime = currentTime;
		frameCount = 0;
	}
}

void OpenGL::StartFPS()
{
	previousTime = glutGet(GLUT_ELAPSED_TIME);
}

void OpenGL::Fullscreen()
{
	fullscreen ? glutReshapeWindow(800, 600) : glutFullScreen();
	fullscreen = !fullscreen;
}

void OpenGL::Wireframe()
{
	filling = !filling;
	filling ? glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void OpenGL::SaveScreenshot(const std::string& filename)
{
	glReadBuffer(GL_FRONT);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	unsigned char* img = new unsigned char[width * height * 3];
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, img);
	unsigned char* swapSpace = new unsigned char[width * height * 3];
	const int bytesPerRow = width * 3;
	for(unsigned int i = 0; i < height; i++)
	{
		memcpy(&swapSpace[i * bytesPerRow], &img[(height - i - 1) * bytesPerRow], bytesPerRow);
	}

	if(!SOIL_save_image(filename.c_str(), SOIL_SAVE_TYPE_BMP, width, height, 3, swapSpace))
	{
		std::cerr << "SaveScreenshot failed\n";
	}
	else
	{
		std::cerr << "SaveScreenshot succeeded\n";
	}
	delete[] img;
	delete[] swapSpace;
}

std::shared_ptr<CubeObj> OpenGL::AddCube(const std::string& textureFile)
{
	std::shared_ptr<CubeObj> cubePtr = std::make_shared<CubeObj>(textureFile);
	objects.push_back(std::static_pointer_cast<Object3D>(cubePtr));
	return cubePtr;
}

std::shared_ptr<LineObj> OpenGL::AddLine(const std::string& textureFile)
{
	std::shared_ptr<LineObj> linePtr = std::make_shared<LineObj>(textureFile);
	objects.push_back(std::static_pointer_cast<Object3D>(linePtr));
	return linePtr;
}

std::shared_ptr<PlaneObj> OpenGL::AddPlane(const std::string& textureFile)
{
	std::shared_ptr<PlaneObj> planePtr = std::make_shared<PlaneObj>(textureFile);
	objects.push_back(std::static_pointer_cast<Object3D>(planePtr));
	return planePtr;
}

void OpenGL::AddObject(std::shared_ptr<Object3D> object)
{
	objects.push_back(object);
}

float OpenGL::FramesPerSecond() const
{
	return framesPerSecond;
}

GLuint OpenGL::WindowId() const
{
	return windowId;
}

float OpenGL::DeltaTime() const
{
	return deltaTime;
}

int OpenGL::Width() const
{
	return glutGet(GLUT_WINDOW_WIDTH);
}

int OpenGL::Height() const
{
	return glutGet(GLUT_WINDOW_HEIGHT);
}
