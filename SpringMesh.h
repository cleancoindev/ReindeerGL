#include "Objects.h"
#include <string>
#include <memory>

const float springConst = 1;
const float3 gravityForce = float3(0, 0, -0.2);
const float frictionConst = 0.04;

class SpringMesh : public MeshObj
{
public:
	SpringMesh(const std::string& label, unsigned int X, unsigned int Y, const std::string& textureFilePath);

	virtual void Draw(const mat4& projectionViewMatrix);

private:
	std::unique_ptr<float3[]> positions;
	std::unique_ptr<float3[]> velocities;

	static void SpringMeshCallback(std::shared_ptr<Object3D> objPtr, float deltaTime);
};
