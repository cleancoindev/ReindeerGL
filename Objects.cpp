#include "ObjectContainer.h"
#include "Objects.h"

#include <array>
#include <vector>
#include <cmath>


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

CubeObj::CubeObj(const std::string& label, const std::string& texfilePath) : Object3D(label, 36, true, GL_TRIANGLES)
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

LineObj::LineObj(const std::string& label, const std::string& texfilePath) : Object3D(label, 2, true, GL_LINES)
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

PlaneObj::PlaneObj(const std::string& label, const std::string& texfilePath) : Object3D(label, 4, true, GL_TRIANGLE_STRIP)
{
	for(int i = 0; i < verts; i++)
	{
		vertices[i] = P_Vertices[i];
		texCoords[i] = P_TexCoords[i];
	}

	SetupVerticesAndInitialize();
	Texture(texfilePath);
}

// GravityPlane::GravityPlane() : Object3D(4, 4, GL_TRIANGLE_STRIP)
// {
// 	for(int i = 0; i < verts; i++)
// 	{
// 		vertices[i] = P_Vertices[i];
// 		texCoords[i] = P_TexCoords[i];
// 	}

// 	SetupVerticesAndInitialize();
// 	SetShaders("gravityTex.glslv", "gravityTex.glslf", "./Images/myPalette.png");
// }


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
Triangle::Triangle(const std::string& label, const std::string& texfilePath) : Object3D(label, 3, true, GL_TRIANGLES)
{
	for(int i = 0; i < verts; i++)
	{
        	vertices[i] = T_Vertices[i];
            texCoords[i] = T_TexCoords[i];
	}

	SetupVerticesAndInitialize();
	Texture(texfilePath);
}


MeshObj::MeshObj(const std::string& label, unsigned int X, unsigned int Y, const std::string& texfilePath, const std::string& vertShaderFile, const std::string& fragShaderFile) :
	x(X), y(Y), Object3D(label, 3*2*(X-1)*(Y-1), true, GL_TRIANGLES)
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


namespace
{
	struct NormalizedTriangle
	{
		float3 a, b, c;
	};

	void SplitTriangle(const NormalizedTriangle& normTri, std::array<NormalizedTriangle, 4>& resTris)
	{
		float3 halfAB = (normTri.a + normTri.b)/2; halfAB.Normalize();
		float3 halfBC = (normTri.b + normTri.c)/2; halfBC.Normalize();
		float3 halfCA = (normTri.c + normTri.a)/2; halfCA.Normalize();

		// Tri around a
		resTris[0].a = normTri.a;
		resTris[0].b = halfAB;
		resTris[0].c = halfCA;

		// .. b
		resTris[1].a = halfAB;
		resTris[1].b = normTri.b;
		resTris[1].c = halfBC;

		// .. c
		resTris[2].a = halfCA;
		resTris[2].b = halfBC;
		resTris[2].c = normTri.c;

		// Center Tri
		resTris[3].a = halfCA;
		resTris[3].b = halfAB;
		resTris[3].c = halfBC;
	}
}

// Number of vertices = 3 * 8 * 4^n = 3 * 2^3 * 2^(2n) = 3 * 2^(2n + 3)
SphereObj::SphereObj(const std::string& label, const unsigned int n, const std::string& texturePath) :
	Object3D(label, 3 * (1 << (2*n + 3)), true, GL_TRIANGLES)
{
	std::vector<NormalizedTriangle> tris;

	// Setup top triangles
	tris.push_back({float3(0, 0, 1), float3(1, 0, 0), float3(0, 1, 0)});
	tris.push_back({float3(1, 0, 0), float3(0, 0, -1), float3(0, 1, 0)});
	tris.push_back({float3(0, 0, -1), float3(-1, 0, 0), float3(0, 1, 0)});
	tris.push_back({float3(-1, 0, 0), float3(0, 0, 1), float3(0, 1, 0)});

	// .. bottom triangles
	tris.push_back({float3(1, 0, 0), float3(0, 0, 1), float3(0, -1, 0)});
	tris.push_back({float3(0, 0, -1), float3(1, 0, 0), float3(0, -1, 0)});
	tris.push_back({float3(-1, 0, 0), float3(0, 0, -1), float3(0, -1, 0)});
	tris.push_back({float3(0, 0, 1), float3(-1, 0, 0), float3(0, -1, 0)});

	std::vector<NormalizedTriangle> tempTris;
	std::array<NormalizedTriangle, 4> resTris;
	for(unsigned int i = 0; i < n; i++)
	{
		tempTris.clear();
		for(unsigned int curTriIndex = 0; curTriIndex < tris.size(); curTriIndex++)
		{
			SplitTriangle(tris[curTriIndex], resTris);
			tempTris.push_back(resTris[0]);
			tempTris.push_back(resTris[1]);
			tempTris.push_back(resTris[2]);
			tempTris.push_back(resTris[3]);
		}
		tris = std::move(tempTris);
	}

	for(unsigned int i = 0; i < tris.size(); i++)
	{
		vertices[3*i] = tris[i].a;
		vertices[3*i + 1] = tris[i].b;
		vertices[3*i + 2] = tris[i].c;

        texCoords[3*i] = PointToTexcoord(tris[i].a);
        texCoords[3*i + 1] = PointToTexcoord(tris[i].b);
        texCoords[3*i + 2] = PointToTexcoord(tris[i].c);

        // This fixes awkward unwinding at 99/100 * 2pi -> 0
        if(tris[i].a.z() < 0 || tris[i].b.z() < 0 || tris[i].c.z() < 0)
        {
        	texCoords[3*i].x() = 1 - texCoords[3*i].x();
        	texCoords[3*i + 1].x() = 1 - texCoords[3*i + 1].x();
        	texCoords[3*i + 2].x() = 1 - texCoords[3*i + 2].x();
        }
	}

	SetupVerticesAndInitialize();
	SetShaders("sphereTexture.glslv", "sphereTexture.glslf", texturePath);
}

float2 SphereObj::PointToTexcoord(const float3& normPoint)
{
	float xzProjectionLength = sqrt(normPoint.x() * normPoint.x() + normPoint.z() * normPoint.z());
	float uCoord = fabs(asin(normPoint.z() / xzProjectionLength));
	uCoord = normPoint.x() >= 0 ? (GLMath::PI - uCoord) : uCoord;
	uCoord /= (2*GLMath::PI);

	float vCoord = (asin(normPoint.y()) + GLMath::PI/2) / GLMath::PI;

	return std::move(float2(uCoord, vCoord));
}
