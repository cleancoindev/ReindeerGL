#include "SpringMesh.h"

#include "Objects.h"
#include "ObjectContainer.h"

SpringMesh::SpringMesh(const std::string& label, unsigned int X, unsigned int Y, const std::string& texfilePath) :
	MeshObj(label, X, Y, texfilePath, "positionColour.glslv", "positionColour.glslf", false)
//	MeshObj(label, X, Y, texfilePath, "texture.glslv", "texture.glslf", true)
{
	velocities.reset(new float3[X*Y]);
	positions = MeshObj::CreateGridMesh(X, Y);

	// Testing
	positions[(X/2)*Y + Y/2] += float3(0, 0, 10);

	this->SetTickTock(SpringMeshCallback);
}

void SpringMesh::SpringMeshCallback(std::shared_ptr<Object3D> obj, float deltaTime)
{
	std::shared_ptr<SpringMesh> mesh = std::dynamic_pointer_cast<SpringMesh>(obj);
	unsigned int x = mesh->x;
	unsigned int y = mesh->y;
	for(unsigned int i = 1; i < x-1; i++)
	{
		for(unsigned int j = 1; j < y-1; j++)
		{
			float3 totalForce = float3(0, 0, 0);
			float3 pos = mesh->positions[i*y + j],
				up = mesh->positions[i*y + j + 1],
				upLeft = mesh->positions[(i-1)*y + j + 1],
				upRight = mesh->positions[(i+1)*y + j + 1],
				down = mesh->positions[i*y + j - 1],
				downLeft = mesh->positions[(i-1)*y + j - 1],
				downRight = mesh->positions[(i+1)*y + j - 1],
				left = mesh->positions[(i-1)*y + j],
				right = mesh->positions[(i+1)*y + j];

			totalForce += up - pos;
			totalForce += upLeft - pos;
			totalForce += upRight - pos;
			totalForce += down - pos;
			totalForce += downLeft - pos;
			totalForce += downRight - pos;
			totalForce += left - pos;
			totalForce += right - pos;
			totalForce *= springConst;

			// Test gravity term
			totalForce += gravityForce;

			// Update vectors
			mesh->velocities[i*y + j] += totalForce * deltaTime;
			mesh->positions[i*y + j] += mesh->velocities[i*y + j] * deltaTime;

			// Adjust velocity post-positioning to account for friction along the way
			mesh->velocities[i*y + j] -= mesh->velocities[i*y + j] * frictionConst * deltaTime;
		}
	}

	mesh->SetVertsFromGrid(mesh->positions);
}

void SpringMesh::Draw(const mat4& projectionViewMatrix)
{
	glDisable(GL_CULL_FACE);
	MeshObj::Draw(projectionViewMatrix);
	glEnable(GL_CULL_FACE);
}
