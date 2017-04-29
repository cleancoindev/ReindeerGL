#version 420
in vec3 modelPosition;
out vec4 FragColor;

vec4 Colour()
{
	vec4 color = vec4(modelPosition, 1);
	return color;
}

void main ()
{
	FragColor = Colour();
}
