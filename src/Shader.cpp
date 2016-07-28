#include "Shader.h"

void readShader(std::string path, std::string& ret);

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
	std::string vertexSource;
	std::string fragmentSource;
	readShader(vertexPath, vertexSource);
	readShader(fragmentPath, fragmentSource);
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

void Shader::use()
{
	glUseProgram(m_program);
}

GLuint Shader::getProgram()
{
	return m_program;
}

void readShader(std::string path, std::string& ret)
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