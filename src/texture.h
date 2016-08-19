#pragma once

#include <GL/glew.h>

class Texture
{
public:
	enum
	{
		TEXTURE_DIFFUSE = 0,
		TEXTURE_SPECULAR = 1
	};

	Texture(const char* path);
	~Texture();

	void bind(GLuint unit);

private:
	GLuint m_texture;

};