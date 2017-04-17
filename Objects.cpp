#include "Objects.h"

float3 C_Vertices[36] = {
	// Front face
	{float3(-1, -1,  1)}, // 2
	{float3( 1, -1,  1)}, // 3
	{float3(-1,  1,  1)}, // 1

	{float3( 1, -1,  1)}, // 3
	{float3( 1,  1,  1)}, // 0
	{float3(-1,  1,  1)}, // 1


	// Right face
	{float3( 1,  1,  1)}, // 0
	{float3( 1, -1,  1)}, // 3
	{float3( 1,  1, -1)}, // 7

	{float3( 1,  1, -1)}, // 7
	{float3( 1, -1,  1)}, // 3
	{float3( 1, -1, -1)}, // 4


	// Bottom face
	{float3( 1, -1, -1)}, // 4
	{float3( 1, -1,  1)}, // 3
	{float3(-1, -1, -1)}, // 5

	{float3(-1, -1, -1)}, // 5
	{float3( 1, -1,  1)}, // 3
	{float3(-1, -1,  1)}, // 2


	// Left face
	{float3(-1, -1,  1)}, // 2
	{float3(-1,  1,  1)}, // 1
	{float3(-1, -1, -1)}, // 5

	{float3(-1,  1,  1)}, // 1
	{float3(-1,  1, -1)}, // 6
	{float3(-1, -1, -1)}, // 5


	// Top face
	{float3(-1,  1,  1)}, // 1
	{float3( 1,  1,  1)}, // 0
	{float3(-1,  1, -1)}, // 6

	{float3( 1,  1,  1)}, // 0
	{float3( 1,  1, -1)}, // 7
	{float3(-1,  1, -1)}, // 6


	// Back face
	{float3( 1,  1, -1)}, // 7
	{float3( 1, -1, -1)}, // 4
	{float3(-1,  1, -1)}, // 6

	{float3(-1,  1, -1)}, // 6
	{float3( 1, -1, -1)}, // 4
	{float3(-1, -1, -1)}, // 5
};
float2 C_TexCoords[36] = {
	// Front face
	{float2(0, 0)}, // bottom left
	{float2(1, 0)}, // bottom right
	{float2(0, 1)}, // top left

	{float2(1, 0)}, // bottom right
	{float2(1, 1)}, // top right
	{float2(0, 1)}, // top left


	// Right face
	{float2(0, 1)}, // top left
	{float2(0, 0)}, // bottom left
	{float2(1, 1)}, // top right

	{float2(1, 1)}, // top right
	{float2(0, 0)}, // bottom left
	{float2(1, 0)}, // bottom right


	// Bottom face
	{float2(1, 0)}, // bottom right
	{float2(1, 1)}, // top right
	{float2(0, 0)}, // bottom left

	{float2(0, 0)}, // bottom left
	{float2(1, 1)}, // top right
	{float2(0, 1)}, // top left


	// Left face
	{float2(1, 0)}, // bottom right
	{float2(1, 1)}, // top right
	{float2(0, 0)}, // bottom left

	{float2(1, 1)}, // top right
	{float2(0, 1)}, // top left
	{float2(0, 0)}, // bottom left


	// Top face
	{float2(0, 0)}, // bottom left
	{float2(1, 0)}, // bottom right
	{float2(0, 1)}, // top left

	{float2(1, 0)}, // bottom right
	{float2(1, 1)}, // top right
	{float2(0, 1)}, // top left


	// Back face
	{float2(0, 1)}, // top left
	{float2(0, 0)}, // bottom left
	{float2(1, 1)}, // top right

	{float2(1, 1)}, // top right
	{float2(0, 0)}, // bottom left
	{float2(1, 0)}, // bottom rightSet2D
};

