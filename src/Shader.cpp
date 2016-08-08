#include "Shader.h"

void loadShader(const std::string& path, std::string& ret);

Shader::Shader(const std::string& name)
{
	std::string vertexSource;
	std::string fragmentSource;
	loadShader(SHADER_PATH + name + VERTEX_EXTENSION, vertexSource);
	loadShader(SHADER_PATH + name + FRAGMENT_EXTENSION, fragmentSource);
	const GLchar* vertexSourceGL = vertexSource.c_str();
	const GLchar* fragmentSourceGL = fragmentSource.c_str();

	GLuint vertexShader;
	GLint success;
	GLchar log[512];

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSourceGL, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		std::cout << "Error::Shader - vertexShader compilation failed\n" << log << std::endl;
	}

	GLuint fragmentShader;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSourceGL, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		std::cout << "Error::Shader - fragmentShader compilation failed\n" << log << std::endl;
	}

	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_program, 512, NULL, log);
		std::cout << "Error::Shader - program linking failed\n" << log << std::endl;
	}

	glDetachShader(m_program, vertexShader);
	glDetachShader(m_program, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

void Shader::bind()
{
	glUseProgram(m_program);
}

GLuint Shader::getProgram()
{
	return m_program;
}

void Shader::addUniform(const std::string& uniform)
{
	GLint location = glGetUniformLocation(m_program, uniform.c_str());
	if (location == -1)
	{
		std::cout << "Error: invalid uniform name: " << uniform << std::endl;
	}
	else
	{
		m_uniforms.insert(std::pair<std::string, GLint>(uniform, location));
	}
}

void Shader::setInt(const std::string& uniform, int value)
{
	glUniform1i(m_uniforms.at(uniform), value);
}

void Shader::setFloat(const std::string& uniform, float value)
{
	glUniform1f(m_uniforms.at(uniform), value);
}

void Shader::setVec3(const std::string& uniform, const Vec3& value)
{
	glUniform3f(m_uniforms.at(uniform), value.x, value.y, value.z);
}

void Shader::setMat4(const std::string& uniform, const Mat4& value)
{
	glUniformMatrix4fv(m_uniforms.at(uniform), 1, GL_TRUE, value.getInternal());
}

void loadShader(const std::string& path, std::string& ret)
{
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	try
	{
		file.open(path);
		std::stringstream stream;
		stream << file.rdbuf();
		file.close();
		ret = stream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Error::Shader - file at " << path << " unable to be read" << std::endl;
	}
}