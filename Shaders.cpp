#include "Shaders.h"
#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

namespace
{
	char* Read(const char* FileName)
	{
		std::ifstream File(FileName, std::ifstream::binary);
		if(File.good())
		{
			File.seekg(0, File.end);
			int size = File.tellg();
			File.seekg(0, File.beg);

			char* buffer = new char [size+1];
			memset(buffer, 0, size + 1);
			File.read(buffer, size);
			File.close();

			return buffer;
		}
		std::cout << "Could not open file " << FileName << "\n";
		exit(0);
	}
}

void Shaders::SetShaders(GLuint* p, GLuint* v, GLuint* f, const std::string& vertShaderFile, const std::string& fragShaderFile)
{
	GLenum error = glGetError();
	char* vs, *fs;
	GLint success = 0;
	GLchar ErrorLog[1024] = {0};

	*v = glCreateShader(GL_VERTEX_SHADER);
	*f = glCreateShader(GL_FRAGMENT_SHADER);

	vs = Read(vertShaderFile.c_str());
	fs = Read(fragShaderFile.c_str());

	const char* vv = vs;
	const char* ff = fs;

	glShaderSource(*v, 1, &vv, NULL);
	glShaderSource(*f, 1, &ff, NULL);

	delete[] vs;
	delete[] fs;

	glCompileShader(*v);
	glGetShaderiv(*v, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(*v, 1024, NULL, ErrorLog);
        std::cout << "Error compiling vertex shader (" << vertShaderFile << "): " << ErrorLog << "\n";
        exit(1);
    }
	glCompileShader(*f);
	glGetShaderiv(*f, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(*f, 1024, NULL, ErrorLog);
        std::cout << "Error compiling fragment shader (" << fragShaderFile << "): " << ErrorLog << "\n";
        exit(1);
    }

	*p = glCreateProgram();

	glAttachShader(*p, *v);
	glAttachShader(*p, *f);

	glLinkProgram(*p);
	glGetProgramiv(*p, GL_LINK_STATUS, &success);
	if (success == 0)
	{
		glGetProgramInfoLog(*p, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << "Error linking shader program: " << ErrorLog << "\n";
        exit(1);
	}
	glValidateProgram(*p);
    glGetProgramiv(*p, GL_VALIDATE_STATUS, &success);
    if (!success)
	{
		glGetProgramInfoLog(*p, sizeof(ErrorLog), NULL, ErrorLog);
        std::cout << "Invalid shader program: " << ErrorLog << "\n";
        exit(1);
    }

	glUseProgram(*p);
	error = glGetError();
	if(error != GL_NO_ERROR)
	{
		std::cerr << "ERROR: Could not create the shaders: " << gluErrorString(error) << "\n";
		exit(-1);
	}
}
