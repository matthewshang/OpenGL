#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>

class Shader
{
public:
	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader();

	void use();
	GLuint getProgram();

private:
	GLuint m_program;

};

#endif