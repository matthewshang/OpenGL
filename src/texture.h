#pragma once

#include <GL/glew.h>

class Texture
{
public:
	Texture(const char* path);
	~Texture();

	void bind(GLuint unit);

private:
	GLuint m_texture;

};