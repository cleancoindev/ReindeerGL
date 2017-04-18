#include "ObjectContainer.h"
#include "ObjectsBase.h"
#include "GLMath.h"

#include <string.h>
#include <stdexcept>
#include <iostream>


Object3D::Object3D(const std::string& label, int Verts, int Coords, int Mode) :
	objectLabel(label), verts(Verts), coords(Coords), mode(Mode)
{
	rotationMatrix = GLMath::Identity();
	modelMatrix = GLMath::Identity();
	scale = 1.0;
	textureFilepath.clear();

	initialized = false;
	draw2D = false;
	programId = 0;
	vaoId = 0;
	vboId = 0;
	textureId = 0;
	texCoordBufferId = 0;

	if(verts)
		vertices = new float3[verts];

	if(coords)
		texCoords = new float2[coords];
}

std::shared_ptr<Object3D> Object3D::MakeCopyNamed(const std::string& label) const
{
	std::shared_ptr<Object3D> newObj(new Object3D(label, verts, coords, mode));
	for(int i = 0; i < verts; i++)
	{
        	newObj->vertices[i] = vertices[i];
	}
	for(int i = 0; i < coords; i++)
	{
        	newObj->texCoords[i] = texCoords[i];
	}

	// Draw properties
	newObj->SetPosition(position);
	newObj->rotationMatrix = rotationMatrix;
	newObj->velocity = velocity;
	newObj->scale = scale;
	newObj->draw2D = draw2D;
	newObj->modelMatrix = modelMatrix;

	newObj->SetupVerticesAndInitialize();
	newObj->SetShaders(vertShaderFile, fragShaderFile, textureFilepath);

	return newObj;
}

Object3D::~Object3D()
{
	if(verts)
		delete[] vertices;

	if(coords)
		delete[] texCoords;

	if(initialized)
	{
		ClearShaders();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &vboId);
		if(texCoordBufferId)
			glDeleteBuffers(1, &texCoordBufferId);

		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vaoId);
	}
}

const std::string & Object3D::GetLabel() const
{
	return objectLabel;
}

ObjectContainer& Object3D::GetContainer()
{
	return container;
}

void Object3D::Draw(const mat4& projectionViewMatrix)
{
	if(!initialized)
	{
		throw std::runtime_error("Object not yet initialized, but Draw() was invoked");
	}

	if(programId)
	{
		glUseProgram(programId);
	}

	glBindVertexArray(vaoId);
	if(textureId)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	mat4 mvp = projectionViewMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(programId, "MVP"), 1, GL_FALSE, (float*)&mvp.p[0][0]);
	glDrawArrays(mode, 0, verts);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	// Now draw all sub-contained objects
	for(ConstLabelObjectPair objectPair : container)
	{
		const std::shared_ptr<Object3D> object = objectPair.second;
		object->Draw(mvp);
	}
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


void Object3D::Texture(const std::string& ImgFilename)
{
	if(!initialized)
	{
		throw std::runtime_error("Object not yet initialized, but Texture() was invoked");
	}

	glBindVertexArray(vaoId);

	// Shaders
	ClearShaders();
	Shaders::SetShaders(&programId, &vertexShaderId, &fragmentShaderId, "texture.glslv", "texture.glslf");

	// Texture
	if(ImgFilename.length())
	{
		textureFilepath = ImgFilename;

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
		unsigned char* image = SOIL_load_image(ImgFilename.c_str(), &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindVertexArray(0);
}

void Object3D::ColourSolid(const float3& redGreenBlue)
{
	if(!initialized)
	{
		throw std::runtime_error("Object not yet initialized, but ColourSolid() was invoked");
	}

	glBindVertexArray(vaoId);

	textureFilepath.clear();

	// Shaders
	ClearShaders();
	vertShaderFile = "dummy.glslv";
	fragShaderFile = "colour.glslf";
	Shaders::SetShaders(&programId, &vertexShaderId, &fragmentShaderId, vertShaderFile, fragShaderFile);

	// Colour
	GLuint solidColourId = glGetUniformLocation(programId, "solidColour");
	glUniform4f(solidColourId, redGreenBlue.x(), redGreenBlue.y(), redGreenBlue.z(), 1);

	glBindVertexArray(0);
}

bool Object3D::Drawing2D() const
{
	return draw2D;
}

void Object3D::SetupVerticesAndInitialize()
{
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

	glBindVertexArray(0);
	initialized = true;
}

void Object3D::SetShaders(const std::string& vertName, const std::string& fragName, const std::string& ImgFilename)
{
	if(!initialized)
	{
		throw std::runtime_error("Object not yet initialized, but SetShaders() was invoked");
	}

	glBindVertexArray(vaoId);

	// Shaders
	ClearShaders();
	vertShaderFile = vertName;
	fragShaderFile = fragName;
	Shaders::SetShaders(&programId, &vertexShaderId, &fragmentShaderId, vertName, fragName);

	// Shader Image
	if(ImgFilename.length())
	{
		textureFilepath = ImgFilename;

		if(coords)
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
		}

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int imgWidth, imgHeight;
		unsigned char* image = SOIL_load_image(ImgFilename.c_str(), &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindVertexArray(0);
}

void Object3D::ClearShaders()
{
	// Shader Cleanup
	if(programId)
	{
		glUseProgram(0);
		glDetachShader(programId, vertexShaderId);
		glDetachShader(programId, fragmentShaderId);
		glDeleteShader(fragmentShaderId);
		glDeleteShader(vertexShaderId);
		glDeleteProgram(programId);
		programId = 0;
	}

	vertShaderFile.clear();
	fragShaderFile.clear();
}

void Object3D::UpdateModelMatrix()
{
	modelMatrix = GLMath::Translate(position) * rotationMatrix * GLMath::Scale(scale);
}
