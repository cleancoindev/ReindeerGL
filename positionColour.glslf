#version 420
in vec3 modelPosition;
out vec4 FragColor;

vec4 Colour()
{
	vec4 color;

	//*// Toggle normal or position colour
	vec3 testX = normalize(dFdx(modelPosition));
	vec3 testY = normalize(dFdy(modelPosition));
	color = vec4(normalize(cross(testX, testY)), 1);
	color.xyz = vec3(abs(color.x), abs(color.y), abs(color.z));/*/
	color = vec4(modelPosition, 1);//*/

	return color;
}

void main ()
{
	FragColor = Colour();
}
