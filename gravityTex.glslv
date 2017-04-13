#version 420
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

//Stays constant for whole mesh
uniform mat4 MVP;			//Model View Projection matrix
out vec4 worldCoord;
out vec2 exchTexCoord;

void main()
{
	worldCoord = MVP * vec4(position, 1);
	gl_Position = worldCoord;
	exchTexCoord = texCoord;
}
