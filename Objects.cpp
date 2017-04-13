#include "Objects.h"

float3 C_Vertices[24] = {
	// Front face
	{float3(-1, -1,  1)}, // 2
	{float3(-1,  1,  1)}, // 1
	{float3( 1, -1,  1)}, // 3
	{float3( 1,  1,  1)}, // 0

	// Right face
	{float3( 1,  1,  1)}, // 0
	{float3( 1, -1,  1)}, // 3
	{float3( 1,  1, -1)}, // 7
	{float3( 1, -1, -1)}, // 4

	// Bottom face
	{float3( 1, -1, -1)}, // 4
	{float3( 1, -1,  1)}, // 3
	{float3(-1, -1, -1)}, // 5
	{float3(-1, -1,  1)}, // 2

	// Left face
	{float3(-1, -1,  1)}, // 2
	{float3(-1, -1, -1)}, // 5
	{float3(-1,  1,  1)}, // 1
	{float3(-1,  1, -1)}, // 6

	// Top face
	{float3(-1,  1,  1)}, // 1
	{float3(-1,  1, -1)}, // 6
	{float3( 1,  1,  1)}, // 0
	{float3( 1,  1, -1)}, // 7

	// Back face
	{float3( 1,  1, -1)}, // 7
	{float3( 1, -1, -1)}, // 4
	{float3(-1,  1, -1)}, // 6
	{float3(-1, -1, -1)}, // 5
};
float2 C_TexCoords[24] = {
	// Front face
	{float2(0, 0)}, // bottom left
	{float2(0, 1)}, // top left
	{float2(1, 0)}, // bottom right
	{float2(1, 1)}, // top right

	// Right face
	{float2(0, 1)}, // top left
	{float2(0, 0)}, // bottom left
	{float2(1, 1)}, // top right
	{float2(1, 0)}, // bottom right

	// Bottom face
	{float2(1, 0)}, // bottom right
	{float2(1, 1)}, // top right
	{float2(0, 0)}, // bottom left
	{float2(0, 1)}, // top left

	// Left face
	{float2(1, 0)}, // bottom right
	{float2(0, 0)}, // bottom left
	{float2(0, 1)}, // top left
	{float2(1, 1)}, // top right

	// Top face
	{float2(0, 0)}, // bottom left
	{float2(0, 1)}, // top left
	{float2(1, 0)}, // bottom right
	{float2(1, 1)}, // top right

	// Back face
	{float2(0, 1)}, // top left
	{float2(0, 0)}, // bottom left
	{float2(1, 1)}, // top right
	{float2(1, 0)}, // bottom right
};

CubeObj::CubeObj(const std::string& texfilePath) : Object3D(24, 24, GL_TRIANGLE_STRIP)
{
	for(int i = 0; i < 24; i++)
	{
		vertices[i] = C_Vertices[i];
		texCoords[i] = C_TexCoords[i];
	}

	SetupVerticesAndShaders(texfilePath, "planeMap.glslv", "textureFrag.glslf");
}


float3 L_Vertices[2] = {
	{float3(0, 0, 0)}, // 0
	{float3(0, 0, 1)}, // 1
};
float2 L_TexCoords[2] = {
	{float2(0, 0)}, // 0
	{float2(1, 1)}, // 1
};

LineObj::LineObj(const std::string& texfilePath) : Object3D(2, 2, GL_LINES)
{
	vertices[0] = L_Vertices[0];
	vertices[1] = L_Vertices[1];
	texCoords[0] = L_TexCoords[0];
	texCoords[1] = L_TexCoords[1];

	SetupVerticesAndShaders(texfilePath, "planeMap.glslv", "textureFrag.glslf");
}


float3 P_Vertices[4] = {
	{float3(-1, -1, 0)}, // bottom left
	{float3(-1,  1, 0)}, // top left
	{float3( 1, -1, 0)}, // bottom right
	{float3( 1,  1, 0)}, // top right
};
float2 P_TexCoords[4] = {
	{float2(0, 0)}, // bottom left
	{float2(0, 1)}, // top left
	{float2(1, 0)}, // bottom right
	{float2(1, 1)}, // top right
};

PlaneObj::PlaneObj(const std::string& texfilePath) : Object3D(4, 4, GL_TRIANGLE_STRIP)
{
	for(int i = 0; i < 4; i++)
	{
		vertices[i] = P_Vertices[i];
		texCoords[i] = P_TexCoords[i];
	}

	SetupVerticesAndShaders(texfilePath, "planeMap.glslv", "textureFrag.glslf");
}

GravityPlane::GravityPlane() : Object3D(4, 4, GL_TRIANGLE_STRIP)
{
	for(int i = 0; i < 4; i++)
	{
		vertices[i] = P_Vertices[i];
		texCoords[i] = P_TexCoords[i];
	}

	SetupVerticesAndShaders("./Images/myPalette.png", "gravityTex.glslv", "gravityTex.glslf");
}

