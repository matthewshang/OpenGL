#pragma once

#include <string>
#include <map>

#include <GL/glew.h>

#include "math/vec3.h"
#include "math/mat4.h"

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
	const static std::string VERTEX_EXTENSION;
	const static std::string FRAGMENT_EXTENSION;
	const static std::string SHADER_PATH;

	GLuint m_program;
	std::map<std::string, GLint> m_uniforms;
};