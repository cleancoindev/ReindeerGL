#version 420
layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexCoord;
out vec2 exchTexCoord;

uniform mat4 MVP;	// Model-View-Projection matrix

#define PI 3.1415926535897932384626433832795

void main(void)
{
		vec3 newVert = inPosition;
		newVert.z = 0;
		newVert.z = sin(PI*newVert.x);
        gl_Position = MVP * vec4(newVert, 1);

        // SOIL inverts images on load, this fixes...
        exchTexCoord = vec2(inTexCoord.x, 1 - inTexCoord.y);
}
