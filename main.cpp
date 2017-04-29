#include "OpenGL.h"
// #include "Text2D.h"
#include "Objects.h"
#include "SpringMesh.h"

#include <iostream>

using namespace std;

OpenGL gl;
unsigned int tick = 0;
const float camSpeedSlow = 1;
const float camSpeed = 10;
unsigned int KEYS = 0;
bool autoScroll = false;
bool shift = false;
const float3 homePos(0, 1, 4);
shared_ptr<Triangle> tri;
shared_ptr<CubeObj> cube;
// shared_ptr<GravityPlane> grvty;
// shared_ptr<Text2D> myText;

inline void MoveCam()
{
	gl.Position += (GLMath::RotateY(-gl.Rotation.y()) * gl.Velocity).Norm() * (shift ? camSpeedSlow : camSpeed) * gl.DeltaTime();
}

void CallbackTest(std::shared_ptr<Object3D>& obj, float deltaTime)
{
	float3 pos(obj->Position());
	obj->SetVelocity(obj->Velocity() + float3(-10 * pos.x() * deltaTime, 0, 0));
	obj->Translate(obj->Velocity() * deltaTime);
}

void Display()
{
	MoveCam();

	gl.DrawAll();

	if(gl.FramesPerSecond() && tick / gl.FramesPerSecond() > 5)		// Print every 5 seconds
	{
		cout << gl.FramesPerSecond() << endl;
		//cout << gl.Position.x() << ", " << gl.Position.y() << ", " << gl.Position.z() << endl;
		tick = 0;
	}

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
	gl.Rotation.y() -= 0.001 * float(gl.Width() / 2 - x);
	gl.Rotation.x() -= 0.00075 * float(gl.Height() / 2 - y);

	if(gl.Rotation.x() > 1.570796)
		gl.Rotation.x() = 1.570796;
	else if(gl.Rotation.x() < -1.570796)
		gl.Rotation.x() = -1.570796;
}

int main(int argc, char** argv)
{
	gl.GLInit(argc, argv, 1200, 680, "TestGL");
	glutWarpPointer(gl.Width()/2, gl.Height()/2);
	gl.ShowCursor(false);

	gl.Position = homePos;
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutPassiveMotionFunc(MouseMotion);
	glutReshapeFunc(Resize);
	gl.Fullscreen();

    // tri = make_shared<Triangle>("Scaling triangle", "./Images/myPalette.png");
    // tri->SetTickTock(CallbackTest);
    // tri->SetPosition(float3(-1, 0, 0));
    // gl.AddAnObjectPtr<Triangle>(tri);

    // std::shared_ptr<PlaneObj> pln = make_shared<PlaneObj>("ground", "./Images/deep_sea.png");
    // gl.AddAnObjectPtr<PlaneObj>(pln);
    // pln->Translate(float3(0, -1.01, 0));
    // pln->Rotate(Quaternion(1, 0, 0, GLMath::PI/2));
    // pln->SetScale(25.0f);

	// cube = gl.AddNewObject<CubeObj>("spinning cube", "./Images/Globe.png");
	// cube->SetPosition(float3(-10, 2, -5));
	// cube->SetTickTock([](std::shared_ptr<Object3D>& obj, float deltaTime) {
	// 	Quaternion q(1, 1, 1, 0);
	// 	q.Normalize3();
	// 	q.w = (2*GLMath::PI) / 60 * gl.DeltaTime();
	// 	obj->Rotate(q);
	// });

    // std::shared_ptr<Triangle> tri2 = make_shared<Triangle>("Sub-contained triangle", "");
    // tri2->ColourSolid(float3(1, 1, 0));
    // tri2->Translate(float3(0, 1.5, 0));
    // tri2->SetScale(float3(0.5f));
    // cube->GetContainer().AddObjectPtr(tri2);
    // std::shared_ptr<Object3D> tri3 = tri2->MakeCopyNamed("Triangle copy demo");
    // tri3->ColourSolid(float3(0, 1, 0));
    // gl.AddAnObjectPtr(tri3);
    // tri->GetContainer().AddObjectPtr(tri3);

    // std::shared_ptr<MeshObj> mesh = make_shared<MeshObj>("mesh graphing", 100, 100, "./Images/myPalette.png", "meshExample.glslv", "texture.glslf");
    // mesh->SetPosition(float3(10, 1, -5));
    // mesh->SetScale(float3(10, 10, 1));
    // mesh->Rotate(Quaternion(1, 0, 0, -GLMath::PI/2));
    // mesh->SetXAxisRange(-2 * GLMath::PI, 2 * GLMath::PI);
    // mesh->SetYAxisRange(-2* GLMath::PI, 2 * GLMath::PI);
    // gl.AddAnObjectPtr<MeshObj>(mesh);

    std::shared_ptr<SpringMesh> mesh = make_shared<SpringMesh>("spring bed", 53, 53, "./Images/Globe.png");
    mesh->SetPosition(float3(-5, 0, 2));
    mesh->SetScale(float3(10, 10, 1));
    mesh->Rotate(Quaternion(1, 0, 0, -GLMath::PI/2));
    gl.AddAnObjectPtr<SpringMesh>(mesh);

	// std::shared_ptr<SphereObj> sphere = make_shared<SphereObj>("sphereTests", 5, "./Images/Globe.png");
	// sphere->SetPosition(float3(0, 1, -10));
	// sphere->SetScale(float3(2));
	// gl.AddAnObjectPtr<SphereObj>(sphere);

    // myText = make_shared<Text2D>("text", "Hello world", 0.1, 0.1);
    // gl.AddObject(OBJECT3D_PTR(myText));/

	gl.StartFPS();
    glutMainLoop();

    return 0;
}
