#version 420
layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexCoord;
out vec2 exchTexCoord;

uniform mat4 MVP;	// Model-View-Projection matrix
uniform vec2 xRange;
uniform vec2 yRange;

#define PI 3.1415926535897932384626433832795

float f(vec2 v)
{
	float r = 1;
	r = cos(sqrt(dot(v, v)));
	// r = cos(v.x)
	return r;
}

void main(void)
{
		// Scale to input range
		vec2 v = vec2((1 - inPosition.x) * xRange.x + inPosition.x * xRange.y,
			(1 - inPosition.y) * yRange.x + inPosition.y * yRange.y);

		// Use original position though
		vec3 pos = inPosition;

		pos.z = f(v);
        gl_Position = MVP * vec4(pos, 1);

        // SOIL inverts images on load, this fixes...
        exchTexCoord = vec2(-(pos.z + 1) / 2, 1 - inTexCoord.y);
}
