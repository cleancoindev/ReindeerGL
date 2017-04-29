#version 420
layout(location = 0) in vec3 inPosition;

//Stays constant for whole mesh
uniform mat4 MVP;			//Model View Projection matrix
out vec3 modelPosition;

void main()
{
	gl_Position = MVP * vec4(inPosition, 1);
	modelPosition = inPosition;
}