CubeObj::CubeObj(const std::string& texfilePath) : Object3D(36, 36, GL_TRIANGLES)
{
	for(unsigned int i = 0; i < verts; i++)
	{
		vertices[i] = C_Vertices[i];
		texCoords[i] = C_TexCoords[i];
	}

	SetupVerticesAndInitialize();
	Texture(texfilePath);
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

	SetupVerticesAndInitialize();
	Texture(texfilePath);
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
	for(int i = 0; i < verts; i++)
	{
		vertices[i] = P_Vertices[i];
		texCoords[i] = P_TexCoords[i];
	}

	SetupVerticesAndInitialize();
	Texture(texfilePath);
}

GravityPlane::GravityPlane() : Object3D(4, 4, GL_TRIANGLE_STRIP)
{
	for(int i = 0; i < verts; i++)
	{
		vertices[i] = P_Vertices[i];
		texCoords[i] = P_TexCoords[i];
	}

	SetupVerticesAndInitialize();
	SetShaders("gravityTex.glslv", "gravityTex.glslf", "./Images/myPalette.png");
}


float3 T_Vertices[3] = {
    float3(1, -1, 0),
    float3(0, 1, 0),
    float3(-1, -1, 0),
};
float2 T_TexCoords[3] = {
    float2(1, 0),
    float2(0.5, 1),
	float2(0, 0),
};
Triangle::Triangle(const std::string& texfilePath) : Object3D(3, 3, GL_TRIANGLES)
{
	for(int i = 0; i < verts; i++)
	{
        	vertices[i] = T_Vertices[i];
            texCoords[i] = T_TexCoords[i];
	}

	SetupVerticesAndInitialize();
	Texture(texfilePath);
}


MeshObj::MeshObj(unsigned int X, unsigned int Y, const std::string& texfilePath, const std::string& vertShaderFile, const std::string& fragShaderFile) :
	x(X), y(Y), Object3D(3*2*(X-1)*(Y-1), 3*2*(X-1)*(Y-1), GL_TRIANGLES)
{
	if(y && x)
	{
		unsigned int vertCount = 0;
		for(int i = 0; i < x-1; i++)
		{
			for(unsigned int j = 0; j < y-1; j++)
			{
				// Triangle One
				vertices[vertCount] = float3(float(i)/float(x-1), float(j)/float(y-1), 0);
		        texCoords[vertCount++] = float2(float(i)/float(x-1), float(j)/float(y-1));

		        vertices[vertCount] = float3(float(i+1)/float(x-1), float(j)/float(y-1), 0);
		        texCoords[vertCount++] = float2(float(i+1)/float(x-1), float(j)/float(y-1));

		        vertices[vertCount] = float3(float(i)/float(x-1), float(j+1)/float(y-1), 0);
		        texCoords[vertCount++] = float2(float(i)/float(x-1), float(j+1)/float(y-1));


		        // Triangle Two
				vertices[vertCount] = float3(float(i+1)/float(x-1), float(j)/float(y-1), 0);
		        texCoords[vertCount++] = float2(float(i+1)/float(x-1), float(j)/float(y-1));

		        vertices[vertCount] = float3(float(i+1)/float(x-1), float(j+1)/float(y-1), 0);
		        texCoords[vertCount++] = float2(float(i+1)/float(x-1), float(j+1)/float(y-1));

		        vertices[vertCount] = float3(float(i)/float(x-1), float(j+1)/float(y-1), 0);
		        texCoords[vertCount++] = float2(float(i)/float(x-1), float(j+1)/float(y-1));
			}
		}
	}

	SetupVerticesAndInitialize();
	SetShaders(vertShaderFile, fragShaderFile, texfilePath);
	SetXAxisRange(-1, 1);
	SetYAxisRange(-1, 1);
}

void MeshObj::SetXAxisRange(float low, float high)
{
	if(high < low)
	{
		high = low;
	}

	xRange = float2(low, high);
	GLuint xId = glGetUniformLocation(programId, "xRange");
	glUniform2f(xId, low, high);
}

void MeshObj::SetYAxisRange(float low, float high)
{
	if(high < low)
	{
		high = low;
	}

	yRange = float2(low, high);
	GLuint yId = glGetUniformLocation(programId, "yRange");
	glUniform2f(yId, low, high);
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
