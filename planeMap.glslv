#version 420
layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexCoord;
out vec4 exchPosition;
out vec2 exchTexCoord;

uniform mat4 MVP;	// Model-View-Projection matrix

void main(void)
{
        gl_Position = MVP * vec4(inPosition, 1);
        exchPosition = gl_Position;
        exchTexCoord = vec2(inTexCoord.x, 1 - inTexCoord.y);
}
