#include "ObjectsBase.h"
#include "GLMath.h"

#include <string.h>
#include <stdexcept>
#include <iostream>

Object3D::Object3D(int Verts, int Coords, int Mode) : verts(Verts), coords(Coords), mode(Mode)
{
	rotationMatrix = GLMath::Identity();
	scale = 1.0;
	Mass = 1;

	initialized = false;
	draw2D = false;
	programId = 0;
	vaoId = 0;
	vboId = 0;

	if(verts)
		vertices = new float3[verts];

	if(coords)
		texCoords = new float2[coords];

	modelMatrix = GLMath::Identity();
}

Object3D::~Object3D()
{
	if(verts)
		delete[] vertices;

	if(coords)
		delete[] texCoords;

	if(initialized)
	{
		// Shader Cleanup
		glUseProgram(0);
		glDetachShader(programId, vertexShaderId);
		glDetachShader(programId, fragmentShaderId);
		glDeleteShader(fragmentShaderId);
		glDeleteShader(vertexShaderId);
		glDeleteProgram(programId);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &vboId);
		if(coords)
			glDeleteBuffers(1, &texCoordBufferId);

		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vaoId);
	}
}

void Object3D::Draw(const mat4& projectionViewMatrix)
{
	if(!initialized)
	{
		throw std::runtime_error("Object not yet initialized, but Draw() was invoked");
	}

	glUseProgram(programId);
	glBindVertexArray(vaoId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	mat4 mvp = projectionViewMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(programId, "MVP"), 1, GL_FALSE, (float*)&mvp.p[0][0]);
	glDrawArrays(mode, 0, verts);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Object3D::SetPosition(const float3& newPos)
{
	position = newPos;
	UpdateModelMatrix();
}

void Object3D::Translate(const float3& vector)
{
	position += vector;
	UpdateModelMatrix();
}

void Object3D::SetScale(const float3& newScale)
{
	scale = newScale;
	UpdateModelMatrix();
}

void Object3D::Rotate(const Quaternion& Rotation)
{
	rotationMatrix = GLMath::Rotate(Rotation) * rotationMatrix;
	UpdateModelMatrix();
}

void Object3D::SetVelocity(const float3& velocity)
{
	this->velocity = velocity;
	UpdateModelMatrix();
}

void Object3D::Transform(const mat4& transform)
{
	modelMatrix = transform * modelMatrix;
}


bool Object3D::Drawing2D() const
{
	return draw2D;
}

void Object3D::Set2D(bool rndr2d)
{
	draw2D = rndr2d;
}


void Object3D::SetupVerticesAndShaders(const std::string& ImgName, const std::string& vertName, const std::string& fragName)
{
	// Shaders
	Shaders::SetShaders(&programId, &vertexShaderId, &fragmentShaderId, vertName, fragName);

	// VAO
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	// VBO (Creating objects)
	glGenBuffers(1, &vboId);														// One buffer per Object
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	float* tempVerts = new float[3 * verts];
	for(unsigned int i = 0; i < verts; i++)
	{
		memcpy(&tempVerts[3*i], vertices[i].n, sizeof(float) * 3);
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * verts, tempVerts, GL_STATIC_DRAW);
	delete[] tempVerts;
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	// Texture
	if(ImgName.length() && coords)
	{
		// Create texture VBO
		glGenBuffers(1, &texCoordBufferId);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBufferId);
		float* tempCoords = new float[2 * coords];
		for(unsigned int i = 0; i < coords; i++)
		{
			memcpy(&tempCoords[2*i], texCoords[i].n, sizeof(float) * 2);
		}
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * coords, tempCoords, GL_STATIC_DRAW);
		delete[] tempCoords;
		glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int imgWidth, imgHeight;
		unsigned char* image = SOIL_load_image(ImgName.c_str(), &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindVertexArray(0);
	initialized = true;
}

void Object3D::UpdateModelMatrix()
{
	modelMatrix = GLMath::Translate(position) * rotationMatrix * GLMath::Scale(scale);
}
