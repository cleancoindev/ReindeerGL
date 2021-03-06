#include "OpenGL.h"
#include "Shaders.h"

#include <iostream>
#include <fstream>
#include <SOIL/SOIL.h>
#include <string.h>

#include <chrono>
typedef std::chrono::high_resolution_clock NanoClock;


OpenGL::OpenGL(int argc, char** argv, int width, int height, const std::string& title)
{
	GLInit(argc, argv, width, height, title);
}

void OpenGL::GLInit(int argc, char** argv, int widthIn, int heightIn, const std::string& title)
{
	filling = true;
	fullscreen = false;

	// Ensure no progress until we get an accurate measure
	framesPerSecond = 0.0f;
	deltaTime = 0.0f;

	width = widthIn;
	height = heightIn;

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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

	// Objects should be created expecting CCW culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glViewport(0, 0, width, height);
}

void OpenGL::DrawAll()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH);
	glEnable(GL_BLEND);
	CalcFPS();

	mat4 projectionViewMatrix = GLMath::Perspective(fieldOfView, float(width) / float(height), 0.05f, 1000.0f) * GLMath::Rotate(-Rotation) * GLMath::Translate(-Position);
	mat4 twoDimensionalMatrix = GLMath::Scale(float3(float(height) / float(width), 1, 1));

	// Experimental camera rotations
	// Quaternion q1(1, 0, 0, Rotation.x());
	// q1.Normalize3();
	// Quaternion q2(0, 1, 0, Rotation.y());
	// q2.Normalize3();
	// mat4 projectionViewMatrix = GLMath::Perspective(fieldOfView, float(width) / float(height), 0.05f, 1000.0f) * GLMath::Rotate(q1*q2) * GLMath::Translate(-Position);

	for(LabelObjectPair objectPair : topLevelContainer)
	{
		std::shared_ptr<Object3D> object = objectPair.second;

		if(object->GetTickTock() != nullptr)
		{
			object->GetTickTock()(object, deltaTime);
		}
		object->Draw(object->Drawing2D() ? twoDimensionalMatrix : projectionViewMatrix);
	}

	glutSwapBuffers();
    glutPostRedisplay();
}

void OpenGL::CalcFPS()
{
	frameCount++;
	std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> delta = currentTime - previousTime;
	if(delta.count() > 0.2f &&  frameCount > 1)
	{
		framesPerSecond = frameCount / delta.count();
		deltaTime = 1.0f / framesPerSecond;
		StartFPS();
	}
}

void OpenGL::StartFPS()
{
	frameCount = 0;
	previousTime = std::chrono::high_resolution_clock::now();
}

void OpenGL::Fullscreen()
{
	fullscreen ? glutReshapeWindow(800, 600) : glutFullScreen();
	fullscreen = !fullscreen;
}
bool OpenGL::IsFullscreen() const
{
	return fullscreen;
}

void OpenGL::Wireframe()
{
	filling = !filling;
	filling ? glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
bool OpenGL::IsFilling() const
{
	return filling;
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
		std::cerr << "SaveScreenshot(" << filename << ") failed\n";
	}
	else
	{
		std::cerr << "SaveScreenshot(" << filename << ") succeeded\n";
	}
	delete[] img;
	delete[] swapSpace;
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

void OpenGL::SetCurrentWindowSize(const unsigned int width, const unsigned int height)
{
	this->width = width;
	this->height = height;

	glViewport(0, 0, width, height);
	glutPostRedisplay();
}

void OpenGL::ShowCursor(bool show) const
{
	if(show)
	{
		glutSetCursor(GLUT_CURSOR_INHERIT);
	} else {
		glutSetCursor(GLUT_CURSOR_NONE);
	}
}