GLuint GravityPlane::GetP() const
{
	return programId;
}

float3 T_Vertices[3] = {
        float3(-1, -1, 0),
        float3(0, 1, 0),
        float3(1, -1, 0),
};
Triangle::Triangle() : Object3D(3, 0, GL_TRIANGLES)
{
	for(int i = 0; i < 3; i++)
	{
        	vertices[i] = T_Vertices[i];
                //texCoords[i] = P_TexCoords[i];
	}
	SetupVerticesAndShaders("");
}


// SphereObj::SphereObj(unsigned int n, float radius): Object3D()
// {
// 	mode = 4;

// 	if(n == 0)
// 		n = 1;

// 	verts = 4 * n;
// 	for(int k = 1; k < n; k++)
// 		verts += 8 * (n-k);

// 	verts += 2;
// 	inds = ((verts * 2) - 4) * 3;

// 	vertices = new Vertex3fColour[verts];
// 	indices = new GLuint[inds];

// 	vertices[0].Pos = float3(0, 1, 0);
// 	Scale = float3(radius);

// 	unsigned int MI = 1;	//MasterIndex for vertices
// 	for(unsigned int iY = 1; iY < n + 1; iY++)		//Fills in top half
// 	{
// 		float ThetaY = (float(iY) / float(n)) * 0.5 * GLMath::PI;
// 		for(unsigned int iX = 0; iX < (iY * 4); iX++)
// 		{
// 			float ThetaX = (float)iX/float(iY * 4) * 2 * GLMath::PI;
// 			vertices[MI].Pos = float3(cosf(ThetaX) * sinf(ThetaY), cosf(ThetaY), sinf(ThetaX) * sinf(ThetaY));
// 			MI++;
// 		}
// 	}
// 	for(; MI < verts; MI++)		//Fills in bottom half
// 	{
// 		vertices[MI].Pos = vertices[(verts - 1) - MI].Pos;
// 		vertices[MI].Pos.y *= -1;
// 		vertices[MI].Pos.z *= -1;
// 	}

	//First row
// 	indices[0] = 0;
// 	indices[1] = 1;
// 	indices[2] = 2;

// 	indices[3] = 0;
// 	indices[4] = 2;
// 	indices[5] = 3;

// 	indices[6] = 0;
// 	indices[7] = 3;
// 	indices[8] = 4;

// 	indices[9] = 0;
// 	indices[10] = 1;
// 	indices[11] = 4;
// 	MI = 12;

// 	unsigned int Corns = 3;
// 	for(unsigned int iY = 1; iY < n; iY++)		//Fills in top half
// 	{
// 		for(unsigned int iX = 0; iX < (iY * 4); iX++)
// 		{
// 			unsigned int self = SphereFindPoint(iY-1) + iX;			//Find our fucking self....

// 			float ratio = float(iX) / float(iY * 4);
			//			0/4			  1/4			   2/4			   3/4
// 			if(ratio == 0 || ratio == 0.25 || ratio == 0.5 || ratio == 0.75)		//are we at a corner? (0-3 == 4 corners)
// 			{
// 				Corns++;

// 				unsigned int* points = new unsigned int[4];
// 				if(iX == 0)
// 					points[0] = SphereFindPoint(iY+1) - 1;					//final point in their row
// 				else
// 					points[0] = self + Corns - 1;

// 				points[1] = self + Corns;
// 				points[2] = self + Corns + 1;
// 				if(self == SphereFindPoint(iY) - 1)
// 					points[3] = SphereFindPoint(iY-1);
// 				else
// 					points[3] = self + 1;

// 				for(int i = 0; i < 3; i++)
// 				{
// 					indices[MI] = self;
// 					MI++;
// 					indices[MI] = points[i];
// 					MI++;
// 					indices[MI] = points[i+1];
// 					MI++;
// 				}
// 				delete[] points;
// 			}
// 			else
// 			{
// 				unsigned int* points = new unsigned int[3];
// 				points[0] = self + Corns;
// 				points[1] = self + Corns + 1;
// 				if(self == SphereFindPoint(iY) - 1)
// 					points[2] = SphereFindPoint(iY-1);
// 				else
// 					points[2] = self + 1;

// 				for(int i = 0; i < 2; i++)
// 				{
// 					indices[MI] = self;
// 					MI++;
// 					indices[MI] = points[i];
// 					MI++;
// 					indices[MI] = points[i+1];
// 					MI++;
// 				}
// 				delete[] points;
// 			}
// 		}
// 	}
// 	for(; MI < inds; MI++)		//Fills in bottom half
// 	{
// 		indices[MI] = indices[(inds - 1) - MI];
// 		indices[MI] = (verts-1) - indices[MI];
// 	}
// }

// unsigned int SphereObj::SphereFindPoint(unsigned int n)
// {
// 	unsigned int tn = 4 * (n - 1);		//no +4 here so...
// 	return ((tn + 8) * n / 2) + 1;		//+8 here
// }
