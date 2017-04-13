#version 420
in vec4 exchPosition;
in vec2 exchTexCoord;
out vec4 FragColor;

uniform sampler2D textureMap;

void main(void)
{
   FragColor = texture(textureMap, exchTexCoord);
}
