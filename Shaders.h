#pragma once
#include <GL/glew.h>
#include <string>

namespace Shaders
{
	void SetShaders(GLuint* p, GLuint* v, GLuint* f, const std::string& vertShaderFile, const std::string& FragShaderFile);
}
