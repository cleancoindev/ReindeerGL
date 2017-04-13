#version 420
// uniform vec3 camPos;
// uniform sampler2D tex;
// uniform vec4 Planets[16];
// uniform float PlanetRadii[16];
// uniform float GravConstant;
// uniform float MaxGFS;

#define PI 3.1415926535897932384626433832795

in vec4 worldCoord;
out vec4 FragColor;

vec4 Colour()
{
	vec4 color = worldCoord * sin(length(worldCoord));
	return color;
}

void main ()
{
	FragColor = Colour();
}
