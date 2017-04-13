#include "OpenGL.h"
#include "Objects.h"

#include <iostream>

using namespace std;

OpenGL gl;
unsigned int tick = 0;
float maxIterations = 128;
const float camSpeedSlow = 1;
const float camSpeed = 4;
unsigned int KEYS = 0;
bool autoScroll = false;
bool shift = false;
const float3 homePos(0, 0, 4);
shared_ptr<Triangle> tri;
shared_ptr<CubeObj> cube;

inline void MoveCam()
{
	gl.Position += (GLMath::RotateY(-gl.Rotation.y()) * gl.Velocity).Norm() * (shift ? camSpeedSlow : camSpeed) * gl.DeltaTime();
}

void Display()
{
	MoveCam();
	//tri->SetPosition(float3(cosf(float(tick)/30.0f), 0, 0));
	//tri->SetScale(float3(cosf(float(tick)/50.0f)));
	//tri->Transform(GLMath::RotateY(0.2f));
	static Quaternion q(1, 1, 1, 1);
	q.w = 4;
	q.w *= gl.DeltaTime();
	cube->Rotate(q);

	gl.DrawAll();

	// if(tick / gl.FramesPerSecond() > 5)
	// {
	// 	cout << gl.FramesPerSecond() << endl;
	// 	cout << gl.Position.x() << ", " << gl.Position.y() << ", " << gl.Position.z() << endl;
	// 	tick = 0;
	// }
	tick++;
}

void Keyboard(unsigned char key, int x, int y)
{
	shift = glutGetModifiers() & GLUT_ACTIVE_SHIFT;
	switch (key)
	{
		case 'r': case 'R':
			gl.Wireframe();
			gl.ShowCursor(!gl.IsFilling());
			break;
		case 'h': case 'H':
			gl.Position = homePos;
			break;
		case 'f': case 'F':
			gl.Fullscreen();
			break;
		case 'w': case 'W':
			if((KEYS & 1) == 0)
			{
				gl.Velocity.z() -= 1;
				KEYS += 1;
			}
			break;
		case 'a': case 'A':
			if((KEYS & 2) == 0)
			{
				gl.Velocity.x() -= 1;
				KEYS += 2;
			}
			break;
		case 's': case 'S':
			if((KEYS & 4) == 0)
			{
				gl.Velocity.z() += 1;
				KEYS += 4;
			}
			break;
		case 'd': case 'D':
			if((KEYS & 8) == 0)
			{
				gl.Velocity.x() += 1;
				KEYS += 8;
			}
			break;
		case ' ':
			if((KEYS & 16) == 0)
			{
				gl.Velocity.y() += 1;
				KEYS += 16;
			}
			break;
		case 'c': case 'C':
			if((KEYS & 32) == 0)
			{
				gl.Velocity.y() -= 1;
				KEYS += 32;
			}
			break;
		case 27:
			glutDestroyWindow(gl.WindowId());
			exit(0);
			break;
	}
	glutPostRedisplay();
}

void KeyboardUp(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'w': case 'W':
			gl.Velocity.z() = 0;
			KEYS -= 1;
			break;
		case 'a': case 'A':
			gl.Velocity.x() = 0;
			KEYS -= 2;
			break;
		case 's': case 'S':
			gl.Velocity.z() = 0;
			KEYS -= 4;
			break;
		case 'd': case 'D':
			gl.Velocity.x() = 0;
			KEYS -= 8;
			break;
		case ' ':
			gl.Velocity.y() = 0;
			KEYS -= 16;
			break;
		case 'c': case 'C':
			gl.Velocity.y() = 0;
			KEYS -= 32;
			break;
		case 'p': case 'P':
			gl.SaveScreenshot("awesome.bmp");
			break;
	}
	glutPostRedisplay();
}

void Resize(int width, int height)
{
	gl.SetCurrentWindowSize(width, height);
}

void MouseMotion(int x, int y)
{
	if(x != gl.Width() / 2 || y != gl.Height() / 2)
		glutWarpPointer(gl.Width()/2, gl.Height()/2);

	//Rotation around y axis depends on moving x coords :P
	gl.Rotation.y() -= 0.015 * float(gl.Width() / 2 - x) * gl.DeltaTime();
	gl.Rotation.x() -= 0.015 * float(gl.Height() / 2 - y) * gl.DeltaTime();

	if(gl.Rotation.x() > 1.570796)
		gl.Rotation.x() = 1.570796;
	else if(gl.Rotation.x() < -1.570796)
		gl.Rotation.x() = -1.570796;
}

int main(int argc, char** argv)
{
	gl.GLInit(argc, argv, 1200, 680, "TestGL");
	gl.ShowCursor(false);

	gl.Position = homePos;
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutPassiveMotionFunc(MouseMotion);
	glutReshapeFunc(Resize);

    //tri = make_shared<Triangle>();
    //gl.AddPlane("./Images/Globe.png");
    //gl.AddLine("./Images/Yellow.png");
    std::shared_ptr<PlaneObj> grvty = make_shared<PlaneObj>("./Images/deep_sea.png");
    gl.AddObject(static_pointer_cast<Object3D>(grvty));
    grvty->Translate(float3(0, -1.01, 0));
    grvty->Rotate(Quaternion(1, 0, 0, GLMath::PI/2));
    grvty->SetScale(25.0f);
    cube = gl.AddCube("./Images/Globe.png");

    // pnl->SetPosition(float3(0, 0, 0));
    //shared_ptr<LineObj> line = make_shared<CubeObj>("./Images/Blue.png");
    // shared_ptr<LineObj> line = make_shared<LineObj>("./Images/Blue.png");
    // line->Rotate(Quaternion(0, 1, 0, 1.5));
    //cube->Rotate(Quaternion(1,1,1,0.2));
    //cube->SetPosition(float3(0, 0, 3));
    // gl.AddObject(static_pointer_cast<Object3D>(line));
    //gl.AddObject(static_pointer_cast<Object3D>(tri));

    gl.StartFPS();
    glutMainLoop();

    return 0;
}
