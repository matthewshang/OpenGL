#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

#include <GL/glew.h>

#include "math/Vec3.h"
#include "math/Mat4.h"

class Shader
{
public:
	Shader(const std::string& name);
	~Shader();

	void bind();
	GLuint getProgram();

	void addUniform(const std::string& uniform);
	void setInt(const std::string& uniform, int value);
	void setFloat(const std::string& uniform, float value);
	void setVec3(const std::string& uniform, const Vec3& value);
	void setMat4(const std::string& uniform, const Mat4& value);

private:
	const std::string VERTEX_EXTENSION = ".vert";
	const std::string FRAGMENT_EXTENSION = ".frag";
	const std::string SHADER_PATH = "res/shaders/";

	GLuint m_program;
	std::map<std::string, GLint> m_uniforms;
};

#endif